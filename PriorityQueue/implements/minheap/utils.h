#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

#define SWAP(a,b,size)  \
        do {            \
            size_t __size = (size);     \
            char *__a = (a),*__b = (b);     \
            do {                            \
                char _tmp = *__a;         \
                *__a++ =  *__b;             \
                *__b++ = _tmp;              \
            } while (--__size > 0);          \
        } while (0)

#endif