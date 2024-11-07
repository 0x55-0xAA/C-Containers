#include "minheap.c"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a[] = {3,7,6,4,3,2,1};
    struct MinHeap *min_heap = minheap_init();
    for (int i = 0;i < 7;i++) {
        struct Node node = {.element=a[i]};
        insert(min_heap,&node);
    }

    while (!is_minheap_empty(min_heap)) {
        printf("%d ",get_min(min_heap)->element);
        pop_min(min_heap);
    }

    free_minheap(min_heap);
    return 0;
}
