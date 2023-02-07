#include "vector.h"

#include <stdlib.h>
#include <string.h>

#ifdef ENABLE_DEBUG_LOG
#include <stdio.h>

#include "log.h"
#include "memory.h"
#include "string.h"
#endif

/*
 * Vector: Heap allocated dynamic array
 */
struct Vec {
    usize capacity;
    usize length;
    usize element_type_size;
    void *items;
};

/*
 * Create empty vector
 */
Vector Vec_new(usize element_type_size) {
    Vector vec = malloc(sizeof(struct Vec));

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector, new, "self pointer: %p, element_type_size: %llu", vec,
              element_type_size);
#endif

    *vec = (struct Vec){
        .capacity = 0,
        .length = 0,
        .element_type_size = element_type_size,
        .items = NULL,
    };
    return vec;
}

/*
 * Create an empty vector that ability to hold `capacity` elements
 */
Vector Vec_with_capacity(usize capacity, usize element_type_size) {
    Vector vec = malloc(sizeof(struct Vec));

    *vec = (struct Vec){
        .capacity = capacity,
        .length = 0,
        .element_type_size = element_type_size,
        .items = malloc(element_type_size * capacity),
    };

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector, with_capacity,
              "self pointer: %p, element_type_size: %llu, capacity: %lu, "
              "self->items: %p",
              vec, element_type_size, capacity, vec->items);
#endif
    return vec;
}

/*
 * Push element to the end of the vector
 *
 * Vector executes a shallow copy which means doesn't copy the internal
 * heap-allocated content!!!
 */
void Vec_push(Vector self, void *element) {
    // ensure the vector has enough space to save all elements;
    // capacity >= self->length + 1
    if (self->capacity < self->length + 1) {
        usize old_capacity = self->capacity;
        self->capacity = (self->capacity == 0) ? 1 : self->capacity * 2;
        self->items =
            realloc(self->items, self->element_type_size * self->capacity);

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(Vector, Vec_Push,
                  "Realloc needed, current capacity: %lu, length+1: %lu, after "
                  "capacity: %lu, self->item: %p",
                  old_capacity, self->length + 1, self->capacity, self->items);
#endif
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
    memcpy(self->items + self->element_type_size * self->length, element,
           self->element_type_size);

#ifdef ENABLE_DEBUG_LOG
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Vec, self, sizeof(struct Vec));
#endif

    self->length += 1;

#ifdef ENABLE_DEBUG_LOG
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Vec items, self->items,
                                      self->length * self->element_type_size);
#endif
}

/*
 * Return the length
 */
const usize Vec_len(const Vector self) { return self->length; }

/*
 * Return the capacity
 */
const usize Vec_capacity(Vector self) { return self->capacity; }

/*
 * Return the item iterator
 */
const VectorIteractor Vec_iter(const Vector self) {
    return (VectorIteractor){.length = self->length, .items = self->items};
}

/*
 * Return the given index item, return `NULL` is not exists.
 */
const void *Vec_get(const Vector self, usize index) {
    if (index < 0 || index > self->length - 1) return NULL;

    return self->items + (index * self->element_type_size);
}

/*
 * Join all elements and return a string
 */
const char *Vec_join(const Vector self, char *delemiter);

/*
 * Free allocated memory
 */
void Vec_free(Vector self) {
    if (self == NULL) return;

    if (self->items != NULL) {
        //
        // Free `items` meory
        //
        void *ptr_to_free = self->items;
        self->items = NULL;
        free(ptr_to_free);
    }
    self->capacity = 0;
    self->length = 0;
    free(self);
}

/*
 * Auto free vector call
 */
void auto_free_vector(Vector *ptr) {
#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector, auto_free_vector,
              "out of scope with vector ptr: %p, length: %lu", *ptr,
              Vec_len(*ptr));
#endif
    Vec_free(*ptr);
}
