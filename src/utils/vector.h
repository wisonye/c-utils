#ifndef __UTILS_VECTOR_H__
#define __UTILS_VECTOR_H__

#include "data_types.h"

//
// Vector: Heap allocated dynamic array
//
typedef struct Vec *Vector;

//
// Iteractor
//
typedef struct {
    usize length;
    void *items;
} VectorIteractor;

//
//
//
void auto_free_vector(Vector *ptr);

/*
 * Define smart `Vector` var that calls `Vector_free()` automatically when the
 * variable is out of the scope
 *
 * ```c
 * SMART_VECTOR(empty_vec) = Vector_new();
 *
 * // (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5472040, length: 0
 * ```
 */
#define SMART_VECTOR(x) \
    __attribute__((cleanup(auto_free_vector))) Vector x

/*
 * Create empty vector
 */
Vector Vector_new();

/*
 * Create an empty vector that ability to hold `capacity` elements
 */
Vector Vector_with_capacity(usize capacity, usize element_type_size);

/*
 * Push element to the end of the vector
 */
void Vector_push(Vector self, void *element, usize element_type_size);

/*
 * Return the length
 */
const usize Vector_len(const Vector self);

/*
 * Return the capacity
 */
const usize Vector_capacity(const Vector self);

/*
 * Return the item iterator
 */
const VectorIteractor Vector_iter(const Vector self);

/*
 * Return the given index item, return `NULL` is not exists.
 */
const void *Vector_get(const Vector self, usize index, usize element_type_size);

/*
 * Join all elements and return a string
 */
const char *Vector_join(const Vector self, char *delemiter);

/*
 * Free allocated memory
 */
void Vector_free(Vector self);

#endif
