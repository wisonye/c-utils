#include "string.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#if ENABLE_LINK_LIST_DEBUG
#include <stdio.h>
#endif

/*
 * Create from `char[]`
 */
Str Str_from_arr(const char arr[]) {
    usize temp_len = (arr != NULL) ? strlen(arr) : 0;

    Str string = {
        ._len = temp_len > 0 ? temp_len : 0,
        ._buffer = NULL,
    };

    if (temp_len > 0) {
        string._buffer = malloc(temp_len + 1);
        memcpy(string._buffer, arr, temp_len);
        string._buffer[temp_len] = '\0';
    }

    return string;
}

/*
 * Create from `char*`
 */
Str Str_from_str(const char *str) {
    usize temp_len = (str != NULL) ? strlen(str) : 0;

    Str string = {
        ._len = temp_len > 0 ? temp_len : 0,
        ._buffer = NULL,
    };

    if (temp_len > 0) {
        string._buffer = malloc(temp_len + 1);
        memcpy(string._buffer, str, temp_len);
        string._buffer[temp_len] = '\0';
    }

    return string;
}

/*
 * Clone from given `Str` instance
 */
Str Str_clone(const Str *src) {
    String string = {
        ._len = 0,
        ._buffer = NULL,
    };

    if (src != NULL && src->_len > 0 && src->_buffer != NULL) {
        string._len = src->_len;
        string._buffer = malloc(src->_len + 1);
        memcpy(string._buffer, src->_buffer, src->_len);
        string._buffer[string._len] = '\0';
    }

    return string;
}

/*
 * Append `char *` at the end
 */
void Str_append(const Str *self, const char *str_to_append) {}

/*
 * Append `char *` at the beginning
 */
void Str_insert_at_begin(const Str *self, const char *str_to_insert) {}

/*
 * Append `char *` at the given index
 */
void Str_insert_at_index(const Str *self, const char *str_to_insert,
                         usize index_to_insert) {}

/*
 * Get back string length
 */
usize Str_length(const Str *self) { return (self != NULL) ? self->_len : 0; }

/*
 * Get back `char *`
 */
const char *Str_as_str(const Str *self) {
    return (self != NULL && self->_buffer != NULL) ? self->_buffer : NULL;
}

/*
 * Find implementation (not public)
 */
long Str_find_substring(const Str *self, const char *str_to_find,
                        bool case_sensitive) {
    if (self == NULL || self->_buffer == NULL || str_to_find == NULL ||
        strlen(str_to_find) <= 0) {
#if ENABLE_LINK_LIST_DEBUG
        printf("\n>>> Str_find_substring - NULL, ignore the search.");
#endif
        return -1;
    }

    char *temp_ptr = (case_sensitive) ? strstr(self->_buffer, str_to_find)
                                      : strcasestr(self->_buffer, str_to_find);

#if ENABLE_LINK_LIST_DEBUG
    printf(
        "\n>>> Str_find_substring - temp_ptr: %p, buffer_ptr: %p, index: %li, "
        "temp_ptr == 0: %d",
        temp_ptr, self->_buffer, (temp_ptr - self->_buffer), temp_ptr == 0x00);
#endif
    return (temp_ptr == NULL || temp_ptr == 0x0) ? -1
                                                 : temp_ptr - self->_buffer;
}

/*
 * Find the given `char *` index, return `-1` if not found.
 */
long Str_index_of(const Str *self, const char *str_to_find) {
    return Str_find_substring(self, str_to_find, false);
}

/*
 * Find the given `char *` (case sensitive) index, return `-1` if not found.
 */
long Str_index_of_case_sensitive(const Str *self, const char *str_to_find) {
    return Str_find_substring(self, str_to_find, true);
}

/*
 * Check whether contain the given `char *` or not
 */
bool Str_contains(const Str *self, char *str_to_check) {
    return Str_find_substring(self, str_to_check, false) != -1;
}

/*
 * Free allocated memory, reset length to 0 and internal buffer to `NULL`
 */
void Str_free(Str *self) {
    if (self != NULL && self->_buffer != NULL) {
        free(self->_buffer);
        self->_len = 0;
        self->_buffer = NULL;
    }
}
