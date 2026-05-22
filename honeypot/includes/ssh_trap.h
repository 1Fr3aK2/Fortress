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

typedef struct s_client
{
    int id;
    char msg[MAX_MSG_SIZE];
} t_client;

t_client clients[MAX_CLIENTS];


int maxfd = 0;
int current_id = 0;

char recv_buffer[MAX_MSG_SIZE];
char send_buffer[MAX_MSG_SIZE + 50];

fd_set write_set;
fd_set read_set;
fd_set current;


//functions

void err(char *msg);
void send_Broadcast(int accepted);

int setup_Server(int port);
void handle_NewConnections(int sockfd);
void handle_Clients(int fd);
void handle_ClientMessage(int fd, int ret);
void run_Server(int sockfd);
#endif
