#ifndef STATS_WRITER_H
#define STATS_WRITER_H

#include <../libraries/libft/libft.h>
#include "../libraries/libft/get_next_line/get_next_line_bonus.h"
#include <hash_map.h>

void parse_file(int fd, t_hashmap *hashmap);
#endif