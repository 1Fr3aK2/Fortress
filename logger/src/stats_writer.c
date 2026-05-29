#include <stats_writer.h>
#include <hash_map.h>


void parse_file(int fd, t_hashmap *password_map,t_hashmap *ip_map)
{
    t_entry temp;
    char *line;
    char *key;

    while((line = get_next_line(fd)))
    {
        if (ft_strchr(line, '{'))
            ft_bzero(&temp, sizeof(temp));
        else
        {
            key = extract_key(line);
            if (!key)
            {
                free(line);
                continue ;    
            }
            if (ft_strncmp(key, "ip", ft_strlen(key)) == 0)
            {
                parse_line(line, &temp);
                hashmap_insert(ip_map, &temp);
            }
            else if (ft_strncmp(key, "password", ft_strlen(key)) == 0)
            {
                parse_line(line, &temp);
                hashmap_insert(password_map, &temp);
            }
            free(key);
        }
        free(line);
    }
}