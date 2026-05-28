#include <stats_writer.h>
#include <hash_map.h>

/* int main()
{
    t_hashmap *hash_map;

    int fd = open("/var/log/fortress/events/events.json", O_RDONLY);
    if (fd == -1)
        return -1;
    hash_map = ft_calloc(1, sizeof(t_hashmap));
    if (!hash_map)
        return (-1);
    parse_file(fd, hash_map);
    close(fd);
    free(hash_map);
} */
/* void find_ip(char *line)
{

        if (ft_strncmp("\"ip\": ", line, ft_strlen("\"ip\": ")) == 0)
        {
            printf("TRUEE\n");
            return ;
        }
        else
        {
            printf("FALSE\n");
            return ;
        }
} */


int main()
{
    parse_line(("\"ip\": \"127.0.0.1\","));
}