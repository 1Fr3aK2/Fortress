#include <ssh_trap.h>

void handle_SIGCHLD(int sig)
{
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

void handle_SIGINT(int sig)
{
    (void)sig;
    g_running = 0;
}

void close_fds()
{
    int i = 3;
    while (i <= FOPEN_MAX)
    {
        close(i);
        i++;
    }
}