#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <arpa/inet.h>
#include <stdbool.h>
#include <../libraries/libft/libft.h>


typedef struct s_entry
{
    char    key[256];
    int     count;
    struct s_entry *next;
}   t_entry;


typedef struct s_hashmap
{
    t_entry *buckets[256];
    int             size;
}   t_hashmap;

char *extract_key(char *line);
char *extract_value(char *line);
void parse_line(char *line, t_entry *bucket);
void hashmap_insert(t_hashmap *hashmap, t_entry *node);
unsigned long hash(char *key);
void free_hashmap(t_hashmap *hashmap);

#endif