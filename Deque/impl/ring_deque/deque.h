#ifndef DEQUE_H
#define DEQUE_H
#include <stddef.h> /* size_t */
#include <stdbool.h> /* _Bool */

#define CAPACITY 1 /* default capacity */

struct Node {
    int val_i;
};

struct RingDeque {
    struct Node *elements;
    size_t size;
    size_t capacity;
    size_t front;
    size_t rear;
};

extern struct RingDeque* alloc_deque();

extern struct RingDeque* init_deque(size_t default_capacity);

extern _Bool is_deque_empty(struct RingDeque *self);

extern _Bool is_deque_full(struct RingDeque *self);

extern void ensure_capacity(struct RingDeque *self,size_t capa);

extern void push_back(struct RingDeque *self,struct Node *val);

extern void push_front(struct RingDeque *self,struct Node *val);

extern void pop_back(struct RingDeque *self);

extern void pop_front(struct RingDeque *self);

extern struct Node* front(struct RingDeque *self);

extern struct Node* back(struct RingDeque *self);

extern void free_deque(struct RingDeque *self);

#endif // DEQUE_H