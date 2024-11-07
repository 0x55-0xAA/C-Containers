#include "minheap.h"
#include "utils.h"
#include <stdlib.h> /* malloc calloc realloc free */
#include <string.h> /* memmove */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */

#define CAPACITY 1 /* default capacity */

struct MinHeap* minheap_init() {
    struct MinHeap *min_heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    if (!min_heap) {
        printf("minheap alloc err\n");
        exit(1);
    }
    min_heap->heap = (struct Node*)malloc((CAPACITY + 1) * sizeof(struct Node));
    min_heap->size = 0;
    min_heap->capacity = CAPACITY;
    return min_heap;
}

bool is_minheap_empty(struct MinHeap *self) {
    return self->size == 0;
}

size_t get_size(struct MinHeap *self) {
    return self->size;
}

void ensure_capacity(struct MinHeap *self,size_t capa) {
    if (self->capacity < capa) {
        size_t new_capacity = self->capacity << 1;
        if (new_capacity < capa) {
            new_capacity = capa;
        }
        struct Node *new_heap = (struct Node*)calloc((new_capacity + 1) , sizeof(struct Node));
        if (!new_heap) {
            perror("new heap realloc failed\n");
            exit(EXIT_FAILURE);
        }
        memmove(new_heap + 1,self->heap + 1,self->size * sizeof(struct Node));
        self->heap = new_heap;
        self->capacity = new_capacity;
    }
}

void swim(struct MinHeap *self,int index) {
    while (index > 1 && self->heap[index / 2].element > self->heap[index].element) {
        SWAP((void*)&self->heap[index / 2],(void*)&self->heap[index],sizeof(struct Node));
        index >>= 1;
    }
}

void sink(struct MinHeap *self,int index) {
    int size = self->size;
    int start_index = index;
    while (2 * start_index <= size) {
        int left_child_index = 2 * start_index;
        int right_child_index = left_child_index + 1;
        if (left_child_index < size && self->heap[left_child_index].element > self->heap[right_child_index].element) {
            left_child_index = right_child_index;
        }
        if (self->heap[start_index].element <= self->heap[left_child_index].element) {
            break;
        }
        SWAP((void*)&self->heap[start_index],(void*)&self->heap[left_child_index],sizeof(struct Node));
        start_index = left_child_index;
    }
}

void insert(struct MinHeap *self,struct Node *val) {
    ensure_capacity(self,self->size + 1);
    self->heap[++self->size] = *val;
    swim(self,self->size);
}

void pop_min(struct MinHeap *self) {
    if (is_minheap_empty(self)) {
        perror("heap is empty! pop err\n");
        exit(EXIT_FAILURE);
    }
    SWAP((void*)&self->heap[1],(void*)&self->heap[self->size--],sizeof(int));
    sink(self,1);
}

struct Node* get_min(struct MinHeap *self) {
    if (is_minheap_empty(self)) {
        perror("heap is empty! get min value err\n");
        exit(EXIT_FAILURE);
    }
    return &self->heap[1];
}

void free_minheap(struct MinHeap *self) {
    if (self->heap) {
        free(self->heap);
    }
    free(self);
}
// void print(struct MinHeap *self) {
//     for (size_t i = 1;i <= self->size;i++) {
//         printf("%d ",self->heap[i]);
//     }
//     printf("\n");
// }

