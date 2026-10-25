#include <logger.h>
#include <event_sender.h>

#define F_USER  32
#define F_PASS  96
#define F_VERS  64

static size_t   json_escape(char *dst, size_t dsize, const char *src, size_t maxraw)
{
    static const char   hex[] = "0123456789abcdef";
    size_t              o;
    size_t              i;
    unsigned char       c;

    o = 0;
    i = 0;
    if (!src)
        src = "";
    while (i < maxraw && src[i])
    {
        c = (unsigned char)src[i++];
        if (c == '"' || c == '\\')
        {
            if (o + 2 >= dsize)
                break ;
            dst[o++] = '\\';
            dst[o++] = c;
        }
        else if (c < 0x20 || c >= 0x7f)
        {
            if (o + 6 >= dsize)
                break ;
            dst[o++] = '\\';
            dst[o++] = 'u';
            dst[o++] = '0';
            dst[o++] = '0';
            dst[o++] = hex[c >> 4];
            dst[o++] = hex[c & 0xf];
        }
        else
        {
            if (o + 1 >= dsize)
                break ;
            dst[o++] = c;
        }
    }
    dst[o] = '\0';
    return (o);
}

bool log_event(t_client *client, const char *user, const char *password)
{
    char        buff[EVENT_MAX + 1];
    char        timef[200];
    char        eu[F_USER * 6 + 1];
    char        ep[F_PASS * 6 + 1];
    char        ev[F_VERS * 6 + 1];
    int         len;
    struct tm   *tm_info;

    tm_info = gmtime(&client->timestamp);
    strftime(timef, sizeof(timef), "%Y-%m-%dT%H:%M:%SZ", tm_info);
    json_escape(eu, sizeof(eu), user, F_USER);
    json_escape(ep, sizeof(ep), password, F_PASS);
    json_escape(ev, sizeof(ev), client->client_version, F_VERS);
    len = snprintf(buff, sizeof(buff),
            "{\n"
            "\t\"timestamp\": \"%s\",\n"
            "\t\"ip\": \"%s\",\n"
            "\t\"port\": \"%d\",\n"
            "\t\"user\": \"%s\",\n"
            "\t\"password\": \"%s\",\n"
            "\t\"client_version\": \"%s\"\n"
            "}\n",
            timef, client->ip, client->port, eu, ep, ev);
    if (len < 0 || (size_t)len >= sizeof(buff))
    {
        ft_putstr_fd("log_event: event too large\n", 2);
        return (false);
    }
    event_send(buff, (size_t)len);
    return (true);
}