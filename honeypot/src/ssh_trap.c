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
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        err(NULL);
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
    sprintf(server->send_buffer, "server: client %d just arrived\n", server->clients[connfd].id);
    send_Broadcast(connfd, server);
}

void handle_Clients(int fd, t_server *server)
{
    int ret;
    ret = recv(fd, server->recv_buffer, MAX_MSG_SIZE, 0);
    if (ret <= 0)
    {
        sprintf(server->send_buffer, "server: client %d just left\n", server->clients[fd].id);
        send_Broadcast(fd, server);
        FD_CLR(fd, &server->current);
        close(fd);
    }
    else
        handle_ClientMessage(fd, ret, server);

}


void handle_ClientMessage(int fd, int ret, t_server *server)
{
    for (int i = 0, j = ft_strlen(server->clients[fd].msg); i < ret; i++, j++)
    {
        server->clients[fd].msg[j] = server->recv_buffer[i];
        if (server->clients[fd].msg[j] == '\n')
        {
            server->clients[fd].msg[j] = '\0';
            sprintf(server->send_buffer, "client %d: %s\n", server->clients[fd].id, server->clients[fd].msg);
            send_Broadcast(fd, server);
            ft_bzero(server->clients[fd].msg, ft_strlen(server->clients[fd].msg));
            j = -1;
        }
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

