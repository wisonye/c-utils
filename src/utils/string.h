#ifndef __UTILS_STRING_H__
#define __UTILS_STRING_H__

#include <stdbool.h>

#include "data_types.h"

//
// Heap allocated string
//
struct Str {
    usize _len;
    char *_buffer;
};

//
// Heap allocated string
//
typedef struct Str *String;

//
// `String` is an opaque pointer which uses to hide the `struct Str` detail,
// which means `struct Str` doesn't exists in the outside world. If you want
// to get back `sizeof(struct Str)` for some reasons, this function is the
// anwser.
//
const usize Str_struct_size();

//
//
//
void auto_free_string(String *ptr);

/*
 * Define smart `String` var that calls `Str_free()` automatically when the
 * variable is out of the scope
 *
 * ```c
 * SMART_STRING(src_str) = Str_from_str("Hey:)");
 *
 * // (D) [ String ] > auto_free_string - out of scope with string ptr:
 * 0x5473850, as_str: Hey:)
 * ```
 */
#define SMART_STRING(x) __attribute__((cleanup(auto_free_string))) String x

/*
 * Init empty `struct Str`
 */
void Str_init(String self);

/*
 * Create from empty
 */
String Str_from_empty();

/*
 * Create from `char[]`
 */
String Str_from_arr(const char arr[]);

/*
 * Create from `char*`
 */
String Str_from_str(const char *str);

/*
 * Clone from the given `String` instance but don't touch the heap-allocated
 * memory it owned
 */
String Str_clone_from(const String other);

/*
 * Move from the given `String` instance and move ownership of the
 * heap-allocated memory to the newly created `String` instance
 */
String Str_move_from(String other);

/*
 * Push other `String *` at the end
 */
void Str_push_other(String self, String other);

// /*
//  * Push from the given `String` instance and copy `other->_buffer`
//  */
// void Str_push_other_copy(String self, const String other);

/*
 * Push the given `char *` at the end
 */
void Str_push_str(String self, const char *str_to_push);

/*
 * Insert `String *` to the beginning
 */
void Str_insert_other_to_begin(String self, const String other);

/*
 * Insert `char *` to the beginning
 */
void Str_insert_str_to_begin(String self, const char *str_to_insert);

/*
 * Insert `char *` at the given index
 */
void Str_insert_at_index(String self, const char *str_to_insert,
                         usize index_to_insert);

/*
 * Get back string length
 */
const usize Str_length(const String self);

/*
 * Get back `char *`
 */
const char *Str_as_str(const String self);

/*
 * Find the given `char *` index, return `-1` if not found.
 */
const long Str_index_of(const String self, const char *str_to_find);

/*
 * Find the given `char *` (case sensitive) index, return `-1` if not found.
 */
const long Str_index_of_case_sensitive(const String self,
                                       const char *str_to_find);

/*
 * Check whether contain the given `char *` or not
 */
const bool Str_contains(const String self, char *str_to_check);

/*
 * Reset  to empty string
 */
void Str_reset_to_empty(String self);

/*
 * Free allocated memory, reset length to 0 and internal buffer to `NULL`
 */
void Str_free(String self);

/*
 * Free allocated memory, reset length to 0 and internal buffer to `NULL`
 * But NOT free `self`. Usually, use this on stack-allocated variable
 */
void Str_free_buffer_only(String self);

#endif
