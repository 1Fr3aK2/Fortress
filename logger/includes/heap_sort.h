#include <hash_map.h>

typedef struct s_heap
{
    t_entry *entries[10];
    int     size;
}   t_heap;  

t_heap *init_heap(t_heap *heap);
void heapify_up(t_heap *heap, int index);
void heapify_down(t_heap *heap, int index);
void insert(t_heap *heap, t_entry *entry);
t_heap *build_top10(t_hashmap *hashmap);
