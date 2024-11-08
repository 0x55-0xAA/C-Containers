#ifndef ITERATOR_H
#define ITERATOR_H
#include "deque.h"

#define DEQUE_BEGIN(ptr)    \
    ((ptr)->elements + ((ptr)->front))
#define DEQUE_END(ptr)     \
    (((ptr)->elements) + ((ptr)->rear))

#define ITER(it,ptr)    \
    for ((it) = DEQUE_BEGIN((ptr)); \
    (it) != DEQUE_END((ptr)) && (it) != ((ptr)->elements + ((ptr)->capacity));     \
    (it) = ((it) == ((ptr)->elements + (ptr)->capacity - 1) ? (ptr)->elements : (it) + 1)  \
    )
       
#endif // ITERATOR_H