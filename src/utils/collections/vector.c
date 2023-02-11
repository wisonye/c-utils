#include "vector.h"

#include <stdlib.h>
#include <string.h>

#ifdef ENABLE_DEBUG_LOG
#include <stdio.h>

#include "../log.h"
#include "../memory.h"
#include "../string.h"
#endif

/*
 * Vector: Heap allocated dynamic array
 */
struct Vec {
    usize _capacity;
    usize _length;
    usize _element_type_size;
    void *_items;
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
        ._capacity = 0,
        ._length = 0,
        ._element_type_size = element_type_size,
        ._items = NULL,
    };
    return vec;
}

/*
 * Create an empty vector that ability to hold `capacity` elements
 */
Vector Vec_with_capacity(usize capacity, usize element_type_size) {
    Vector vec = malloc(sizeof(struct Vec));

    *vec = (struct Vec){
        ._capacity = capacity,
        ._length = 0,
        ._element_type_size = element_type_size,
        ._items = malloc(element_type_size * capacity),
    };

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector, with_capacity,
              "self pointer: %p, element_type_size: %llu, capacity: %lu, "
              "self->items: %p",
              vec, element_type_size, capacity, vec->_items);
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
    if (self->_capacity < self->_length + 1) {
        usize old_capacity = self->_capacity;
        self->_capacity = (self->_capacity == 0) ? 1 : self->_capacity * 2;
        self->_items =
            realloc(self->_items, self->_element_type_size * self->_capacity);

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(Vector, Vec_Push,
                  "Realloc needed, current capacity: %lu, length+1: %lu, after "
                  "capacity: %lu, self->item: %p",
                  old_capacity, self->_length + 1, self->_capacity,
                  self->_items);
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
    memcpy(self->_items + self->_element_type_size * self->_length, element,
           self->_element_type_size);

#ifdef ENABLE_DEBUG_LOG
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Vec, self, sizeof(struct Vec));
#endif

    self->_length += 1;

#ifdef ENABLE_DEBUG_LOG
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Vec items, self->_items,
                                      self->_length * self->_element_type_size);
#endif
}

/*
 * Return the length
 */
const usize Vec_len(const Vector self) { return self->_length; }

/*
 * Return the capacity
 */
const usize Vec_capacity(Vector self) { return self->_capacity; }

/*
 * Return the item iterator
 */
const VectorIteractor Vec_iter(const Vector self) {
    return (VectorIteractor){.length = self->_length, .items = self->_items};
}

/*
 * Return the given index item, return `NULL` is not exists.
 */
const void *Vec_get(const Vector self, usize index) {
    if (index < 0 || index > self->_length - 1) return NULL;

    return self->_items + (index * self->_element_type_size);
}

/*
 * Join all elements and return a string
 */
const String Vec_join(const Vector self, char *delemiter) {
    if (self == NULL || self->_length <= 0) return Str_from_empty();

    /* usize capacity = self->_length * self->_element_type_size; */
    /* if (delemiter != NULL) { */
    /*     capacity += strlen(delemiter); */
    /* } */

    /* String result = Str_from_empty(); */

    /* char *data_type = TYPE_NAME(self->_items); */
    /* for (usize index=0; index<self->_length; index++) { */

    /* } */

    /* return result; */
    return Str_from_str("Unimplemented");
}

/*
 * Free allocated memory
 */
void Vec_free(Vector self) {
    if (self == NULL) return;

    if (self->_items != NULL) {
        //
        // Free `items` meory
        //
        void *ptr_to_free = self->_items;
        self->_items = NULL;
        free(ptr_to_free);
    }
    self->_capacity = 0;
    self->_length = 0;
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
