#ifndef STATS_WRITER_H
#define STATS_WRITER_H
#define _XOPEN_SOURCE 700 //trocar

#include <../libraries/libft/libft.h>
#include "../libraries/libft/get_next_line/get_next_line_bonus.h"
#include <hash_map.h>
#include <time.h>
#include <heap_sort.h>

typedef struct s_stats
{
    int total;
    int last_1h;
    int last_24h;
} t_stats;

void fill_stats(t_entry *node, t_stats *stats);
void parse_file(int fd, t_hashmap *password_map,t_hashmap *ip_map, t_stats *stats);
void write_stats(t_heap *ip_heaps, t_heap *passwords_heap, t_stats *stats);

#endif