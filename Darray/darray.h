#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>     /* size_t */
#include <string.h>     /* elements operation */
#include <assert.h>     /* assert */

#ifndef darray_clib_free
#include <stdlib.h>
#define darray_clib_free free
#endif // darray_clib_free

#ifndef darray_clib_malloc
#include <stdlib.h>
#define darray_clib_malloc malloc
#endif // darray_clib_malloc

#ifndef darray_clib_calloc
#include <stdlib.h>
#define darray_clib_calloc calloc
#endif // darray_clib_calloc

#ifndef darray_clib_realloc
#include <stdlib.h>
#define darray_clib_realloc realloc
#endif // darray_clib_realloc


typedef void (*arr_ele_destructor)(void *elements);

struct darray_meta {
        size_t size;           /* current size */
        size_t capacity;        /* capacity */
        arr_ele_destructor fn_dtr;      /* destructor */
};

/**
 * @brief get the type of elements in user's darray
 * @param [type] the type of darray
 */
#define darray_elements_type_ptr(type) type *

/**
 * @brief define darray
 * @param [type] the type of darray
 */
#define darray(type) darray_elements_type_ptr(type)

/**
 * @brief define iterator of darray
 * @param [type] the type of darray
 */
#define darray_iter(type) darray_elements_type_ptr(type)

/**
 * @brief converts a user's darray pointer to a metadata pointer
 * @param [darray_ptr] user's darray pointer
 * @internal
 */
#define darray_arr_to_meta(darray_ptr)                                                                          \
        (&((struct darray_meta*)(darray_ptr))[-1])
/**
 * @brief converts a metadata pointer to a user's darray pointer
 * @param [darray_meta] metadata pointer
 * @internal
 */
#define darray_meta_to_arr(darray_meta_data)                                                                         \
        ((void*)&((struct darray_meta*)(darray_meta_data))[1])

/**
 * @brief set the size of new realloced darray,only in internal use
 * @param [darray_ptr] user's darray pointer
 * @param [__size] the size 
 * @internal
 */
#define darray_set_size(darray_ptr,__size)                                                                      \
        do {                                                                                                    \
                if (darray_ptr) {                                                                               \
                        darray_arr_to_meta(darray_ptr)->size = (__size);                                        \
                }                                                                                               \
        } while (0)

/**
 * @brief set the capacity of new realloced darray,only in internal use
 * @param [darray_ptr] user's darray pointer
 * @param [__capacity] the capacity
 */
#define darray_set_capacity(darray_ptr,__capacity)                                                              \
        do {                                                                                                    \
                if (darray_ptr) {                                                                               \
                        darray_arr_to_meta(darray_ptr)->capacity = (__capacity);                                \
                }                                                                                               \
        } while (0)

/**
 * @brief set the destructor function pointer of new realloced darray,only in internal use
 * @param [darray_ptr] user's darray pointer
 * @param [__dtr] the destructor
 * @internal
 */
#define darray_set_destructor(darray_ptr,__dtr)                                                                 \
        do {                                                                                                    \
                if (darray_ptr) {                                                                               \
                        darray_arr_to_meta(darray_ptr)->fn_dtr = (__dtr);                                       \
                }                                                                                               \
        } while (0)
                                                                  
/**
 * @brief make darray autogrowth and set allocator of darray,only in internal use
 * @param [darray] user's darray pointer
 * @param [count] new size of darray
 * @internal
 */
#define darray_grow(darray_ptr,count)                                                                           \
        do {                                                                                                    \
                const size_t darray_new_size__ = (count) * sizeof(*(darray_ptr)) + sizeof(struct darray_meta);  \
                if (darray_ptr) {                                                                               \
                        void *darray_old_ptr__ = darray_arr_to_meta(darray_ptr);                                \
                        void *darray_new_ptr__ = darray_clib_realloc(darray_old_ptr__,darray_new_size__);       \
                        assert(darray_new_ptr__);                                                               \
                        (darray_ptr) = darray_meta_to_arr(darray_new_ptr__);                                    \
                }else {                                                                                         \
                        void *darray_init_ptr__ = darray_clib_malloc(darray_new_size__);                        \
                        assert(darray_init_ptr__);                                                              \
                        (darray_ptr) = darray_meta_to_arr(darray_init_ptr__);                                   \
                        darray_set_size((darray_ptr),0);                                                        \
                        darray_set_destructor((darray_ptr),NULL);                                               \
                }                                                                                               \
                darray_set_capacity((darray_ptr),(count));                                                      \
        } while (0)
 
