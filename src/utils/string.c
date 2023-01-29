#include "string.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#if ENABLE_LINK_LIST_DEBUG
#include <stdio.h>
#endif

//
// Heap allocated string
//
struct Str {
    usize _len;
    char *_buffer;
};

/*
 * Create from empty
 */
String Str_from_empty() {
    String string = malloc(sizeof(struct Str));
    *string = (struct Str){
        ._len = 0,
        ._buffer = NULL,
    };

    return string;
}

/*
 * Create from `char[]`
 */
String Str_from_arr(const char arr[]) {
    usize temp_len = (arr != NULL) ? strlen(arr) : 0;

    String string = malloc(sizeof(struct Str));
    *string = (struct Str){
        ._len = temp_len > 0 ? temp_len : 0,
        ._buffer = NULL,
    };

    if (temp_len > 0) {
        string->_buffer = malloc(temp_len + 1);
        memcpy(string->_buffer, arr, temp_len);
        string->_buffer[temp_len] = '\0';
    }

    return string;
}

/*
 * Create from `char*`
 */
String Str_from_str(const char *str) {
    usize temp_len = (str != NULL) ? strlen(str) : 0;

    String string = malloc(sizeof(struct Str));
    *string = (struct Str){
        ._len = temp_len > 0 ? temp_len : 0,
        ._buffer = NULL,
    };

    if (temp_len > 0) {
        string->_buffer = malloc(temp_len + 1);
        memcpy(string->_buffer, str, temp_len);
        string->_buffer[temp_len] = '\0';
    }

    return string;
}

/*
 * Clone from given `Str` instance
 */
String Str_clone(const String other) {
    String string = malloc(sizeof(struct Str));
    *string = (struct Str){
        ._len = 0,
        ._buffer = NULL,
    };

    if (other != NULL && other->_len > 0 && other->_buffer != NULL) {
        string->_len = other->_len;
        string->_buffer = malloc(other->_len + 1);
        memcpy(string->_buffer, other->_buffer, other->_len);
        string->_buffer[string->_len] = '\0';
    }

    return string;
}

/*
 * Push other `String *` at the end
 */
void Str_push_other(String self, const String other) {
    if (self == NULL || other == NULL) {
        return;
    }

    Str_push_str(self, Str_as_str(other));
}

/*
 * Push the given `char *` at the end
 */
void Str_push_str(String self, const char *str_to_push) {
    if (self == NULL || str_to_push == NULL) {
        return;
    }

    usize str_to_push_len = strlen(str_to_push);
    if (str_to_push_len <= 0) {
        return;
    }

    usize new_buffer_len = self->_len + str_to_push_len + 1;
    char *new_buffer = malloc(new_buffer_len);
    char *copy_ptr = new_buffer;

    // Copy original value (NOT include the `\0`)
    if (self->_len > 0) {
        memcpy(copy_ptr, self->_buffer, self->_len);
        copy_ptr += self->_len;
    }

    memcpy(copy_ptr, str_to_push, str_to_push_len);
    new_buffer[new_buffer_len - 1] = '\0';

    // Update
    self->_len = new_buffer_len - 1;  // Not count the '\0'
    if (self->_buffer != NULL) {
        free(self->_buffer);
    }
    self->_buffer = new_buffer;
}

/*
 * Insert `String *` to the beginning
 */
void Str_insert_other_to_begin(String self, const String other) {
    if (self == NULL || other == NULL) {
        return;
    }

    Str_insert_str_to_begin(self, Str_as_str(other));
}

/*
 * Insert `char *` to the beginning
 */
void Str_insert_str_to_begin(String self, const char *str_to_insert) {
    if (self == NULL || str_to_insert == NULL) {
        return;
    }

    usize insert_len = strlen(str_to_insert);
    if (insert_len <= 0) {
        return;
    }

    usize new_buffer_len = self->_len + insert_len + 1;
    char *new_buffer = malloc(new_buffer_len);
    char *copy_ptr = new_buffer;

    // Copy insert value (NOT include the `\0`)
    memcpy(copy_ptr, str_to_insert, insert_len);
    copy_ptr += insert_len;

    if (self->_len > 0) {
        memcpy(copy_ptr, self->_buffer, self->_len);
    }
    new_buffer[new_buffer_len - 1] = '\0';

    // Update
    self->_len = new_buffer_len - 1;  // Not count the '\0'
    if (self->_buffer != NULL) {
        free(self->_buffer);
    }
    self->_buffer = new_buffer;
}

/*
 * Insert `char *` at the given index
 */
void Str_insert_at_index(String self, const char *str_to_insert,
                         usize index_to_insert) {}

/*
 * Get back string length
 */
const usize Str_length(const String self) {
    return (self != NULL) ? self->_len : 0;
}

/*
 * Get back `char *`
 */
const char *Str_as_str(const String self) {
    return (self != NULL && self->_buffer != NULL) ? self->_buffer : NULL;
}

/*
 * Find implementation (not public)
 */
long Str_find_substring(const String self, const char *str_to_find,
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
const long Str_index_of(const String self, const char *str_to_find) {
    return Str_find_substring(self, str_to_find, false);
}

/*
 * Find the given `char *` (case sensitive) index, return `-1` if not found.
 */
const long Str_index_of_case_sensitive(const String self,
                                       const char *str_to_find) {
    return Str_find_substring(self, str_to_find, true);
}

/*
 * Check whether contain the given `char *` or not
 */
const bool Str_contains(const String self, char *str_to_check) {
    return Str_find_substring(self, str_to_check, false) != -1;
}

/*
 * Reset  to empty string
 */
void Str_reset_to_empty(String self) {
    if (self != NULL && self->_buffer != NULL) {
        self->_len = 0;
        free(self->_buffer);
        self->_buffer = NULL;
    }
}

/*
 * Free allocated memory, reset length to 0 and internal buffer to `NULL`
 */
void Str_free(String self) {
    if (self == NULL) return;

    if (self->_buffer != NULL) {
        void *ptr_to_free = self->_buffer;
        self->_buffer = NULL;
        free(ptr_to_free);
    }

    self->_len = 0;
    free(self);
}
