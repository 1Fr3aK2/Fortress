#include <stats_writer.h>
#include <heap_sort.h>
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
    if (diff < 86400)
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

void write_stats(t_heap *ip_heaps, t_heap *passwords_heap, t_stats *stats)
{
    time_t now;
    char timef[200];
    char buff[1024];
    int         fd;

    fd = open("/var/log/fortress/logs/stats.json", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return ;
    now = time(NULL);
    strftime(timef, sizeof(timef), "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));
    snprintf(buff, sizeof(buff), "{\n\t\"generated_at\": \"%s\",\n\t\"total_atemps\": %d,\n\t\"attempts_last_1h\": %d,\n\t\"attempts_last_24h\": %d,\n\t\"top_passwords\": [\n", timef, stats->total, stats->last_1h, stats->last_24h);
    write(fd, buff, ft_strlen(buff));
    for (int i = 0; i < passwords_heap->size; i++)
    {
        snprintf(buff, sizeof(buff), "\t\t{\"password\": \"%s\", \"count\": %d}", passwords_heap->entries[i]->key, passwords_heap->entries[i]->count);
        write(fd, buff, ft_strlen(buff));
        if (i + 1 < passwords_heap->size)
            write(fd, ",", 1);
        write(fd, "\n", 1);
    }
    write(fd, "\t],\n\t", 5);
    snprintf(buff, sizeof(buff), "\"top_ips\": [\n");
    write(fd, buff, ft_strlen(buff));
    for (int i = 0; i < ip_heaps->size; i++)
    {
        snprintf(buff, sizeof(buff), "\t\t{\"ip\": \"%s\", \"count\": %d}", ip_heaps->entries[i]->key, ip_heaps->entries[i]->count);
        write(fd, buff, ft_strlen(buff));
        if (i + 1 < ip_heaps->size)
            write(fd, ",", 1);
        write(fd, "\n", 1);
    }
    write(fd, "\t]\n}\n", 5);
    close(fd);
}
