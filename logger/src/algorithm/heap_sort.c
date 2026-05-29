#include <heap_sort.h>

t_heap *init_heap(t_heap *heap)
{
    
    return (ft_calloc(1, sizeof(t_heap)));
}

void heapify_up(t_heap *heap, int index)
{
    int father;
    t_entry *temp;

    while (index > 0)
    {
        father = ((index - 1) / 2);
        if (heap->entries[index]->count < heap->entries[father]->count)
        {
            temp = heap->entries[index];
            heap->entries[index] = heap->entries[father];
            heap->entries[father] = temp;
            index = father;
        }
        else
            return ;
    }
}

void heapify_down(t_heap *heap, int index)
{
    t_entry *temp;
    int left_child;
    int right_child;
    int smallest;

    while (1)
    {
        smallest = index;
        left_child = 2 * index + 1;
        right_child = 2 * index + 2;
        if (left_child < heap->size && heap->entries[left_child]->count < heap->entries[smallest]->count)
            smallest = left_child;
        if (right_child < heap->size && heap->entries[right_child]->count < heap->entries[smallest]->count)
            smallest = right_child;
        if (smallest == index)
            return ;
        temp = heap->entries[index];
        heap->entries[index] = heap->entries[smallest];
        heap->entries[smallest] = temp;
        index = smallest;
    }
}

void insert(t_heap *heap, t_entry *entry)
{
    heap->entries[heap->size] = entry;
    heap->size++;
    heapify_up(heap, heap->size - 1);
}

t_heap *build_top10(t_hashmap *hashmap)
{
    //heap_sort
    t_heap *heap;
    t_entry *curr;
    int i;

    heap = init_heap(heap);
    if (!heap)
        return (NULL);    
    i = 0;
    for (int i = 0; i < 256; i++)
    {
        curr = hashmap->buckets[i];
        while(curr)
        {
            if (heap->size < 10)
                insert(heap, curr);
            else if (curr->count > heap->entries[0]->count)
            {
                heap->entries[0] = curr;
                heapify_down(heap, 0);
            }
            curr = curr->next;
        }
    }
    return (heap);
}

void sort_top10(t_heap *heap)
{
    //insertion_sort
    t_entry *curr;
    int j;
    j = 0;
    for (int i = 1; i < heap->size; i++)
    {
        curr = heap->entries[i];
        j = i - 1;
        while (j >= 0 && (heap->entries[j]->count < curr->count))
        {
            heap->entries[j + 1] = heap->entries[j];
            j--;  
        }
        heap->entries[j + 1] = curr;
    }
}

t_heap *get_top10(t_hashmap *hashmap)
{
    t_heap *heap;
    heap = build_top10(hashmap);
    if (!heap)
        return (NULL);
    sort_top10(heap);
    return (heap);
}