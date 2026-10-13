#include <ingest.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <../libraries/libft/libft.h>

int ingest_open(void)
{
    struct sockaddr_in addr;
    int fd;

    fd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
    if (fd < 0)
    {
        ft_putendl_fd("Error: ingest socket", 2);
        return -1;
    }
    ft_memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(INGEST_PORT);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) > 0)
    {
        ft_putendl_fd("Error: ingest bind", 2);
        close(fd);
        return -1;
    }
    return fd;
}

static void	ingest_dump(const char *buf, ssize_t n)
{
    unsigned char c;

    fprintf(stderr, "[ingest] %zd bytes: ", n);
    for (ssize_t i = 0; i < n; i++)
    {
        c = (unsigned char)buf[i];
        if (c == '\n')
            ft_putstr_fd("\\n", 2);
        else if (c >= 20 && c < 127)
            ft_putchar_fd(c, 2);
        else
            fprintf(stderr, "\\x%02x", c);
    }
    ft_putchar_fd('\n', 2);   
}


void ingest_handle(int fd)
{
    char buf[INGEST_MAX + 1];
    ssize_t n;

    n = recv(fd, buf, sizeof(buf), 0);
    if (n < 0)
    {
        if (errno != EAGAIN && errno != EINTR)
            ft_putendl_fd("Error: ingest recv", 2);
        return ;
    }
    if (n > INGEST_MAX)
    {
        ft_putstr_fd("[ingest] rejected: datagram too large\n", 2);
        return;
    }
    ingest_dump(buf, n);
}

void	ingest_close(int fd)
{
	if (fd >= 0)
		close(fd);
}