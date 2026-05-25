#include <ssh_trap.h>

int main()
{   
    t_server *server;
    int sockfd;
    struct epoll_event ev;
    
    server = ft_calloc(1, sizeof(t_server));
    if (!server)
        err(NULL);
    sockfd = setup_Server(2222);
    server->epfd = epoll_create1(0);
    if (server->epfd == -1)
        err("epoll_create1() errror\n");
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    if (epoll_ctl(server->epfd, EPOLL_CTL_ADD, sockfd, &ev) == -1)
        err("epoll_ctl() error\n");
    run_Server(sockfd, server);
}