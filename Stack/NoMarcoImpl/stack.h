#ifndef STACK_H
#define STACK_H
#include <stddef.h> /* size_t */
#include <stdbool.h> /* bool */

#define CAPACITY 1 /* default capacity */

struct Node {
    int val_i;
};

struct Stack {
    struct Node *elements;
    long long top;
    size_t size;
    size_t capacity;
};

extern struct Stack* init_stack(size_t capa);

extern struct Stack* alloc_stack();

extern bool is_stack_empty(struct Stack *self);

extern size_t get_size(struct Stack *self);

extern size_t get_capacity(struct Stack *self);

extern void ensure_capacity(struct Stack *self,size_t capa);

extern void push_back(struct Stack *self,struct Node *val);

extern void pop_back(struct Stack *self);

extern struct Node* get_top(struct Stack *self);

extern void free_stack(struct Stack *self);
#endif // STACK_H
