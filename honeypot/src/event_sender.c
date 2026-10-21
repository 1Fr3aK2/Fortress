#include <event_sender.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#define RESOLVE_EVERY	30
#define RETRY_FAST		2
#define WARN_EVERY		10

static int						g_fd = -1;
static struct sockaddr_storage	g_addr;
static socklen_t				g_addrlen;
static time_t					g_last_resolve;
static time_t					g_last_warn;
static unsigned long			g_failed;

static void	sink_fail(const char *why)
{
	time_t	now;

	g_failed++;
	now = time(NULL);
	if (now - g_last_warn >= WARN_EVERY)
	{
		g_last_warn = now;
		fprintf(stderr, "[event_sender] %s (failures in this process: %lu)\n",
			why, g_failed);
	}
}

static int	sink_resolve(void)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				fd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	res = NULL;
	if (getaddrinfo(EVENT_SINK_HOST, EVENT_SINK_PORT, &hints, &res) != 0)
		return (-1);
	fd = g_fd;
	if (fd < 0)
		fd = socket(res->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (fd >= 0)
	{
		memcpy(&g_addr, res->ai_addr, res->ai_addrlen);
		g_addrlen = res->ai_addrlen;
		g_fd = fd;
	}
	freeaddrinfo(res);
	return (fd < 0 ? -1 : 0);
}

int	event_send(const char *buf, size_t len)
{
	time_t	now;

	if (len == 0 || len > EVENT_MAX)
	{
		sink_fail("event rejected: bad size");
		return (-1);
	}
	now = time(NULL);
	if (now - g_last_resolve >= (g_fd < 0 ? RETRY_FAST : RESOLVE_EVERY))
	{
		g_last_resolve = now;
		if (sink_resolve() < 0 && g_fd >= 0)
			sink_fail("cannot resolve logger, using last known address");
	}
	if (g_fd < 0)
	{
		sink_fail("logger unreachable (never resolved)");
		return (-1);
	}
	if (sendto(g_fd, buf, len, MSG_DONTWAIT,
			(struct sockaddr *)&g_addr, g_addrlen) != (ssize_t)len)
	{
		sink_fail("sendto failed");
		return (-1);
	}
	return (0);
}