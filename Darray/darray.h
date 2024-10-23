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
        ((darray) ? darray_arr_to_meta(darray_ptr)->fn_dtr : NULL)
        
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

                     
#endif // DYNAMIC_ARRAY_H
