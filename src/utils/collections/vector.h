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
 * `Vec_push` calls `memcpy` to do a shallow copy on the given element instance.
 * If the element is a struct with its own heap-allocated member, that shallow
 * copy should be treated as taking ownership of all heap-allocated members.
 *
 * The shallow copied instance should reset all heap-allocated member's pointers
 * to `NULL` and pass an "Element heap-allocated destructor function pointer"
 * when creating a new "Vector".
 *
 * The exception is for `struct Str*` or `String`, as `Vector` does the
 * following efforts for `String` type:
 *
 * - Set `Str_free_buffer_only` to `self->element_destructor` as default element
 * destructor.
 *
 * - Call `Str_reset_to_empty_without_freeing_buffer` in `Vec_push`, so you don't
 * need to call `Str_reset_to_empty_without_freeing_buffer` on the passed in
 * `String` instance anymore.
 *
 * Plz check the [`Use
 * String`](https://github.com/wisonye/c-utils/blob/master/src/utils/collections/README.md#14-use-string)
 * example for more details.
 */
typedef void (*ElementHeapMemberDestructor)(void *ptr);

/*
 * Define smart `Vector` var that calls `Vec_free()` automatically when the
 * variable is out of the scope
 *
 * ```c
 * SMART_VECTOR(vec, int, NULL);
 * SMART_VECTOR_WITH_CAPACITY(usize_vec, usize, 10, NULL);
 *
 * (D) [ Vector ] > new - self pointer: 0x5472040, element_type_size: 4
 * (D) [ Vector ] > with_capacity - self pointer: 0x54730f0, element_type_size:
 * 8, capacity: 10, self->items: 0x5473160 (D) [ Vector ] > auto_free_vector -
 * out of scope with vector ptr: 0x54730f0, length: 0 (D) [ Vector ] >
 * auto_free_vector - out of scope with vector ptr: 0x5472040, length: 0
 * ```
 */
#define SMART_VECTOR(v_name, element_type, element_destructor) \
    __attribute__((cleanup(auto_free_vector))) Vector v_name = \
        Vec_new(TYPE_SIZE_FROM_TYPE(element_type),             \
                TYPE_NAME_TO_STRING(element_type), element_destructor)

#define SMART_VECTOR_WITH_CAPACITY(v_name, element_type, capacity,     \
                                   element_destructor)                 \
    __attribute__((cleanup(auto_free_vector))) Vector v_name =         \
        Vec_with_capacity(TYPE_SIZE_FROM_TYPE(element_type),           \
                          TYPE_NAME_TO_STRING(element_type), capacity, \
                          element_destructor)

/*
 * Create empty vector.
 * `Vec_push` calls `memcpy` to do a shallow copy on the given element instance.
 * If the element is a struct with its own heap-allocated member, that shallow
 * copy should be treated as taking ownership of all heap-allocated members.
 *
 * The shallow copied instance should reset all heap-allocated member's pointers
 * to `NULL` and pass an "Element heap-allocated destructor function pointer"
 * when creating a new "Vector".
 *
 * The exception is for `struct Str*` or `String`, as `Vector` does the
 * following efforts for `String` type:
 *
 * - Set `Str_free_buffer_only` to `self->element_destructor` as default element
 * destructor.
 *
 * - Call `Str_reset_to_empty_without_freeing_buffer` in `Vec_push`, so you don't
 * need to call `Str_reset_to_empty_without_freeing_buffer` on the passed in
 * `String` instance anymore.
 *
 * Plz check the [`Use
 * String`](https://github.com/wisonye/c-utils/blob/master/src/utils/collections/README.md#14-use-string)
 * example for more details.
 */
Vector Vec_new(usize element_type_size, char *element_type,
               ElementHeapMemberDestructor element_destructor);

/*
 * Create an empty vector that ability to hold `capacity` elements.
 *
 * `Vec_push` calls `memcpy` to do a shallow copy on the given element instance.
 * If the element is a struct with its own heap-allocated member, that shallow
 * copy should be treated as taking ownership of all heap-allocated members.
 *
 * The shallow copied instance should reset all heap-allocated member's pointers
 * to `NULL` and pass an "Element heap-allocated destructor function pointer"
 * when creating a new "Vector".
 *
 * The exception is for `struct Str*` or `String`, as `Vector` does the
 * following efforts for `String` type:
 *
 * - Set `Str_free_buffer_only` to `self->element_destructor` as default element
 * destructor.
 *
 * - Call `Str_reset_to_empty_without_freeing_buffer` in `Vec_push`, so you don't
 * need to call `Str_reset_to_empty_without_freeing_buffer` on the passed in
 * `String` instance anymore.
 *
 * Plz check the [`Use
 * String`](https://github.com/wisonye/c-utils/blob/master/src/utils/collections/README.md#14-use-string)
 * example for more details.
 */
Vector Vec_with_capacity(usize element_type_size, char *element_type,
                         usize capacity,
                         ElementHeapMemberDestructor element_destructor);

/*
 * Push element to the end of the vector:
 *
 * `Vec_push` calls `memcpy` to do a shallow copy on the given element instance.
 * If the element is a struct with its own heap-allocated member, that shallow
 * copy should be treated as taking ownership of all heap-allocated members.
 *
 * The shallow copied instance should reset all heap-allocated member's pointers
 * to `NULL` and pass an "Element heap-allocated destructor function pointer"
 * when creating a new "Vector".
 *
 * The exception is for `struct Str*` or `String`, as `Vector` does the
 * following efforts for `String` type:
 *
 * - Set `Str_free_buffer_only` to `self->element_destructor` as default element
 * destructor.
 *
 * - Call `Str_reset_to_empty_without_freeing_buffer` in `Vec_push`, so you don't
 * need to call `Str_reset_to_empty_without_freeing_buffer` on the passed in
 * `String` instance anymore.
 *
 * Plz check the [`Use
 * String`](https://github.com/wisonye/c-utils/blob/master/src/utils/collections/README.md#14-use-string)
 * example for more details.
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
