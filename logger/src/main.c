#include <stats_writer.h>
#include <hash_map.h>
#include <heap_sort.h>
#include <ingest.h>
#include <errno.h>
#include <signal.h>
#include <sys/select.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define STATS_INTERVAL 60

static volatile sig_atomic_t g_stop = 0;

static void on_signal(int sig)
{
    (void)sig;
    g_stop = 1;
}

static void update_stats(void)
{
    t_hashmap *passwords_map;
    t_hashmap *ip_map;
    t_stats stats;
    t_heap *ip_top10;
    t_heap *passwords_top10;
    int fd;

    fd = open("/var/log/fortress/events/events.json", O_RDONLY);
    if (fd < 0)
        return;

    passwords_map = ft_calloc(1, sizeof(t_hashmap));
    ip_map = ft_calloc(1, sizeof(t_hashmap));
    if (!passwords_map || !ip_map)
    {
        free(passwords_map);
        free(ip_map);
        close(fd);
        return;
    }

    ft_bzero(&stats, sizeof(t_stats));
    parse_file(fd, passwords_map, ip_map, &stats);

    passwords_top10 = get_top10(passwords_map);
    ip_top10 = get_top10(ip_map);

    if (passwords_top10 && ip_top10)
        write_stats(ip_top10, passwords_top10, &stats);

    free_hashmap(passwords_map);
    free_hashmap(ip_map);
    free_heap(passwords_top10);
    free_heap(ip_top10);
    close(fd);
}

int main()
{
    fd_set rfds;
    struct timeval tv;
    time_t last;
    int ing;
    int r;

    signal(SIGTERM, on_signal);
    signal(SIGINT, on_signal);

    ing = ingest_open();
    if (ing < 0)
        return (1);

    last = time(NULL);
    while (!g_stop)
    {
        FD_ZERO(&rfds);
        FD_SET(ing, &rfds);
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        r = select(ing + 1, &rfds, NULL, NULL, &tv);
        if (r < 0 && errno != EINTR)
            break;
        if (r > 0 && FD_ISSET(ing, &rfds))
            ingest_handle(ing);

        if (time(NULL) - last >= STATS_INTERVAL)
        {
            update_stats();
            last = time(NULL);
        }
    }
    ingest_close(ing);
    return (0);
}

