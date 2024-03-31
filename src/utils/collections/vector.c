#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef ENABLE_DEBUG_LOG
    #include <stdio.h>

    #include "../heap_string.h"
    #include "../log.h"
    #include "../memory.h"
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
    ElementHeapMemberDestructor element_destructor;
};

/*
 *
 */
bool is_string_type(const char *type) {
    return ((strcmp(type, "struct HeapString") == 0) ||
            (strcmp(type, "String") == 0));
}

/*
 *
 */
Vector Vec_new(usize element_type_size,
               char *element_type,
               ElementHeapMemberDestructor element_destructor) {
    Vector vec = malloc(sizeof(struct Vec));
    // usize element_type_size = sizeof(TYPE_NAME)

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector,
              new,
              "self pointer: %p, element_type_size: %llu",
              vec,
              element_type_size);
#endif

    *vec = (struct Vec){
        ._capacity          = 0,
        ._length            = 0,
        ._element_type_size = element_type_size,
        ._element_type      = element_type,
        ._items             = NULL,
        .element_destructor = is_string_type(element_type)
                                  ? (void (*)(void *))HS_free_buffer_only
                                  : element_destructor,
    };
    return vec;
}

/*
 *
 */
Vector Vec_with_capacity(usize element_type_size,
                         char *element_type,
                         usize capacity,
                         ElementHeapMemberDestructor element_destructor) {
    Vector vec = malloc(sizeof(struct Vec));

    *vec = (struct Vec){
        ._capacity          = capacity,
        ._length            = 0,
        ._element_type_size = element_type_size,
        ._element_type      = element_type,
        ._items             = malloc(element_type_size * capacity),
        .element_destructor = is_string_type(element_type)
                                  ? (void (*)(void *))HS_free_buffer_only
                                  : element_destructor,
    };

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector,
              with_capacity,
              "self pointer: %p, element_type_size: %llu, capacity: %lu, "
              "self->items: %p",
              vec,
              element_type_size,
              capacity,
              vec->_items);
#endif
    return vec;
}

/*
 *
 */
