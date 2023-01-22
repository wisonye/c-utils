#ifndef __UTILS_STRING_H__
#define __UTILS_STRING_H__

#include <stdbool.h>

#include "data_types.h"

//
// Heap allocated string
//
typedef struct {
    usize _len;
    char *_buffer;
} String, Str;

/*
 * Create from empty
 */
Str Str_from_empty();

/*
 * Create from `char[]`
 */
Str Str_from_arr(const char arr[]);

/*
 * Create from `char*`
 */
Str Str_from_str(const char *str);

/*
 * Clone from given `Str` instance
 */
Str Str_clone(const Str *src);

/*
 * Push other `Str *` at the end
 */
void Str_push_other(Str *self, const Str *other);

/*
 * Push the given `char *` at the end
 */
void Str_push_str(Str *self, const char *str_to_push);

/*
 * Insert `Str *` to the beginning
 */
void Str_insert_other_to_begin(Str *self, const Str *other);

/*
 * Insert `char *` to the beginning
 */
void Str_insert_str_to_begin(Str *self, const char *str_to_insert);


/*
 * Insert `char *` at the given index
 */
void Str_insert_at_index(Str *self, const char *str_to_insert,
                         usize index_to_insert);

/*
 * Get back string length
 */
usize Str_length(const Str *self);

/*
 * Get back `char *`
 */
const char *Str_as_str(const Str *self);

/*
 * Find the given `char *` index, return `-1` if not found.
 */
long Str_index_of(const Str *self, const char *str_to_find);

/*
 * Find the given `char *` (case sensitive) index, return `-1` if not found.
 */
long Str_index_of_case_sensitive(const Str *self, const char *str_to_find);

/*
 * Check whether contain the given `char *` or not
 */
bool Str_contains(const Str *self, char *str_to_check);

/*
 * Reset  to empty string
 */
void Str_reset_to_empty(Str *self);

/*
 * Free allocated memory, reset length to 0 and internal buffer to `NULL`
 */
void Str_free(Str *self);

#endif
