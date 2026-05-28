#include <hash_map.h>

char *extract_key(char *line)
{
    char *key;
    char *start;
    char *end;
    size_t len;

    start = ft_strchr(line, '"');
    if (!start)
        return (NULL);
    start++;
    end = ft_strchr(start, '"');
    if (!end)
        return (NULL);
    len = end - start;
    key = (char *)malloc(len + 1);
    if (!key)
        return (NULL);
    ft_strlcpy(key, start, len + 1);
    return (key);
}


void parse_line(char *line)
{
    char ip[INET_ADDRSTRLEN];
    char password[256];
    char *key;

    key = extract_key(line);
    if (!key)
        return ;
    if (ft_strncmp(key, "ip", ft_strlen(key)) == 0)
        printf("TRUE\n");
    else
        printf("FALSE");
    return ;
}


void hashmap_insert(t_hashmap *hashmap, char *line)
{
    unsigned long index;

    index = hash(line);
    if (!hashmap->buckets[index])
    {
        hashmap->buckets[index]->count++;
        parse_line();
    }
    else
    {
        hashmap->buckets[index]->count++;
        hashmap->buckets[index]->next = ft_calloc(1, sizeof(t_hashmap));
        if (!hashmap->buckets[index]->next)
            return ;
        parse_line();
    }
}

unsigned long hash(char *line)
{
    unsigned long number = 0;
    while(*line)
    {
        number = (number * 31) + *line;
        line++;
    }
    number %= 256;
    return(number);
}