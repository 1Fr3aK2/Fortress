#include <stats_writer.h>
#include <hash_map.h>


int main()
{
    t_hashmap *hash_map;

    int fd = open("/var/log/fortress/events/events.json", O_RDONLY);
    if (fd == -1)
    {
        printf("aqui\n");
        return -1;
    }
    hash_map = ft_calloc(1, sizeof(t_hashmap));
    if (!hash_map)
        return (-1);
    parse_file(fd, hash_map);
    free_hashmap(hash_map);
    close(fd);
}
