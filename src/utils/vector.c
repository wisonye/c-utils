#include "vector.h"

#include <stdlib.h>
#include <string.h>

//
// Vector: Heap allocated dynamic array
//
struct Vec {
    usize capacity;
    usize length;
    void *items;
};

/*
 * Create empty vector
 */
Vector Vector_from_empty() {
    Vector vec = malloc(sizeof(Vector));
    vec->capacity = 0;
    vec->length = 0;
    vec->items = NULL;
    return vec;
}

/*
 * Push element to the end of the vector
 */
void Vector_push(Vector self, void *element, usize element_type_size) {
    // ensure the vector has enough space to save all elements;
    // capacity >= self->length + 1
    if (self->capacity < self->length + 1) {
        self->capacity = (self->capacity == 0) ? 1 : self->capacity * 2;
        self->items = realloc(self->items, element_type_size * self->capacity);
    }

    //
    // Move the `self->item` (first element pointer) to the last element
    // position and then dereference it, assign the value to it.
    //
    // Because `self->` is `void *` (without any type information), that's why
    // you can't assign value like this:
    //
    // *(self->items + element_type_size * self->length) = *element;
    //
    // C compile doesn't know how much bytes need to be written.
    //
    // Instead, you have to use `memcpy` to deal `void *` data assignment.
    //
    memcpy(self->items + element_type_size * self->length, element,
           element_type_size);

    self->length += 1;
}

/*
 * Return the length
 */
const usize Vector_length(const Vector self) { return self->length; }

/*
 * Return the capacity
 */
const usize Vector_capacity(Vector self) { return self->capacity; }

/*
 * Return the item iterator
 */
const VectorIteractor Vector_iter(const Vector self) {
    return (VectorIteractor){.length = self->length, .items = self->items};
}

/*
 * Join all elements and return a string
 */
const char *Vector_join(const Vector self, char *delemiter);

/*
 * Push element to the end of the vector
 */
void Vector_free(Vector self) {
    free(self);
    self->capacity = 0;
    self->length = 0;
    self->items = NULL;
}
