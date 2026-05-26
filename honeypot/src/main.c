#include <ssh_trap.h>

volatile sig_atomic_t g_running = 1;

int main()
{   
    t_server *server;
    struct epoll_event ev;
    
    struct sigaction sa_chld;
    struct sigaction sa_int;

    ft_memset(&sa_chld, 0, sizeof(sa_chld));
    sa_chld.sa_handler = handle_SIGCHLD;
    sigemptyset(&sa_chld.sa_mask);

    sa_chld.sa_flags = SA_RESTART | SA_NOCLDSTOP; 
    if (sigaction(SIGCHLD, &sa_chld, NULL) == -1)
        err("sigaction SIGCHLD error\n", NULL);

    ft_memset(&sa_int, 0, sizeof(sa_int));
    sa_int.sa_handler = handle_SIGINT;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1)
        err("sigaction SIGINT error\n", NULL);
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

    close(server->sockfd);
    close(server->epfd);
    ssh_bind_free(server->sshBind);
    free(server);

}