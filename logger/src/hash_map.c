#include <hash_map.h>

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
    char *value;

    value = extract_value(line);
    if (!value)
        return ;
    ft_strlcpy(bucket->key, value, sizeof(bucket->key));
    free(value);
}


void hashmap_insert(t_hashmap *hashmap, t_entry *entry)
{
    unsigned long index;
    t_entry *new_node;
    t_entry *curr;

    index = hash(entry->key);
    curr = hashmap->buckets[index];
    while (curr)
    {
        if ((ft_strncmp(curr->key, entry->key, sizeof(curr->key)) == 0))
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
    ft_strlcpy(new_node->key, entry->key, sizeof(new_node->key));
    new_node->count++;
    if (!hashmap->buckets[index])
        hashmap->buckets[index] = new_node;
    else
        curr->next = new_node;
    hashmap->size++;
}

unsigned long hash(char *key)
{
    char *str;
    unsigned long number = 0;
    str = key;
    while(*str)
    {
        number = (number * 31) + *str;
        str++;
    }
    number %= 256;
    return(number);
}
