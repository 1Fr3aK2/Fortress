#include <stats_writer.h>
#include <hash_map.h>
#include <heap_sort.h>


int main()
{
    t_hashmap *passwords_map;
    t_hashmap *ip_map;
    t_stats stats;
    t_heap *ip_top10;
    t_heap *passwords_top10;

    while(1)
    {
        int fd = open("/var/log/fortress/events/events.json", O_RDONLY);
        if (fd == -1)
        {
            ft_putstr_fd("Waiting for events file...\n", 2);
            sleep(5);
            continue;
        }
        passwords_map = ft_calloc(1, sizeof(t_hashmap));
        if (!passwords_map)
            return (-1);
        ip_map = ft_calloc(1, sizeof(t_hashmap));
        if (!ip_map)
            return (-1);
        ft_bzero(&stats, sizeof(t_stats));
        parse_file(fd, passwords_map, ip_map, &stats);
        passwords_top10 = get_top10(passwords_map);
        ip_top10 = get_top10(ip_map);
        write_stats(ip_top10, passwords_top10, &stats);
        free_hashmap(passwords_map);
        free_hashmap(ip_map);
        free_heap(passwords_top10);
        free_heap(ip_top10);
        close(fd);
        sleep(60);
    }
}

