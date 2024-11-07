#include "maxheap.h"
#include "utils.h"
#include <stdlib.h> /* malloc realloc calloc free */
#include <string.h> /* memmove memcpy */
#include <stdio.h> /* printf scanf */
#include <assert.h> /* assert */

#define CAPACITY 1 /* default capacity */

struct MaxHeap* maxheap_init() {
    struct MaxHeap *max_heap = (struct MaxHeap*)malloc(sizeof(struct MaxHeap));
    max_heap->heap = (struct Node*)malloc((CAPACITY + 1) * sizeof(struct Node));
    max_heap->capacity = CAPACITY;
    max_heap->size = 0;
    return max_heap;
}

bool is_maxheap_empty(struct MaxHeap *self) {
    return self->size == 0;
}

size_t get_size(struct MaxHeap *self) {
    return self->size;
}

void insert(struct MaxHeap *self,struct Node *val) {
    ensure_capacity(self,self->size + 1);
    self->heap[++self->size] = *val;
    swim(self,self->size);
}

void pop_max(struct MaxHeap *self) {
    if (is_maxheap_empty(self)) {
        perror("heap is empty! pop err\n");
        exit(EXIT_FAILURE);
    }
    SWAP((void*)&self->heap[1],(void*)&self->heap[self->size--],sizeof(struct Node));
    sink(self,1);
}

struct Node* get_max(struct MaxHeap *self) {
    if (is_maxheap_empty(self)) {
        perror("heap is empty! get max value err\n");
        exit(EXIT_FAILURE);
    }
    return &self->heap[1];
}

void ensure_capacity(struct MaxHeap *self,size_t capa) {
    if (self->capacity < capa) {
        size_t new_capacity = (self->capacity << 1);
        if (new_capacity < capa) {
            new_capacity = capa;
        }
        struct Node *new_heap = (struct Node*)calloc((new_capacity + 1) , sizeof(struct Node));
        memmove(new_heap + 1,self->heap + 1,self->size * sizeof(struct Node));
        self->heap = new_heap;
        self->capacity = new_capacity; 
    }
}

void swim(struct MaxHeap *self,int index) {
    while (index > 1 && self->heap[index / 2].element < self->heap[index].element) {
        SWAP((void*)&self->heap[index / 2],(void*)&self->heap[index],sizeof(struct Node));
        index >>= 1;
    }
}

void sink(struct MaxHeap *self,int index) {
    int size = self->size;
    int start_index = index;
    while (2 * start_index <= size) {
        int left_child_index = 2 * start_index;
        int right_child_index = left_child_index + 1;
        if (left_child_index < size && self->heap[left_child_index].element < self->heap[right_child_index].element) {
            left_child_index = right_child_index;
        }
        if (self->heap[start_index].element >= self->heap[left_child_index].element) {
            break;
        }
        SWAP((void*)&self->heap[start_index],(void*)&self->heap[left_child_index],sizeof(struct Node));
        start_index = left_child_index;
    }
}

void free_maxheap(struct MaxHeap *self) {
    if (self->heap) {
        free(self->heap);
    }
    free(self);
}
// void print(struct MaxHeap *self) {
//     for (size_t i = 1;i < self->size;i++) {
//         printf("%d ",self->heap[i]);
//     }
//     printf("\n");
// }