#define darray_init(darray_ptr,__capacity,__dtr)                                                                \
        do {                                                                                                    \
                if (!(darray_ptr)) {                                                                            \
                        darray_reserve((darray_ptr),(__capacity));                                              \
                        darray_set_destructor((darray_ptr),(__dtr));                                            \
                }                                                                                               \
        } while (0)

#define darray_free(darray_ptr)                                                                                 \
        do {                                                                                                    \
                if (darray_ptr) {                                                                               \
                        arr_ele_destructor arr_destructor__ = darray_elements_dtr(darray_ptr);                  \
                        void *meta_data__ = darray_arr_to_meta(darray_ptr);                                     \
                        if (arr_destructor__) {                                                                 \
                                size_t __i;                                                                     \
                                for (__i = 0;__i < darray_size(darray_ptr);__i++) {                             \
                                        arr_destructor__(&(darray_ptr)[__i]);                                   \
                                }                                                                               \
                        }                                                                                       \
                        darray_clib_free(meta_data__);                                                          \
                }                                                                                               \
        } while (0)             

/**
 * @brief get the capacity of darray
 * @param [darray_ptr] user's darray pointer
 * @return size_t
 */
#define darray_capacity(darray_ptr)                                                                             \
        ((darray_ptr) ? darray_arr_to_meta(darray_ptr)->capacity : (size_t)0)

/**
 * @brief get the size of darray
 * @param [darray_ptr] user's darray pointer
 * @return size_t
 */
#define darray_size(darray_ptr)                                                                                 \
        ((darray_ptr) ? darray_arr_to_meta(darray_ptr)->size : (size_t)0)

/**
 * @brief get the destructor of darray
 * @param [darray_ptr] user's darray pointer
 * @return function pointer
 */
#define darray_elements_dtr(darray_ptr)                                                                          \
        ((darray_ptr) ? darray_arr_to_meta(darray_ptr)->fn_dtr : NULL)
        
/**
 * @brief get whether darray is empty
 * @param [darray_ptr] user's darray pointer
 * @return bool
 */
#define darray_empty(darray_ptr)                                                                                \
        (darray_size(darray_ptr) == 0)

#define darray_shrink_to_fit(darray_ptr)                                                                        \
        do {                                                                                                    \
                if (darray_ptr) {                                                                               \
                        const size_t __size = darray_size(darray_ptr);                                          \
                        darray_grow((darray_ptr),__size);                                                       \
                }                                                                                               \
        } while (0)                                                     

#define darray_reserve(darray_ptr,new_cap)                                                                      \
        do {                                                                                                    \
                const size_t __darray_capacity = darray_capacity((darray_ptr));                                 \
                if (__darray_capacity < (new_cap)) {                                                            \
                        darray_grow(darray_ptr,(new_cap));                                                      \
                }                                                                                               \
        } while (0)

#define darray_clear(darray_ptr)                                                                                \
        do {                                                                                                    \
                if (darray_ptr) {                                                                               \
                        arr_ele_destructor arr_destructor__ = darray_elements_dtr(darray_ptr);                  \
                        size_t __i;                                                                             \
                        for (__i = 0;__i < darray_size(darray_ptr);__i++) {                                     \
                                arr_ele_destructor(&(darray_ptr)[__i]);                                         \
                        }                                                                                       \
                        darray_set_size((darray_ptr),0);                                                        \
                }                                                                                               \
        } while (0)

