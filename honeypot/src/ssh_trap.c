#include <ssh_trap.h>
#include <logger.h>

void err(char *msg, t_server *server)
{
    if (!msg)
        ft_putstr_fd("Fatal error\n", 2);
    else
        ft_putstr_fd(msg, 2);
    close_fds();
    if (server)
    {
        if (server->sshBind)
            ssh_bind_free(server->sshBind);
        free(server);
    }
    exit(1);
}

int setup_Server(int port)
{
    int opt;
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        ft_putstr_fd("socket() errorn\n", 2);
        return (-1);
    }
    opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    ft_bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        ft_putstr_fd("bind() error\n", 2);
        return (-1);
    }
    if (listen(sockfd, 10) != 0)
    {
        ft_putstr_fd("listen() error\n", 2);
        return (-1);
    }
    return (sockfd);
}


void handle_childProcess(t_server *server, int connfd)
{
    ssh_session session;
    ssh_message message;

    close(server->epfd);
    close(server->sockfd);
    session = ssh_new();
    if (!session)
    {
        close(connfd);
        err("ssh_new() error\n", server);
    }
    if (ssh_bind_accept_fd(server->sshBind, session, connfd) == SSH_ERROR)
    {
        ssh_disconnect(session);
        ssh_free(session);
        close(connfd);
        err("ssh_bind_accept_fd() error\n", server);
    }
    if (ssh_handle_key_exchange(session) != SSH_OK)
    {
        ssh_disconnect(session);
        ssh_free(session);
        close(connfd);
        err("ssh_handle_key_exchange() error\n", server);
    }
    ft_strlcpy(server->clients[connfd].client_version, ssh_get_clientbanner(session), sizeof(server->clients[connfd].client_version));
    while ((message = ssh_message_get(session)))
    {
        if (ssh_message_type(message) == SSH_REQUEST_AUTH && ssh_message_subtype(message) == SSH_AUTH_METHOD_PASSWORD)
        {
            printf("User: %s\n", ssh_message_auth_user(message));
            printf("Password: %s\n", ssh_message_auth_password(message));
            if (!log_event(&server->clients[connfd], ssh_message_auth_user(message), ssh_message_auth_password(message)))
            {
                ssh_disconnect(session);
                ssh_free(session);
                err("log_events() error\n", server);
            }
            ssh_message_reply_default(message);
            ssh_message_free(message);
        }
        else
        {
            ssh_message_reply_default(message);
            ssh_message_free(message);
        }
    }
    ssh_disconnect(session);
    ssh_free(session);
    ssh_bind_free(server->sshBind);
    free(server);
    close(connfd);
    exit(0);
}


void handle_sshSesion(t_server *server, int connfd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        close(connfd);
        ft_putstr_fd("Process error\n", 2);
        return ;
    }
    else if (pid == 0)
        handle_childProcess(server, connfd);
    else
    {
        close(connfd);
        return ;
    }
}

void handle_NewConnections(int sockfd, t_server *server)
{
    struct sockaddr_in client;
    socklen_t len;
    int connfd;

    ft_bzero(&client, sizeof(client));
    len = sizeof(client);
    connfd = accept(sockfd, (struct sockaddr *)&client, &len);
    if (connfd < 0)
    {
        close(connfd);
        ft_putstr_fd("accept() error\n", 2);
        return ;
    }
    if (connfd >= MAX_CLIENTS)
    {
        ft_putstr_fd("Warning: connection refused, connfd exceeds MAX_CLIENTS\n", 2);
        close(connfd);
        return;
    }
    server->clients[connfd].id = server->current_id;
    server->current_id++;
    inet_ntop(AF_INET, &client.sin_addr, server->clients[connfd].ip, sizeof(server->clients[connfd].ip));
    server->clients[connfd].port = ntohs(client.sin_port);
    server->clients[connfd].timestamp = time(NULL);
    handle_sshSesion(server, connfd);
}

void run_Server(int sockfd, t_server *server)
{
    struct epoll_event events[MAX_EVENTS];
    int n;

    while (g_running)
    {
        n = epoll_wait(server->epfd, events, MAX_EVENTS, -1);
        if (n == -1)
        {
            if (errno == EINTR)
            {
                if (g_running == 0)
                    break;
                continue;
            }
            err("epoll_wait() error\n", server);
        }
        for (int i = 0; i < n; i++)
        {
            if (events[i].data.fd == sockfd)
                handle_NewConnections(sockfd, server);
        }
    }
}

