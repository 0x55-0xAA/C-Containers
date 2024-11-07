#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include <stddef.h>
#include <stdbool.h>

struct Node {
    int element;
};

struct MinHeap {
    struct Node *heap;
    size_t size;
    size_t capacity;
};

extern struct MinHeap* minheap_init();

extern bool is_minheap_empty(struct MinHeap *self);

extern size_t get_size(struct MinHeap *self);

extern void ensure_capacity(struct MinHeap *self,size_t capa);

extern void swim(struct MinHeap *self,int index);

extern void sink(struct MinHeap *self,int index);

extern void insert(struct MinHeap *self,struct Node *val);

extern void pop_min(struct MinHeap *self);

extern struct Node* get_min(struct MinHeap *self);

extern void free_minheap(struct MinHeap *self);

#endif // MIN_HEAP_H