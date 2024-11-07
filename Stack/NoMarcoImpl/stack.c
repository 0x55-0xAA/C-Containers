#include "stack.h"
#include <stdlib.h> /* malloc realloc calloc free */
#include <string.h> /* memmove */

struct Stack* init_stack(size_t capa) {
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) {
        perror("stack alloc err!\n");
        exit(EXIT_SUCCESS);
    }
    stack->elements = (struct Node*)malloc(capa * sizeof(struct Node));
    if (!stack->elements) {
        perror("stack init err!\n");
        exit(EXIT_SUCCESS);
    }
    stack->top = -1;
    stack->size = 0;
    stack->capacity = CAPACITY;
    return stack;
}

struct Stack* alloc_stack() {
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) {
        perror("stack alloc err!\n");
        exit(EXIT_SUCCESS);
    }
    stack->elements = (struct Node*)malloc(CAPACITY * sizeof(struct Node));
        if (!stack->elements) {
        perror("stack init err!\n");
        exit(EXIT_SUCCESS);
    }
    stack->top = -1;
    stack->size = 0;
    stack->capacity = CAPACITY;
    return stack;
}

bool is_stack_empty(struct Stack *self) {
    return self->size == 0;
}

size_t get_size(struct Stack *self) {
    return self->size;
}

size_t get_capacity(struct Stack *self) {
    return self->capacity;
}

void ensure_capacity(struct Stack *self,size_t capa) {
    if (get_capacity(self) < capa) {
        size_t new_capacity = self->capacity << 1;
        if (new_capacity < capa) {
            new_capacity = capa;
        }
        struct Node *new_stack = (struct Node*)malloc(new_capacity * sizeof(struct Node));
        memmove(new_stack,self->elements,get_size(self) * sizeof(struct Node));
        self->elements = new_stack;
        self->capacity = new_capacity;
    }
}

void push_back(struct Stack *self,struct Node *val) {
    ensure_capacity(self,self->size + 1);
    self->elements[++self->top] = *val;
    self->size++;
}

void pop_back(struct Stack *self) {
    if (is_stack_empty(self)) {
        perror("stack is empty,pop_back err!\n");
        exit(EXIT_FAILURE);
    }
    --self->top;
    --self->size;
}

struct Node* get_top(struct Stack *self) {
    return &self->elements[self->top];
}

void free_stack(struct Stack *self) {
    if (self->elements) {
        free(self->elements);
    }
    free(self);
}
