#include <stats_writer.h>
#include <hash_map.h>


void fill_stats(t_entry *node, t_stats *stats)
{
    struct tm tm_info;
    ft_bzero(&tm_info, sizeof(tm_info));
    strptime(node->key, "%Y-%m-%dT%H:%M:%SZ", &tm_info);
    time_t event_time = mktime(&tm_info);
    time_t now = time(NULL);
    double diff = difftime(now, event_time);
    if (diff < 3600)
        stats->last_1h++;
    else if (diff < 86400)
        stats->last_24h++;
    stats->total++;
}

void parse_file(int fd, t_hashmap *password_map,t_hashmap *ip_map, t_stats *stats)
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
            else if (ft_strncmp(key, "timestamp", ft_strlen(key)) == 0)
            {
                parse_line(line, &temp);
                fill_stats(&temp, stats);              
            }
            free(key);
        }
        free(line);
    }
}