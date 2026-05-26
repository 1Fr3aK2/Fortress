#ifndef SSH_TRAP_H
#define SSH_TRAP_H

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <../libraries/libft/libft.h>
#include <time.h>
#include <libssh/libssh.h>
#include <libssh/server.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>

#define MAX_CLIENTS 1024
#define SSH_BANNER "OpenSSH_8.9p1\r\n"
#define MAX_EVENTS 64

extern volatile sig_atomic_t g_running;


typedef struct s_client
{
    int         id;
    char        ip[INET_ADDRSTRLEN];
    uint32_t    port;
    time_t      timestamp;
    char        client_version[256];
} t_client;

typedef struct s_server
{
    t_client    clients[MAX_CLIENTS];
    int         current_id;
    int         epfd;
    int         sockfd;
    ssh_bind    sshBind;
} t_server;



//ssh_trap.c
void err(char *msg, t_server *server);
int setup_Server(int port);
void handle_NewConnections(int sockfd, t_server *server);
void run_Server(int sockfd, t_server *server);
void handle_sshSesion(t_server *server, int connfd);
void handle_childProcess(t_server *server, int connfd);
void close_fds();

#endif
