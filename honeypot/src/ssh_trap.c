#include <ssh_trap.h>

void err(char *msg)
{
    if (!msg)
        ft_putstr_fd("Fatal error\n", 2);
    else
        ft_putstr_fd(msg, 2);
    exit(1);
}

void send_Broadcast(int accepted, t_server *server)
{
    for (int fd = 0; fd <= server->maxfd; fd++)
    {
        if (FD_ISSET(fd, &server->write_set) && fd != accepted)
            if (send(fd, server->send_buffer, strlen(server->send_buffer), 0) == -1)
                err(NULL);
    }
}

int setup_Server(int port)
{
    int opt;
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        err(NULL);
    opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    ft_bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
        err(NULL);
    if (listen(sockfd, 10) != 0)
        err(NULL);
    return (sockfd);
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
        err(NULL);
    if (connfd > server->maxfd)
        server->maxfd = connfd;
    server->clients[connfd].id = server->current_id;
    server->current_id++;
    FD_SET(connfd, &server->current);
    if (send(connfd, SSH_BANNER, ft_strlen(SSH_BANNER), 0) == -1)
        err(NULL);
    inet_ntop(AF_INET, &client.sin_addr, server->clients[connfd].ip, sizeof(server->clients[connfd].ip));
    server->clients[connfd].port = ntohs(client.sin_port);
}

void handle_Clients(int fd, t_server *server)
{
    int ret;
    ret = recv(fd, server->recv_buffer, MAX_MSG_SIZE, 0);
    if (ret <= 0)
    {
        FD_CLR(fd, &server->current);
        close(fd);
    }
    else
        handle_ClientMessage(fd, ret, server);
}


void handle_ClientMessage(int fd, int ret, t_server *server)
{
    for (int i = 0; i < ret; i++)
    {
        server->clients[fd].msg[server->clients[fd].msg_len] = server->recv_buffer[i];
        if (server->clients[fd].msg[server->clients[fd].msg_len] == '\n')
        {
            server->clients[fd].msg[server->clients[fd].msg_len] = '\0';
            if (server->clients[fd].msg_len > 0 && server->clients[fd].msg[server->clients[fd].msg_len - 1] == '\r')
            {
                server->clients[fd].msg[server->clients[fd].msg_len - 1] = '\0';
                ft_strlcpy(server->clients[fd].client_version, server->clients[fd].msg, sizeof(server->clients[fd].client_version));
            }
            ft_bzero(server->clients[fd].msg, server->clients[fd].msg_len);
            server->clients[fd].msg_len = 0;
        }
        else
            server->clients[fd].msg_len++;
    }
}

void run_Server(int sockfd, t_server *server)
{
    while (1)
    {
        server->read_set = server->write_set = server->current;
        if (select(server->maxfd + 1, &server->read_set, &server->write_set, NULL, NULL) == -1)
            err(NULL);
        for (int fd = 0; fd <= server->maxfd; fd++)
        {
            if (FD_ISSET(fd, &server->read_set))
            {
                if (fd == sockfd)
                    handle_NewConnections(sockfd, server);
                else
                    handle_Clients(fd, server);
            }
        }
    }
}

