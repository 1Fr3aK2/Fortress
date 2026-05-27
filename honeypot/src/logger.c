#include <logger.h>

bool log_event(t_client *client, const char *user, const char *password)
{
    char buff[1024];
    char timef[200];
    int fd;
    struct tm *tm_info;
    
    tm_info = gmtime(&client->timestamp);
    strftime(timef, sizeof(timef), "%Y-%m-%dT%H:%M:%SZ", tm_info);
    snprintf(buff, sizeof(buff), "{\n\t\"timestamp\": \"%s\",\n\t\"ip\": \"%s\",\n\t\"port\" :%d,\n\t\"user\": \"%s\",\n\t\"password\": \"%s\",\n\t\"client_version\": \"%s\"\n}\n", timef, client->ip, client->port, user, password, client->client_version);
    fd = open("/var/log/fortress/events/events.json", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("open() error\n", 2);
        return (false);
    }
    write(fd, buff, ft_strlen(buff));
    close(fd);
    return (true);
}