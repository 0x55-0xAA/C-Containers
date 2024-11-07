#include "maxheap.c"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a[] = {3,7,6,4,3,2,1};
    struct MaxHeap *max_heap = maxheap_init();
    for (int i = 0;i < 7;i++) {
        struct Node node = {.element=a[i]};
        insert(max_heap,&node);
    }

    while (!is_maxheap_empty(max_heap)) {
        printf("%d ",get_max(max_heap)->element);
        pop_max(max_heap);
    }

    free_maxheap(max_heap);
    return 0;
}
