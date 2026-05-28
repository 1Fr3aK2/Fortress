#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <arpa/inet.h>
#include <stdbool.h>
#include <../libraries/libft/libft.h>


typedef struct s_entry
{
    char    password[256];
    int     count;
    char    ip[INET_ADDRSTRLEN];
    struct s_entry *next;
}   t_entry;


typedef struct s_hashmap
{
    t_entry *buckets[256];
    int             size;
}   t_hashmap;

unsigned long hash(char *line);


#endif