#include <ssh_trap.h>

volatile sig_atomic_t g_running = 1;

void close_fds()
{
    int i = 3;
    while (i <= FOPEN_MAX)
    {
        close(i);
        i++;
    }
}

static void handle_SIGCHLD(int sig)
{
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

static void handle_SIGINT(int sig)
{
    (void)sig;
    g_running = 0;
}

int main()
{   
    t_server *server;
    struct epoll_event ev;
    
    signal(SIGINT, handle_SIGINT);
    signal(SIGCHLD, handle_SIGCHLD);
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