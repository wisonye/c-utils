#ifndef __UTILS_VECTOR_H__
#define __UTILS_VECTOR_H__

#include "../data_types.h"
#include "../string.h"

/*
 * Vector: Heap allocated dynamic array
 */
typedef struct Vec *Vector;

/*
 * Iteractor
 */
typedef struct {
    usize length;
    void *items;
} VectorIteractor;

/*
 *
 */
void auto_free_vector(Vector *ptr);

/*
 * Define smart `Vector` var that calls `Vec_free()` automatically when the
 * variable is out of the scope
 *
 * ```c
 * SMART_VECTOR(vec, int);
 * SMART_VECTOR_WITH_CAPACITY(usize_vec, usize, 10);
 *
 * (D) [ Vector ] > new - self pointer: 0x5472040, element_type_size: 4
 * (D) [ Vector ] > with_capacity - self pointer: 0x54730f0, element_type_size:
 * 8, capacity: 10, self->items: 0x5473160 (D) [ Vector ] > auto_free_vector -
 * out of scope with vector ptr: 0x54730f0, length: 0 (D) [ Vector ] >
 * auto_free_vector - out of scope with vector ptr: 0x5472040, length: 0
 * ```
 */
#define SMART_VECTOR(v_name, element_type)                              \
    __attribute__((cleanup(auto_free_vector))) Vector v_name = Vec_new( \
        TYPE_SIZE_FROM_TYPE(element_type), TYPE_NAME_TO_STRING(element_type))

#define SMART_VECTOR_WITH_CAPACITY(v_name, element_type, capacity) \
    __attribute__((cleanup(auto_free_vector))) Vector v_name =     \
        Vec_with_capacity(TYPE_SIZE_FROM_TYPE(element_type),       \
                          TYPE_NAME_TO_STRING(element_type), capacity)

/*
 * Create empty vector
 */
Vector Vec_new(usize element_type_size, char *element_type);

/*
 * Create an empty vector that ability to hold `capacity` elements
 */
Vector Vec_with_capacity(usize element_type_size, char *element_type,
                         usize capacity);

/*
 * Push element to the end of the vector:
 *
 * Vector executes a shallow copy which means doesn't copy the internal
 * heap-allocated content!!!
 */
void Vec_push(Vector self, void *element);

/*
 * Return the length
 */
const usize Vec_len(const Vector self);

/*
 * Return the capacity
 */
const usize Vec_capacity(const Vector self);

/*
 * Return the item iterator
 */
const VectorIteractor Vec_iter(const Vector self);

/*
 * Return the given index item, return `NULL` is not exists.
 */
const void *Vec_get(const Vector self, usize index);

/*
 * Join all elements and return a string
 */
const String Vec_join(const Vector self, char *delemiter,
                      String (*custom_struct_desc)(void *ptr));

/*
 * Free allocated memory
 */
void Vec_free(Vector self);

#endif
