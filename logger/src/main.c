#include <stats_writer.h>
#include <hash_map.h>

void    print_hashmap(t_hashmap *map)
{
    int     i;
    t_entry *current;

    if (!map)
        return;

    printf("Hashmap size: %d\n", map->size);

    i = 0;
    while (i < 256)
    {
        current = map->buckets[i];

        if (current)
            printf("\nBucket[%d]:\n", i);

        while (current)
        {
            printf(" KEY: \"%s\" (len: %d) -> bytes: ", current->key, (int)ft_strlen(current->key));
            for (size_t j = 0; current->key[j]; j++)
                printf("%02X ", (unsigned char)current->key[j]);
            printf("\n");


            printf("  Count: %d\n", current->count);
            printf("------------------------\n");

            current = current->next;
        }
        i++;
    }
}

int main()
{
    t_hashmap *passwords_map;
    t_hashmap *ip_map;
    t_stats stats;

    int fd = open("/var/log/fortress/events/events.json", O_RDONLY);
    if (fd == -1)
    {
        printf("aqui\n");
        return -1;
    }
    passwords_map = ft_calloc(1, sizeof(t_hashmap));
    if (!passwords_map)
        return (-1);
    ip_map = ft_calloc(1, sizeof(t_hashmap));
    if (!ip_map)
        return (-1);
    ft_bzero(&stats, sizeof(t_stats));
    parse_file(fd, passwords_map, ip_map, &stats);
    printf("Passwords:\n");
    print_hashmap(passwords_map);
    printf("ip:\n");
    print_hashmap(ip_map);
    free_hashmap(passwords_map);
    free_hashmap(ip_map);
    close(fd);
}

