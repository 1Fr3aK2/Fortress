#include <ssh_trap.h>

int main()
{   
    t_server *server;
    int sockfd;

    server = ft_calloc(1, sizeof(t_server));
    if (!server)
        err(NULL);
    sockfd = setup_Server(2222);
    FD_ZERO(&server->current);
    FD_SET(sockfd, &server->current);
    server->maxfd = sockfd;

    run_Server(sockfd, server);
}