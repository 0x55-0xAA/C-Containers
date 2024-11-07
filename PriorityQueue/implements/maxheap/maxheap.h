#ifndef MAX_HEAP_H
#define MAX_HEAP_H
#include <stddef.h>
#include <stdbool.h>

struct Node {
    int element;
};

struct MaxHeap {
    struct Node *heap;
    size_t size;
    size_t capacity;
};

extern struct MaxHeap* maxheap_init();

extern bool is_maxheap_empty(struct MaxHeap *self);

extern size_t get_size(struct MaxHeap *self);

extern void ensure_capacity(struct MaxHeap *self,size_t capa);

extern void swim(struct MaxHeap *self,int index);

extern void sink(struct MaxHeap *self,int index);

extern void insert(struct MaxHeap *self,struct Node *val);

extern void pop_max(struct MaxHeap *self);

extern struct Node *get_max(struct MaxHeap *self);

extern void free_maxheap(struct MaxHeap *self);

#endif // MAX_HEAP_H