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

/*
 * Create empty vector
 */
Vector Vector_from_empty();

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
const usize Vector_length(const Vector self);

/*
 * Return the item iterator
 */
const VectorIteractor Vector_iter(const Vector self);

/*
 * Return the capacity
 */
const usize Vector_capacity(const Vector self);

/*
 * Join all elements and return a string
 */
const char *Vector_join(const Vector self, char *delemiter);

/*
 * Push element to the end of the vector
 */
void Vector_free(Vector self);

#endif
