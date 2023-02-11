#ifndef __UTILS_VECTOR_H__
#define __UTILS_VECTOR_H__

#include "../data_types.h"

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
 * SMART_VECTOR(empty_vec) = Vec_new();
 *
 * // (D) [ Vector ] > auto_free_vector - out of scope with vector ptr:
 * 0x5472040, length: 0
 * ```
 */
#define SMART_VECTOR(x) __attribute__((cleanup(auto_free_vector))) Vector x

/*
 * Create empty vector
 */
Vector Vec_new(usize element_type_size);

/*
 * Create an empty vector that ability to hold `capacity` elements
 */
Vector Vec_with_capacity(usize capacity, usize element_type_size);

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
const char *Vec_join(const Vector self, char *delemiter);

/*
 * Free allocated memory
 */
void Vec_free(Vector self);

#endif
