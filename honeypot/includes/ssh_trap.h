#ifndef SSH_TRAP_H
#define SSH_TRAP_H

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <../libraries/libft/libft.h>

#define MAX_CLIENTS 1024
#define MAX_MSG_SIZE 1000000
#define SSH_BANNER "SSH-2.0-OpenSSH_8.9p1\r\n"



typedef struct s_client
{
    int id;
    char msg[MAX_MSG_SIZE];
} t_client;

typedef struct s_server
{
    t_client clients[MAX_CLIENTS];
    int maxfd;
    int current_id;
    char recv_buffer[MAX_MSG_SIZE];
    char send_buffer[MAX_MSG_SIZE + 50]; 
    fd_set write_set;
    fd_set read_set;
    fd_set current;
} t_server;



//ssh_trap.c
void err(char *msg);
void send_Broadcast(int accepted, t_server *server);
int setup_Server(int port);
void handle_NewConnections(int sockfd, t_server *server);
void handle_Clients(int fd, t_server *server);
void handle_ClientMessage(int fd, int ret, t_server *server);
void run_Server(int sockfd, t_server *server);


#endif
