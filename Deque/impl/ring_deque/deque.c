#include "deque.h"
#include <stdlib.h> /* malloc realloc calloc free */
#include <string.h> /* memmove */

struct RingDeque* alloc_deque() {
    struct RingDeque *ring_deque = (struct RingDeque*)malloc(sizeof(struct RingDeque));
    if (!ring_deque) {
        perror("deque alloc err\n");
        exit(EXIT_FAILURE);
    }
    ring_deque->elements = (struct Node*)malloc(CAPACITY * sizeof(struct Node));
    if (!ring_deque->elements) {
        perror("deque's array alloc err\n");
        exit(EXIT_FAILURE);
    }
    ring_deque->size = 0;
    ring_deque->capacity = CAPACITY;
    ring_deque->front = 0;
    ring_deque->rear = 0;
    return ring_deque;
}

struct RingDeque* init_deque(size_t default_capacity) {
    struct RingDeque *ring_deque = (struct RingDeque*)malloc(sizeof(struct RingDeque));
    if (!ring_deque) {
        perror("deque alloc err\n");
        exit(EXIT_FAILURE);
    }
    ring_deque->elements = (struct Node*)malloc(default_capacity * sizeof(struct Node));
    if (!ring_deque->elements) {
        perror("deque's array alloc err\n");
        exit(EXIT_FAILURE);
    }
    ring_deque->size = 0;
    ring_deque->capacity = default_capacity;
    ring_deque->front = 0;
    ring_deque->rear = 0;
    return ring_deque;
}

_Bool is_deque_empty(struct RingDeque *self) {
    return self->size == 0;
}

_Bool is_deque_full(struct RingDeque *self) {
    return self->size == self->capacity;
}

void ensure_capacity(struct RingDeque *self,size_t capa) {
    if (self->capacity < capa) {
        size_t new_capacity = self->capacity << 1;
        if (new_capacity < capa) {
            new_capacity = capa;
        }
        struct Node *new_ring_deque = (struct Node*)malloc(new_capacity * sizeof(struct Node));
        if (!new_ring_deque) {
            perror("new deque alloc err!\n");
            exit(EXIT_FAILURE);
        }
        if (self->front < self->rear) {
            memmove(
                new_ring_deque,
                self->elements + self->front,
                self->size * sizeof(struct Node)
            );
        } else {
            size_t front_to_deque_end = self->capacity - self->front;
            memmove(
                new_ring_deque,
                self->elements + self->front,
                front_to_deque_end * sizeof(struct Node)
            );
            memmove(
                new_ring_deque + front_to_deque_end,
                self->elements,
                (self->size - front_to_deque_end) * sizeof(struct Node)
            );
        }
        self->elements = new_ring_deque;
        self->capacity = new_capacity;
        self->front = 0;
        self->rear = self->size;        
    }
}

void push_back(struct RingDeque *self,struct Node *val) {
    if (is_deque_full(self)) {
        ensure_capacity(self,self->size + 1);
    }
    self->elements[self->rear] = *val;
    self->rear = (self->rear + 1) % self->capacity;
    self->size++;
}

void push_front(struct RingDeque *self,struct Node *val) {
    if (is_deque_full(self)) {
        ensure_capacity(self,self->size + 1);
    }
    self->front = (self->front - 1 + self->capacity) % self->capacity;
    self->elements[self->front] = *val;
    self->size++;
}

void pop_back(struct RingDeque *self) {
    if (is_deque_empty(self)) {
        perror("deque is empty pop_back err\n");
        exit(EXIT_FAILURE);
    }
    self->rear = (self->rear - 1 + self->capacity) % self->capacity;
    self->size--;
}

void pop_front(struct RingDeque *self) {
    if (is_deque_empty(self)) {
        perror("deque is empty pop_front err\n");
        exit(EXIT_FAILURE);
    }
    self->front = (self->front + 1) % self->capacity;
    self->size--;
}

struct Node* front(struct RingDeque *self) {
    if (is_deque_empty(self)) {
        perror("deque is empty get_front err\n");
        exit(EXIT_FAILURE);
    }
    return &self->elements[self->front];
}

struct Node* back(struct RingDeque *self) {
    if (is_deque_empty(self)) {
        perror("deque is empty get_rear err\n");
        exit(EXIT_FAILURE);
    }
    return &self->elements[(self->rear - 1 + self->capacity) % self->capacity];
}

void free_deque(struct RingDeque *self) {
    if (self->elements) {
        free(self->elements);
    }
    free(self);
}