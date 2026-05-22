#include <ssh_trap.h>

void err(char *msg)
{
    if (!msg)
        ft_putstr_fd("Fatal error\n", 2);
    else
        ft_putstr_fd(msg, 2);
    exit(1);
}

void send_Broadcast(int accepted)
{
    for (int fd = 0; fd <= maxfd; fd++)
    {
        if (FD_ISSET(fd, &write_set) && fd != accepted)
            if (send(fd, send_buffer, strlen(send_buffer), 0) == -1)
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

void handle_NewConnections(int sockfd)
{
    struct sockaddr_in client;
    socklen_t len;
    int connfd;

    ft_bzero(&client, sizeof(client));
    len = sizeof(client);
    connfd = accept(sockfd, (struct sockaddr *)&client, &len);
    if (connfd < 0)
        err(NULL);
    if (connfd > maxfd)
        maxfd = connfd;
    clients[connfd].id = current_id;
    current_id++;
    FD_SET(connfd, &current);
    sprintf(send_buffer, "server: client %d just arrived\n", clients[connfd].id);
    send_Broadcast(connfd);
}

void handle_Clients(int fd)
{
    int ret;
    ret = recv(fd, recv_buffer, MAX_MSG_SIZE, 0);
    if (ret <= 0)
    {
        sprintf(send_buffer, "server: client %d just left\n", clients[fd].id);
        send_Broadcast(fd);
        FD_CLR(fd, &current);
        close(fd);
    }
    else
        handle_ClientMessage(fd, ret);

}


void handle_ClientMessage(int fd, int ret)
{
    for (int i = 0, j = ft_strlen(clients[fd].msg); i < ret; i++, j++)
    {
        clients[fd].msg[j] = recv_buffer[i];
        if (clients[fd].msg[j] == '\n')
        {
            clients[fd].msg[j] = '\0';
            sprintf(send_buffer, "client %d: %s\n", clients[fd].id, clients[fd].msg);
            send_Broadcast(fd);
            ft_bzero(clients[fd].msg, ft_strlen(clients[fd].msg));
            j = -1;
        }
    }
}

void run_Server(int sockfd)
{
    while (1)
    {
        read_set = write_set = current;
        if (select(maxfd + 1, &read_set, &write_set, NULL, NULL) == -1)
            err(NULL);
        for (int fd = 0; fd <= maxfd; fd++)
        {
            if (FD_ISSET(fd, &read_set))
            {
                if (fd == sockfd)
                    handle_NewConnections(sockfd);
                else
                    handle_Clients(fd);
            }
        }
    }
}

int main()
{    
    int sockfd;

    sockfd = setup_Server(2222);
    FD_ZERO(&current);
    FD_SET(sockfd, &current);
    maxfd = sockfd;

    run_Server(sockfd);
}