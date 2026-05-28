#include <stats_writer.h>
#include <hash_map.h>


void parse_file(int fd, t_hashmap *hashmap)
{
    char *line;
    t_entry temp;

    while((line = get_next_line(fd)))
    {
        printf("line: %s\n", line);
        if (ft_strchr(line, '{'))
            ft_bzero(&temp, sizeof(temp));
        else if (ft_strchr(line, '}'))
        {
            if (temp.ip[0] != '\0' && temp.password[0] != '\0')
                hashmap_insert(hashmap, &temp);
        }
        else
            parse_line(line, &temp);    
        free(line);
    }
}