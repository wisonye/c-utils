#include "vector.h"

#include <stdlib.h>
#include <string.h>

#ifdef ENABLE_DEBUG_LOG
#include <stdio.h>

#include "log.h"
#endif

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
Vector Vector_new() {
    Vector vec = malloc(sizeof(struct Vec));
    *vec = (struct Vec){
        .capacity = 0,
        .length = 0,
        .items = NULL,
    };
    return vec;
}

/*
 * Create an empty vector that ability to hold `capacity` elements
 */
Vector Vector_with_capacity(usize capacity, usize element_type_size) {
    Vector vec = malloc(sizeof(struct Vec));
    *vec = (struct Vec){
        .capacity = capacity,
        .length = 0,
        .items = malloc(element_type_size * capacity),
    };
    return vec;
}

/*
 * Push element to the end of the vector
 */
void Vector_push(Vector self, void *element, usize element_type_size) {
    // ensure the vector has enough space to save all elements;
    // capacity >= self->length + 1
    if (self->capacity < self->length + 1) {
        /* #ifdef ENABLE_DEBUG_LOG */
        /*         DEBUG_LOG(Vector, Vector_Push, */
        /*                   "Realloc needed, current capacity: %lu, length+1:
         * %lu, after " */
        /*                   "capacity: %lu", */
        /*                   self->capacity, self->length + 1, self->capacity *
         * 2); */
        /* #endif */
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
const usize Vector_len(const Vector self) { return self->length; }

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
 * Return the given index item, return `NULL` is not exists.
 */
const void *Vector_get(const Vector self, usize index,
                       usize element_type_size) {
    if (index < 0 || index > self->length - 1) return NULL;

    return self->items + (index * element_type_size);
}

/*
 * Join all elements and return a string
 */
const char *Vector_join(const Vector self, char *delemiter);

/*
 * Push element to the end of the vector
 */
void Vector_free(Vector self) {
    if (self == NULL) return;

    if (self->items != NULL) {
        void *ptr_to_free = self->items;
        self->items = NULL;
        free(ptr_to_free);
    }
    self->capacity = 0;
    self->length = 0;
    free(self);
}
