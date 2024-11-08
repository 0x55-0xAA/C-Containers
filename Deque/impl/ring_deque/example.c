#include "deque.c"
#include <stdio.h>
#include "iterator.h"

int main(int argc, char const *argv[])
{
    struct RingDeque *deque = alloc_deque();
    int nums[] = {1,2,3,4,5,6,7,8,9,10};
    int numsSize = 10;
    for (int i = 0;i < numsSize;i++) {
        struct Node node = {.val_i = nums[i]};
        push_back(deque,&node);
    }
    printf("%d %d %d %d\n",front(deque)->val_i,back(deque)->val_i,deque->size,deque->capacity);
    pop_back(deque);
    pop_front(deque);
    printf("%d %d %d %d\n",front(deque)->val_i,back(deque)->val_i,deque->size,deque->capacity);
    struct Node node = {.val_i = 10001};
    push_front(deque,&node);
    printf("%d %d %d %d\n",front(deque)->val_i,back(deque)->val_i,deque->size,deque->capacity);
    printf("%d %d\n",DEQUE_BEGIN(deque)->val_i,DEQUE_END(deque)->val_i);
    struct Node *it = NULL;
    ITER(it,deque) {
        printf("%d ",it->val_i);
    }
    return 0;
}
