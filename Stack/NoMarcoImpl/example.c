#include "stack.h"
#include "stack.c"
#include <stdio.h> /* printf */

int main(int argc, char const *argv[])
{
    int a[] = {1,3,4,55,3,2,4,6};
    struct Stack *stack = alloc_stack();
    struct Node nodes[8];
    for (int i = 0;i < 8;i++) {
        nodes[i].val_i = a[i];
        push_back(stack,&nodes[i]);
    }
    while (!is_stack_empty(stack)) {
        printf("%d ",get_top(stack)->val_i);
        pop_back(stack);
    }
    free_stack(stack);
    return 0;
}