void Vec_push(Vector self, void *element) {
    // ensure the vector has enough space to save all elements;
    // capacity >= self->length + 1
    if (self->_capacity < self->_length + 1) {
        usize old_capacity = self->_capacity;
        self->_capacity    = (self->_capacity == 0) ? 1 : self->_capacity * 2;
        self->_items =
            realloc(self->_items, self->_element_type_size * self->_capacity);

#ifdef ENABLE_DEBUG_LOG
        DEBUG_LOG(Vector,
                  Vec_Push,
                  "Realloc needed, current capacity: %lu, length+1: %lu, after "
                  "capacity: %lu, self->item: %p",
                  old_capacity,
                  self->_length + 1,
                  self->_capacity,
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
    memcpy((u8 *)self->_items + self->_element_type_size * self->_length,
           element,
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

    //
    // Handly reset for `String` instance:
    //
    // Reset the `String` to empty, then you don't need to call
    // `HS_reset_to_empty_without_freeing_buffer` manually!!!
    //
    if (is_string_type(self->_element_type)) {
        ((struct HeapString *)element)->_len      = 0;
        ((struct HeapString *)element)->_capacity = 0;
        ((struct HeapString *)element)->_buffer   = 0;
    }
}

/*
 *
 */
usize Vec_len(const Vector self) {
    return self == NULL ? 0 : self->_length;
}

/*
 *
 */
usize Vec_capacity(Vector self) {
    return self == NULL ? 0 : self->_capacity;
}

/*
 *
 */
const VectorIteractor Vec_iter(const Vector self) {
    return self == NULL ? (VectorIteractor){.length = 0, .items = NULL}
                        : (VectorIteractor){.length = self->_length,
                                            .items  = self->_items};
}

/*
 *
 */
const void *Vec_get(const Vector self, usize index) {
    if (index > self->_length - 1) return NULL;

    return (u8 *)self->_items + (index * self->_element_type_size);
}

/*
 *
 */
String Vec_join(const Vector self,
                char *delemiter,
                String (*custom_struct_desc)(void *ptr)) {
    if (self == NULL || self->_length <= 0) return HS_from_empty();

    //
    // Calaculte the pre-allocated memory to hold all element + delemiter
    // in a `String`.
    //
    usize capacity = 0;
    if (strcmp("_Bool", self->_element_type) == 0) {
        // `True` or `False` (5 chars)
        capacity = self->_length * 5 + 1;
    } else {
        // For all `non _Bool` and `non-custom-struct`data type, actually it's
        // impossible to calaculte the actual size without another for loop.
        // So `capaiacty` below just a `better than nothing` solution:)
        capacity = self->_length * self->_element_type_size + 1;
    }

    if (delemiter != NULL) {
        capacity += strlen(delemiter) * (self->_length - 1);
    }

#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector,
              Vec_join,
              "element_type: %s, element_size: %lu, delimiter size: %lu, "
              "length: %lu, "
              "capacity: %lu",
              self->_element_type,
              self->_element_type_size,
              delemiter == NULL ? 0 : strlen(delemiter),
              self->_length,
              capacity);
#endif

    String result = HS_from_empty_with_capacity(capacity);

    for (usize index = 0; index < self->_length; index++) {
        // printf("\n>>> JOIN, element_type: %s", self->_element_type);
        //
        if (strcmp("_Bool", self->_element_type) == 0) {
            bool *ptr         = self->_items;
            bool *current_ptr = ptr + index;
            HS_push_str(result, *current_ptr == true ? "True" : "False");
        } else if (strcmp("u8", self->_element_type) == 0 ||
                   strcmp("uint8_t", self->_element_type) == 0 ||
                   strcmp("unsigned char", self->_element_type) == 0) {
            // Max: 255
            char str_buffer[4] = {0};
            snprintf(str_buffer,
                     4,
                     "%u",
                     *((unsigned char *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("u16", self->_element_type) == 0 ||
                   strcmp("uint16_t", self->_element_type) == 0 ||
                   strcmp("unsigned short int", self->_element_type) == 0) {
            // Max: 65535
            char str_buffer[6] = {0};
            snprintf(str_buffer,
                     6,
                     "%u",
                     *((unsigned short int *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("u32", self->_element_type) == 0 ||
                   strcmp("uint32_t", self->_element_type) == 0 ||
                   strcmp("unsigned int", self->_element_type) == 0) {
            // Max: 4294967295
            char str_buffer[11] = {0};
            snprintf(str_buffer,
                     11,
                     "%u",
                     *((unsigned int *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("u64", self->_element_type) == 0 ||
                   strcmp("usize", self->_element_type) == 0 ||
                   strcmp("size_t", self->_element_type) == 0 ||
                   strcmp("uint64_t", self->_element_type) == 0 ||
                   strcmp("unsigned long long int", self->_element_type) == 0 ||
                   strcmp("unsigned long int", self->_element_type) == 0) {
            // Max: 4294967295
            char str_buffer[21] = {0};
            snprintf(str_buffer,
                     21,
                     "%llu",
                     *((unsigned long long int *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("i8", self->_element_type) == 0 ||
                   strcmp("int8_t", self->_element_type) == 0 ||
                   strcmp("signed char", self->_element_type) == 0 ||
                   strcmp("char", self->_element_type) == 0) {
            // Range: -127 ~ +128
            char str_buffer[5] = {0};
            snprintf(str_buffer,
                     5,
                     "%i",
                     *((signed char *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("i16", self->_element_type) == 0 ||
                   strcmp("int16_t", self->_element_type) == 0 ||
                   strcmp("signed short int", self->_element_type) == 0 ||
                   strcmp("short int", self->_element_type) == 0) {
            // Range: −32768 ~ +32767
            char str_buffer[7] = {0};
            snprintf(str_buffer, 7, "%i", *((short int *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("i32", self->_element_type) == 0 ||
                   strcmp("int32_t", self->_element_type) == 0 ||
                   strcmp("int", self->_element_type) == 0 ||
                   strcmp("signed int", self->_element_type) == 0) {
            // Range: −2147483648 ~ +2147483647
            char str_buffer[12] = {0};
            snprintf(str_buffer, 12, "%i", *((int *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("i64", self->_element_type) == 0 ||
                   strcmp("int64_t", self->_element_type) == 0 ||
                   strcmp("long", self->_element_type) == 0 ||
                   strcmp("long int", self->_element_type) == 0 ||
                   strcmp("long long int", self->_element_type) == 0 ||
                   strcmp("signed long long int", self->_element_type) == 0 ||
                   strcmp("long long", self->_element_type) == 0) {
            // Range: -9223372036854775808 ~ +9223372036854775807
            char str_buffer[21] = {0};
            snprintf(str_buffer,
                     21,
                     "%lli",
                     *((long long int *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("double", self->_element_type) == 0) {
            char str_buffer[25] = {0};
            snprintf(str_buffer, 25, "%f", *((double *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("float", self->_element_type) == 0) {
            char str_buffer[25] = {0};
            snprintf(str_buffer, 25, "%f", *((float *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if (strcmp("long double", self->_element_type) == 0) {
            char str_buffer[25] = {0};
            snprintf(str_buffer,
                     25,
                     "%Lf",
                     *((long double *)self->_items + index));
            HS_push_str(result, str_buffer);
        } else if ((strcmp("struct HeapString", self->_element_type) == 0) ||
                   (strcmp("String", self->_element_type) == 0)) {
            // String
            String temp_str =
                (String)((u8 *)self->_items + index * HS_struct_size());
            HS_push_str(result, HS_as_str(temp_str));
        } else {
            // Custom struct: Use provided callback to get back `String`
            if (custom_struct_desc != NULL) {
                defer_string(temp_str) = custom_struct_desc(
                    (u8 *)self->_items + index * self->_element_type_size);
                HS_push_other(result, temp_str);
            }
        }

        if (delemiter != NULL && index + 1 < self->_length) {
            HS_push_str(result, delemiter);
        }
    }

    return result;
}

/*
 *
 */
void Vec_free(Vector self) {
    if (self == NULL) return;

    if (self->_items != NULL) {
        //
        // Call element destructor if exists
        //
        if (self->element_destructor != NULL) {
            for (usize index = 0; index < self->_length; index++) {
                void *element_ptr =
                    (u8 *)self->_items + index * self->_element_type_size;
                /* #ifdef ENABLE_DEBUG_LOG */
                /*                 DEBUG_LOG(Vector, free, "element ptr: %p",
                 * element_ptr); */
                /* #endif */
                self->element_destructor(element_ptr);
            }
        }

        //
        // Free `items` meory
        //
        void *ptr_to_free = self->_items;
        self->_items      = NULL;
        /* #ifdef ENABLE_DEBUG_LOG */
        /*         DEBUG_LOG(Vector, free, "ptr_to_free: %p", ptr_to_free); */
        /* #endif */
        free(ptr_to_free);
    }
    self->_capacity = 0;
    self->_length   = 0;
    free(self);
}

/*
 *
 */
void auto_free_vector(Vector *ptr) {
#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(Vector,
              auto_free_vector,
              "out of scope with vector ptr: %p, length: %lu",
              *ptr,
              Vec_len(*ptr));
#endif
    Vec_free(*ptr);
}
