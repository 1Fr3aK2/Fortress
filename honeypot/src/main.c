#include <ssh_trap.h>

void close_fds()
{
    int i = 3;
    while (i <= FOPEN_MAX)
    {
        close(i);
        i++;
    }
}


static void handle_SIGINT(int sig)
{
    (void)sig;
    close_fds();
}

int main()
{   
    t_server *server;
    struct epoll_event ev;
    
    signal(SIGINT, handle_SIGINT);
    server = ft_calloc(1, sizeof(t_server));
    if (!server)
        err(NULL, server);
    server->sockfd = setup_Server(2222);
    if (server->sockfd == -1)
        err(NULL, server);
    server->epfd = epoll_create1(0);
    if (server->epfd == -1)
        err("epoll_create1() errror\n", server);
    ev.events = EPOLLIN;
    ev.data.fd = server->sockfd;
    if (epoll_ctl(server->epfd, EPOLL_CTL_ADD, server->sockfd, &ev) == -1)
        err("epoll_ctl() error\n", server);
    server->sshBind = ssh_bind_new();
    if (!server->sshBind)
        err("ssh_bind_new() error\n", server);
    ssh_bind_options_set(server->sshBind, SSH_BIND_OPTIONS_RSAKEY, "/etc/fortress/keys/ssh_host_rsa_key");
    run_Server(server->sockfd, server);
    ssh_bind_free(server->sshBind);
    free(server);
}