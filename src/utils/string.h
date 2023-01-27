#ifndef __UTILS_STRING_H__
#define __UTILS_STRING_H__

#include <stdbool.h>

#include "data_types.h"

//
// Heap allocated string
//
typedef struct Str *String;

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
 * Clone from given `Str` instance
 */
String Str_clone(const String other);

/*
 * Push other `String *` at the end
 */
void Str_push_other(String self, const String other);

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

#endif