#define darray_erase(darray_ptr,index)                                                                          \
        do {                                                                                                    \
                if (darray_ptr) {                                                                               \
                        const size_t __size = darray_size(darray_ptr);                                          \
                        if ((index) < __size) {                                                                 \
                                arr_ele_destructor arr_destructor__ = darray_elements_dtr(darray_ptr);          \
                                if (arr_destructor__) {                                                         \
                                        arr_destrcutor__(&(darray_ptr)[(index)]);                               \
                                }                                                                               \
                                memmove((darray_ptr) + (index),                                                 \
                                (darray_ptr) + (index) + 1,                                                     \
                                sizeof(*(darray_ptr)) * (__size - 1 - (index)));                                \
                                darray_set_size(__size - 1);                                                    \
                        }                                                                                       \
                }                                                                                               \
        } while (0)

#define darray_calculate_growth(size)                                                                           \
        ((size) ? ((size) << 1) : 1)                                                                            \

#define darray_insert(darray_ptr,position,val)                                                                  \
        do {                                                                                                    \
                size_t __capacity = darray_capacity(darray_ptr);                                                \
                if(__capacity <= darray_size(darray_ptr)) {                                                     \
                        darray_grow(darray_ptr,darray_calculate_growth(__capacity));                            \
                }                                                                                               \
                if ((position) < darray_size(darray_ptr)) {                                                     \
                        memmove((darray_ptr) + (position) + 1,                                                  \
                        (darray_ptr) + (position),                                                              \
                        sizeof(*(darray_ptr)) * ((darray_size(darray_ptr)) - (position)));                      \
                }                                                                                               \
                (darray_ptr)[(position)] = (val);                                                               \
                darray_set_size((darray_ptr),darray_size(darray_ptr) + 1);                                      \
        } while (0)

#define darray_push_back(darray_ptr,val)                                                                        \
        do {                                                                                                    \
                size_t __capacity = darray_capacity(darray_ptr);                                                \
                if (__capacity <= darray_size(darray_ptr)) {                                                    \
                        darray_grow(darray_ptr,darray_calculate_growth(__capacity));                            \
                }                                                                                               \
                (darray_ptr)[darray_size(darray_ptr)] = (val);                                                  \
                darray_set_size((darray_ptr),darray_size(darray_ptr) + 1);                                      \
        } while(0)


#define darray_pop_back(darray_ptr)                                                                             \
        do {                                                                                                    \
                arr_ele_destructor arr_destructor__ = darray_elements_dtr(darray_ptr);                          \
                if (arr_destructor__) {                                                                               \
                        arr_destructor__(&(darray_ptr)[darray_size(darray_ptr) - 1]);                           \
                }                                                                                               \
                darray_set_size((darray_ptr),darray_size(darray_ptr) - 1);                                      \
        } while (0)

#define darray_swap(darray_ptr,__other,type)                                                                    \
        do {                                                                                                    \
                if (darray_ptr && __other) {                                                                    \
                        darray_elements_type_ptr(type) __temp = (darray_ptr);                                   \
                        (darray_ptr) = (__other);                                                               \
                        (__other) = (__temp);                                                                   \
                }                                                                                               \
        } while(0)

#define darray_copy(darray_ptr_dest,darray_ptr_src)                                                             \
        do {                                                                                                    \
                if (darray_ptr_src) {                                                                           \
                        darray_grow(darray_ptr_dest,darray_size(darray_ptr_src));                               \
                        darray_set_size(darray_ptr_dest,darray_size(darray_ptr_src));                           \
                        memmove((darray_ptr_dest),                                                              \
                        (darray_ptr_src),                                                                       \
                        sizeof(*(darray_ptr_from)) * darray_size(darray_ptr_src));                              \
                }                                                                                               \
        } while(0)

#define darray_at(darray_ptr,index)                                                                             \
        ((darray_ptr) ? (((int)(index) < 0 || (size_t)(index) >= darray_size(darray_ptr)) ? NULL : &(darray_ptr)[(index)]):NULL)      \

#define darray_front(darray_ptr)                                                                                \
        ((darray_ptr) ? (darray_size(darray_ptr) > 0 ? darray_at(darray_ptr,0) : NULL) : NULL)                  \

#define darray_back(darray_ptr)                                                                                 \
        ((darray_ptr) ? (darray_size(darray_ptr) > 0 ? darray_at(darray_ptr,darray_size(darray_ptr) - 1) : NULL) : NULL) \

#endif // DYNAMIC_ARRAY_H
