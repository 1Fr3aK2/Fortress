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

char *extract_value(char *line)
{
    char *key;
    char *start;
    char *end;
    size_t len;

    start = ft_strchr(line, ':');
    if (!start)
        return (NULL);
    start = ft_strchr(start, '"');
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

void parse_line(char *line, t_entry *bucket)
{
    char *key;
    char *value;
    
    key = extract_key(line);
    if (!key)
        return ;
    value = extract_value(line);
    if (!value)
    {
        free(key);
        return ;
    }
    if (ft_strncmp(key, "ip", ft_strlen(key)) == 0)
        ft_strlcpy(bucket->ip, value, sizeof(bucket->ip));
    else if (ft_strncmp(key, "password", ft_strlen(key)) == 0)
        ft_strlcpy(bucket->password, value, sizeof(bucket->password));
    free(value);
    free(key);
    return ;
}


void hashmap_insert(t_hashmap *hashmap, t_entry *entry)
{
    unsigned long index;
    t_entry *new_node;
    t_entry *curr;

    index = hash(entry->ip, entry->password);
    curr = hashmap->buckets[index];
    while (curr)
    {
        if ((ft_strncmp(curr->ip, entry->ip, sizeof(curr->ip)) == 0) && (ft_strncmp(curr->password, entry->password, sizeof(curr->password)) == 0))
        {
            curr->count++;
            return ;
        }
        if (!curr->next)
            break;
        curr = curr->next;
    }
    new_node = ft_calloc(1, sizeof(t_entry));
    if (!new_node)
        return ;
    ft_strlcpy(new_node->ip, entry->ip, sizeof(new_node->ip));
    ft_strlcpy(new_node->password, entry->password, sizeof(new_node->password));
    new_node->count++;
    if (!hashmap->buckets[index])
        hashmap->buckets[index] = new_node;
    else
        curr->next = new_node;
    hashmap->size++;
}


unsigned long hash(char *ip, char *password)
{
    char *str;
    unsigned long number = 0;
    str = ip;
    while(*str)
    {
        number = (number * 31) + *str;
        str++;
    }
    str = password;
    while (*str)
    {
        number = (number * 31) + *str;
        str++;
    }
    number %= 256;
    return(number);
}

void free_hashmap(t_hashmap *hashmap)
{
    t_entry *tmp;
    t_entry *curr;
    int i;
    i = 0;
    while(i < 256)
    {
        curr = hashmap->buckets[i]; 
        while(curr)
        {
            tmp = curr->next;
            if (curr)
                free(curr);
            curr = tmp;
        }
        i++;
    }
    free(hashmap);
}