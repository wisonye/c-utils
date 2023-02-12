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
    char *_element_type;
    void *_items;
};

/*
 * Create empty vector
 */
Vector Vec_new(usize element_type_size, char *element_type) {
    Vector vec = malloc(sizeof(struct Vec));
    // usize element_type_size = sizeof(TYPE_NAME)

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector, new, "self pointer: %p, element_type_size: %llu", vec,
              element_type_size);
#endif

    *vec = (struct Vec){
        ._capacity = 0,
        ._length = 0,
        ._element_type_size = element_type_size,
        ._element_type = element_type,
        ._items = NULL,
    };
    return vec;
}

/*
 * Create an empty vector that ability to hold `capacity` elements
 */
Vector Vec_with_capacity(usize element_type_size, char *element_type,
                         usize capacity) {
    Vector vec = malloc(sizeof(struct Vec));

    *vec = (struct Vec){
        ._capacity = capacity,
        ._length = 0,
        ._element_type_size = element_type_size,
        ._element_type = element_type,
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

    /* #ifdef ENABLE_DEBUG_LOG */
    /*     PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Vec, self, sizeof(struct
     * Vec)); */
    /* #endif */

    self->_length += 1;

    /* #ifdef ENABLE_DEBUG_LOG */
    /*     PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Vec items, self->_items, */
    /*                                       self->_length *
     * self->_element_type_size); */
    /* #endif */
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
const String Vec_join(const Vector self, char *delemiter,
                      String (*custom_struct_desc)(void *ptr)) {
    if (self == NULL || self->_length <= 0) return Str_from_empty();

    /* usize capacity = self->_length * self->_element_type_size; */
    /* if (delemiter != NULL) { */
    /*     capacity += strlen(delemiter); */
    /* } */

    String result = Str_from_empty();

    for (usize index = 0; index < self->_length; index++) {
        // printf("\n>>> JOIN, element_type: %s", self->_element_type);
        //
        if (strcmp("_Bool", self->_element_type) == 0) {
            bool *ptr = self->_items;
            bool *current_ptr = ptr + index;
            Str_push_str(result, *current_ptr == true ? "True" : "False");
        } else if (strcmp("u8", self->_element_type) == 0 ||
                   strcmp("uint8_t", self->_element_type) == 0 ||
                   strcmp("unsigned char", self->_element_type) == 0) {
            // Max: 255
            char str_buffer[4] = {0};
            snprintf(str_buffer, 4, "%u",
                     *((unsigned char *)self->_items + index));
            Str_push_str(result, str_buffer);
        } else if (strcmp("u16", self->_element_type) == 0 ||
                   strcmp("uint16_t", self->_element_type) == 0 ||
                   strcmp("unsigned short int", self->_element_type) == 0) {
            // Max: 65535
            char str_buffer[6] = {0};
            snprintf(str_buffer, 6, "%u",
                     *((unsigned short int *)self->_items + index));
            Str_push_str(result, str_buffer);
        } else if (strcmp("u32", self->_element_type) == 0 ||
                   strcmp("uint32_t", self->_element_type) == 0 ||
                   strcmp("unsigned int", self->_element_type) == 0) {
            // Max: 4294967295
            char str_buffer[11] = {0};
            snprintf(str_buffer, 11, "%u",
                     *((unsigned int *)self->_items + index));
            Str_push_str(result, str_buffer);
        } else if (strcmp("u64", self->_element_type) == 0 ||
                   strcmp("usize", self->_element_type) == 0 ||
                   strcmp("size_t", self->_element_type) == 0 ||
                   strcmp("uint64_t", self->_element_type) == 0 ||
                   strcmp("unsigned long long int", self->_element_type) == 0 ||
                   strcmp("unsigned long int", self->_element_type) == 0) {
            // Max: 4294967295
            char str_buffer[21] = {0};
            snprintf(str_buffer, 21, "%llu",
                     *((unsigned long long int *)self->_items + index));
            Str_push_str(result, str_buffer);
        } else if (strcmp("i8", self->_element_type) == 0 ||
                   strcmp("int8_t", self->_element_type) == 0 ||
                   strcmp("signed char", self->_element_type) == 0 ||
                   strcmp("char", self->_element_type) == 0) {
            // Range: -127 ~ +128
            char str_buffer[5] = {0};
            snprintf(str_buffer, 5, "%i",
                     *((signed char *)self->_items + index));
            Str_push_str(result, str_buffer);
        } else if (strcmp("i16", self->_element_type) == 0 ||
                   strcmp("int16_t", self->_element_type) == 0 ||
                   strcmp("signed short int", self->_element_type) == 0 ||
                   strcmp("short int", self->_element_type) == 0) {
            // Range: −32768 ~ +32767
            char str_buffer[7] = {0};
            snprintf(str_buffer, 7, "%i", *((short int *)self->_items + index));
            Str_push_str(result, str_buffer);
        } else if (strcmp("i32", self->_element_type) == 0 ||
                   strcmp("int32_t", self->_element_type) == 0 ||
                   strcmp("int", self->_element_type) == 0 ||
                   strcmp("signed int", self->_element_type) == 0) {
            // Range: −2147483648 ~ +2147483647
            char str_buffer[12] = {0};
            snprintf(str_buffer, 12, "%i", *((int *)self->_items + index));
            Str_push_str(result, str_buffer);
        } else if (strcmp("i64", self->_element_type) == 0 ||
                   strcmp("int64_t", self->_element_type) == 0 ||
                   strcmp("long", self->_element_type) == 0 ||
                   strcmp("long int", self->_element_type) == 0 ||
                   strcmp("long long int", self->_element_type) == 0 ||
                   strcmp("signed long long int", self->_element_type) == 0 ||
                   strcmp("long long", self->_element_type) == 0) {
            // Range: -9223372036854775808 ~ +9223372036854775807
            char str_buffer[21] = {0};
            snprintf(str_buffer, 21, "%lli",
                     *((long long int *)self->_items + index));
            Str_push_str(result, str_buffer);
        } else if (strcmp("struct Str", self->_element_type) == 0) {
            // String
            String temp_str =
                (String)(self->_items + index * Str_struct_size());
            Str_push_str(result, Str_as_str(temp_str));
        } else {
            // Custom struct: Use provided callback to get back `String`
            if (custom_struct_desc != NULL) {
                SMART_STRING(temp_str) = custom_struct_desc(
                    self->_items + index * self->_element_type_size);
                Str_push_other(result, temp_str);
            }
        }

        if (delemiter != NULL && index + 1 < self->_length) {
            Str_push_str(result, delemiter);
        }
    }

    return result;
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
