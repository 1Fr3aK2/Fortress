#include "ingest.h"
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define NFIELDS 6
#define EVENTS_PATH "/var/log/fortress/events/events.json"

typedef struct s_field
{
	const char	*p;
	size_t		len;
}	t_field;

static const char	*g_keys[NFIELDS] = {
	"timestamp", "ip", "port", "user", "password", "client_version"
};

/* máximo de bytes originais por campo (antes do escape) */
static const size_t	g_max[NFIELDS] = { 20, 15, 5, 32, 96, 64 };

static int	g_store = -1;

static void	warn_limited(const char *msg)
{
	static time_t	last;
	time_t			now;

	now = time(NULL);
	if (now - last >= 5)
	{
		last = now;
		fprintf(stderr, "[ingest] %s\n", msg);
	}
}

static int	store_open(void)
{
	umask(022);
	g_store = open(EVENTS_PATH, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0644);
	if (g_store < 0)
	{
		perror("ingest: cannot open " EVENTS_PATH);
		return (-1);
	}
	return (0);
}

static int	store_append(const char *buf, size_t len)
{
	ssize_t	w;

	while (len > 0)
	{
		w = write(g_store, buf, len);
		if (w < 0)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		buf += w;
		len -= (size_t)w;
	}
	return (0);
}

int	ingest_open(void)
{
	struct sockaddr_in	addr;
	int					fd;

	if (store_open() < 0)
		return (-1);
	fd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (fd < 0)
	{
		perror("ingest: socket");
		close(g_store);
		return (-1);
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(INGEST_PORT);
	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("ingest: bind");
		close(fd);
		close(g_store);
		return (-1);
	}
	return (fd);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_hex(char c)
{
	return (is_digit(c) || (c >= 'a' && c <= 'f'));
}

static int	expect(const char **p, const char *end, const char *lit)
{
	size_t	l;

	l = strlen(lit);
	if ((size_t)(end - *p) < l || memcmp(*p, lit, l) != 0)
		return (0);
	*p += l;
	return (1);
}

/* lê um valor até à aspa de fecho, por unidades: \" \\ \u00xx ou 1 caractere */
static int	read_value(const char **pp, const char *end, size_t max, t_field *f)
{
	const char		*p;
	size_t			units;
	unsigned char	c;

	p = *pp;
	f->p = p;
	units = 0;
	while (p < end && *p != '"')
	{
		c = (unsigned char)*p;
		if (c < 0x20 || c > 0x7e)
			return (0);
		if (c != '\\')
			p++;
		else if (p + 1 < end && (p[1] == '"' || p[1] == '\\'))
			p += 2;
		else if ((size_t)(end - p) >= 6 && p[1] == 'u' && p[2] == '0'
			&& p[3] == '0' && is_hex(p[4]) && is_hex(p[5]))
			p += 6;
		else
			return (0);
		if (++units > max)
			return (0);
	}
	if (p >= end)
		return (0);
	f->len = (size_t)(p - f->p);
	*pp = p + 1;
	return (1);
}

static int	ingest_parse(const char *s, size_t n, t_field f[NFIELDS])
{
	const char	*p;
	const char	*end;
	char		lit[40];
	int			i;

	p = s;
	end = s + n;
	if (!expect(&p, end, "{\n"))
		return (0);
	for (i = 0; i < NFIELDS; i++)
	{
		snprintf(lit, sizeof(lit), "\t\"%s\": \"", g_keys[i]);
		if (!expect(&p, end, lit) || !read_value(&p, end, g_max[i], &f[i]))
			return (0);
		if (!expect(&p, end, (i + 1 < NFIELDS) ? ",\n" : "\n"))
			return (0);
	}
	return (expect(&p, end, "}\n") && p == end);
}

static int	timestamp_ok(const t_field *f)
{
	static const char	pat[] = "dddd-dd-ddTdd:dd:ddZ";
	size_t				i;

	if (f->len != 20)
		return (0);
	for (i = 0; i < 20; i++)
	{
		if (pat[i] == 'd' ? !is_digit(f->p[i]) : f->p[i] != pat[i])
			return (0);
	}
	return (1);
}

static int	ip_ok(const t_field *f)
{
	char			tmp[16];
	struct in_addr	a;

	if (f->len == 0 || f->len > 15)
		return (0);
	memcpy(tmp, f->p, f->len);
	tmp[f->len] = '\0';
	return (inet_pton(AF_INET, tmp, &a) == 1);
}

static int	port_ok(const t_field *f)
{
	size_t	i;
	long	v;

	if (f->len == 0 || f->len > 5)
		return (0);
	v = 0;
	for (i = 0; i < f->len; i++)
	{
		if (!is_digit(f->p[i]))
			return (0);
		v = v * 10 + (f->p[i] - '0');
	}
	return (v >= 1 && v <= 65535);
}

static int	ingest_format(char *out, size_t size, const t_field f[NFIELDS])
{
	time_t		now;
	struct tm	tm;
	char		ts[32];

	now = time(NULL);
	gmtime_r(&now, &tm);
	strftime(ts, sizeof(ts), "%Y-%m-%dT%H:%M:%SZ", &tm);
	return (snprintf(out, size,
			"{\n"
			"\t\"timestamp\": \"%.*s\",\n"
			"\t\"ip\": \"%.*s\",\n"
			"\t\"port\": \"%.*s\",\n"
			"\t\"user\": \"%.*s\",\n"
			"\t\"password\": \"%.*s\",\n"
			"\t\"client_version\": \"%.*s\",\n"
			"\t\"received_at\": \"%s\"\n"
			"}\n",
			(int)f[0].len, f[0].p, (int)f[1].len, f[1].p,
			(int)f[2].len, f[2].p, (int)f[3].len, f[3].p,
			(int)f[4].len, f[4].p, (int)f[5].len, f[5].p, ts));
}

void	ingest_handle(int fd)
{
	char	buf[INGEST_MAX + 1];
	char	out[INGEST_MAX + 128];
	t_field	f[NFIELDS];
	ssize_t	n;
	int		len;

	n = recv(fd, buf, sizeof(buf), 0);
	if (n < 0)
	{
		if (errno != EAGAIN && errno != EINTR)
			perror("ingest: recv");
		return ;
	}
	if (n > INGEST_MAX)
		return (warn_limited("rejected: datagram too large"));
	if (!ingest_parse(buf, (size_t)n, f) || !timestamp_ok(&f[0])
		|| !ip_ok(&f[1]) || !port_ok(&f[2]))
		return (warn_limited("rejected: invalid event"));
	len = ingest_format(out, sizeof(out), f);
	if (len < 0 || (size_t)len >= sizeof(out))
		return (warn_limited("rejected: cannot format event"));
	if (store_append(out, (size_t)len) < 0)
		warn_limited("cannot write event to events.json");
}

void	ingest_close(int fd)
{
	if (fd >= 0)
		close(fd);
	if (g_store >= 0)
	{
		close(g_store);
		g_store = -1;
	}
}