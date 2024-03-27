#include "str.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#if ENABLE_DEBUG_LOG
    #include <stdio.h>

    #include "log.h"
    #if ENABLE_PRINT_STRING_MEMORY
        #include "memory.h"
    #endif
#endif

//
// `String` is an opaque pointer which uses to hide the `struct Str` detail,
// which means `struct Str` doesn't exists in the outside world. If you want
// to get back `sizeof(struct Str)` for some reasons, this function is the
// anwser.
//
usize Str_struct_size(void) {
    return sizeof(struct Str);
}

/*
 * Init empty `struct Str`
 */
void Str_init(String self) {
    *self = (struct Str){
        ._capacity = 0,
        ._len      = 0,
        ._buffer   = NULL,
    };

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(String,
              init,
              "self ptr: %p, capacity: %lu",
              self,
              self->_capacity);
#endif
}

/*
 * Init empty `struct Str` that ability to hold `capacity` characters
 */
void Str_init_with_capacity(String self, usize capacity) {
    *self = (struct Str){
        ._capacity = capacity,
        ._len      = 0,
        ._buffer   = calloc(capacity, 1),
    };

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(String,
              init_with_capacity,
              "self ptr: %p, capacity: %lu, malloc ptr: %p",
              self,
              self->_capacity,
              self->_buffer);
#endif
}

/*
 * Create from empty
 */
String Str_from_empty(void) {
    String string = malloc(sizeof(struct Str));

    *string = (struct Str){
        ._capacity = 0,
        ._len      = 0,
        ._buffer   = NULL,
    };

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(String,
              from_empty,
              "self ptr: %p, capacity: %lu",
              string,
              string->_capacity);
#endif

    return string;
}

/*
 * Create from empty that ability to hold `capacity` characters
 */
String Str_from_empty_with_capacity(usize capacity) {
    String string = malloc(sizeof(struct Str));

    *string = (struct Str){
        ._capacity = capacity,
        ._len      = 0,
        ._buffer   = calloc(capacity, 1),
    };

#if ENABLE_DEBUG_LOG
    DEBUG_LOG(String,
              from_empty_with_capacity,
              "self ptr: %p, capacity: %lu, malloc ptr: %p",
              string,
              string->_capacity,
              string->_buffer);
#endif

    return string;
}

/*
 * Create from `char[]`
 */
String Str_from_arr(const char arr[]) {
    usize temp_len = (arr != NULL) ? strlen(arr) : 0;

    String string = malloc(sizeof(struct Str));

    *string = (struct Str){
        ._capacity = temp_len > 0 ? temp_len + 1 : 0,
        ._len      = temp_len > 0 ? temp_len : 0,
        ._buffer   = NULL,
    };

    if (temp_len > 0) {
        string->_buffer = malloc(string->_capacity);
#if ENABLE_DEBUG_LOG
        DEBUG_LOG(String,
                  from_arr,
                  "self ptr: %p, capacity: %lu, malloc ptr: %p, from_arr: %s",
                  string,
                  string->_capacity,
                  string->_buffer,
                  arr);
#endif
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
        ._capacity = temp_len > 0 ? temp_len + 1 : 0,
        ._len      = temp_len > 0 ? temp_len : 0,
        ._buffer   = NULL,
    };

    if (temp_len > 0) {
        string->_buffer = malloc(string->_capacity);
        memcpy(string->_buffer, str, temp_len);
        string->_buffer[temp_len] = '\0';

#if ENABLE_DEBUG_LOG
        DEBUG_LOG(String,
                  from_str,
                  "self ptr: %p, capacity: %lu, malloc ptr: %p, from_str: %s",
                  string,
                  string->_capacity,
                  string->_buffer,
                  str);
#endif
    }

    return string;
}

/*
 * Create from `char*` with give position and count
 */
String Str_from_str_with_pos(const char *str, int start_pos, int count) {
    int temp_str_len = (str != NULL) ? strlen(str) : 0;
    usize temp_len   = ((start_pos >= 0) && (count >= 1) &&
                      (start_pos + count - 1 <= temp_str_len - 1))
                           ? count
                           : 0;
    /* printf("\n>>> temp_str_len: %lu\n", temp_str_len); */
    /* printf("\n>>> temp_len: %lu\n", temp_len); */

    String string = malloc(sizeof(struct Str));

    *string = (struct Str){
        ._capacity = temp_len > 0 ? temp_len + 1 : 0,
        ._len      = temp_len > 0 ? temp_len : 0,
        ._buffer   = NULL,
    };

    if (temp_len > 0) {
        string->_buffer = malloc(string->_capacity);
        memcpy(string->_buffer, str + start_pos, temp_len);
        string->_buffer[temp_len] = '\0';

#if ENABLE_DEBUG_LOG
        DEBUG_LOG(String,
                  from_str,
                  "self ptr: %p, capacity: %lu, malloc ptr: %p, _buffer: %s, "
                  "start_pos: %i, count: %i",
                  string,
                  string->_capacity,
                  string->_buffer,
                  string->_buffer,
                  start_pos,
                  count);
#endif
    }

    return string;
}

/*
 * Clone from the given `String` instance but don't touch the heap-allocated
 * memory it owned
 */
String Str_clone_from(const String other) {
    String string = malloc(sizeof(struct Str));

    *string = (struct Str){
        ._capacity = 0,
        ._len      = 0,
        ._buffer   = NULL,
    };

    if (other != NULL && other->_len > 0 && other->_buffer != NULL) {
        string->_len      = other->_len;
        string->_capacity = other->_len + 1;
        string->_buffer   = malloc(string->_capacity);
        memcpy(string->_buffer, other->_buffer, other->_len);
        string->_buffer[string->_len] = '\0';

#if ENABLE_DEBUG_LOG
        DEBUG_LOG(String,
                  clone_from,
                  "self ptr: %p, capacity: %lu, malloc ptr: %p, other: %s",
                  string,
                  string->_capacity,
                  string->_buffer,
                  Str_as_str(other));
#endif
    } else {
#if ENABLE_DEBUG_LOG
        DEBUG_LOG(String,
                  clone_from,
                  "self ptr: %p, capacity: %lu, other: %s",
                  string,
                  string->_capacity,
                  Str_as_str(other));
#endif
    }

    return string;
}

/*
 * Move from the given `String` instance and move ownership of the
 * heap-allocated memory to the newly created `String` instance
 */
String Str_move_from(String other) {
    String string = malloc(sizeof(struct Str));

    *string = (struct Str){
        ._capacity = 0,
        ._len      = 0,
        ._buffer   = NULL,
    };

    if (other != NULL && other->_len > 0 && other->_buffer != NULL) {
        string->_len      = other->_len;
        string->_capacity = other->_len + 1;

        //
        // Copy the `other->_buffer` and delete before returning this fuction,
        // that's `MOVE` semantic in `C++`
        //
        string->_buffer = other->_buffer;

#if ENABLE_DEBUG_LOG
        DEBUG_LOG(String,
                  move_from,
                  "self ptr: %p, capacity: %lu, malloc ptr: %p, other: %s",
                  string,
                  string->_capacity,
                  string->_buffer,
                  Str_as_str(other));
#endif
    } else {
#if ENABLE_DEBUG_LOG
        DEBUG_LOG(String,
                  move_from,
                  "self ptr: %p, capacity: %lu, other: %s",
                  string,
                  string->_capacity,
                  Str_as_str(other));
#endif
    }

    //
    // Reset the `other` to empty, so the newly created `string->_buffer`
    // becomes the only one pointer to the previous heap-allocated memory, it
    // becomes the owner of that chunk of memory.
    //
    other->_len      = 0;
    other->_capacity = 0;
    other->_buffer   = NULL;

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

    usize new_len_with_null_terminated_char = self->_len + str_to_push_len + 1;
    bool need_realloc                       = false;

#ifdef ENABLE_PRINT_STRING_MEMORY
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE("char *", self->_buffer, self->_capacity);
#endif

    //
    // ensure the `_buffer` has enough space to hold all characters;
    // capacity >= self->_len + 1
    //
    if (new_len_with_null_terminated_char > self->_capacity) {
        need_realloc = true;
        self->_buffer =
            realloc(self->_buffer, new_len_with_null_terminated_char);

#ifdef ENABLE_DEBUG_LOG
        usize old_capacity = self->_capacity;
        DEBUG_LOG(String,
                  Str_push_str,
                  "Realloc needed, current capacity: %lu, new capacity: %lu, "
                  "self->_buffer: %p",
                  old_capacity,
                  new_len_with_null_terminated_char,
                  self->_buffer);
#endif
    }

#ifdef ENABLE_PRINT_STRING_MEMORY
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE("char *",
                                      self->_buffer,
                                      new_len_with_null_terminated_char);
#endif

    char *copy_ptr = self->_buffer;

    //
    // Make sure to write from `\0` of exists `char *` (override the existing
    // null-terminated character)!!!
    //
    if (self->_len > 0) {
        copy_ptr += self->_len;
    }

    memcpy(copy_ptr, str_to_push, str_to_push_len);

    // Make sure add the null-terminated character
    self->_buffer[new_len_with_null_terminated_char - 1] = '\0';

#ifdef ENABLE_PRINT_STRING_MEMORY
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE("char *",
                                      self->_buffer,
                                      new_len_with_null_terminated_char);
#endif

    // Update new length and capacity (when needed)
    self->_len = new_len_with_null_terminated_char - 1;
    if (need_realloc) {
        self->_capacity = new_len_with_null_terminated_char;
    }
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

    usize new_len_with_null_terminated_char = self->_len + insert_len + 1;
    bool need_realloc                       = false;

    //
    // ensure the `_buffer` has enough space to hold all characters;
    // capacity >= self->_len + 1
    //
    if (new_len_with_null_terminated_char > self->_capacity) {
        need_realloc = true;
        self->_buffer =
            realloc(self->_buffer, new_len_with_null_terminated_char);

#ifdef ENABLE_DEBUG_LOG
        usize old_capacity = self->_capacity;
        DEBUG_LOG(String,
                  Str_push_str,
                  "Realloc needed, current capacity: %lu, new capacity: %lu, "
                  "self->_buffer: %p",
                  old_capacity,
                  new_len_with_null_terminated_char,
                  self->_buffer);
#endif
    }

#ifdef ENABLE_PRINT_STRING_MEMORY
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE("char *",
                                      self->_buffer,
                                      new_len_with_null_terminated_char);
#endif

    char *copy_ptr = self->_buffer;

    //
    // First, move the existing char to the right
    //
    if (self->_len > 0) {
        memmove(copy_ptr + insert_len, self->_buffer, self->_len);
    }

    // Copy insert value (NOT include the `\0`)
    memcpy(copy_ptr, str_to_insert, insert_len);

    // Make sure add the null-terminated character
    self->_buffer[new_len_with_null_terminated_char - 1] = '\0';

#ifdef ENABLE_PRINT_STRING_MEMORY
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE("char *",
                                      self->_buffer,
                                      new_len_with_null_terminated_char);
#endif

    // Update new length and capacity (when needed)
    self->_len = new_len_with_null_terminated_char - 1;
    if (need_realloc) {
        self->_capacity = new_len_with_null_terminated_char;
    }
}

/*
 * Insert `char *` at the given index
 */
// void Str_insert_at_index(String self, const char *str_to_insert,
//                          usize index_to_insert) {}

/*
 * Get back string length
 */
usize Str_length(const String self) {
    return (self != NULL) ? self->_len : 0;
}

/*
 * Get back capacity
 */
usize Str_capacity(const String self) {
    return (self != NULL) ? self->_capacity : 0;
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
long Str_find_substring(const String self,
                        const char *str_to_find,
                        bool case_sensitive) {
    if (self == NULL || self->_buffer == NULL || str_to_find == NULL ||
        strlen(str_to_find) <= 0) {
#if ENABLE_LINK_LIST_DEBUG
        printf("\n>>> Str_find_substring - NULL, ignore the search.");
#endif
        return -1;
    }

#ifdef __APPLE__
    char *temp_ptr = (case_sensitive) ? strstr(self->_buffer, str_to_find)
                                      : strcasestr(self->_buffer, str_to_find);
#else
    char *temp_ptr = (case_sensitive) ? strstr(self->_buffer, str_to_find)
                                      : strcasestr(self->_buffer, str_to_find);
#endif

#if ENABLE_LINK_LIST_DEBUG
    printf(
        "\n>>> Str_find_substring - temp_ptr: %p, buffer_ptr: %p, index: %li, "
        "temp_ptr == 0: %d",
        temp_ptr,
        self->_buffer,
        (temp_ptr - self->_buffer),
        temp_ptr == 0x00);
#endif
    return (temp_ptr == NULL || temp_ptr == 0x0) ? -1
                                                 : temp_ptr - self->_buffer;
}

/*
 * Find the given `char *` index, return `-1` if not found.
 */
long Str_index_of(const String self, const char *str_to_find) {
    return Str_find_substring(self, str_to_find, false);
}

/*
 * Find the given `char *` (case sensitive) index, return `-1` if not found.
 */
long Str_index_of_case_sensitive(const String self, const char *str_to_find) {
    return Str_find_substring(self, str_to_find, true);
}

/*
 * Check whether contain the given `char *` or not
 */
bool Str_contains(const String self, char *str_to_check) {
    return Str_find_substring(self, str_to_check, false) != -1;
}

/*
 * Reset  to empty string
 */
void Str_reset_to_empty(String self) {
    if (self != NULL && self->_buffer != NULL) {
        self->_len      = 0;
        self->_capacity = 0;
        if (self->_buffer != NULL) {
            free(self->_buffer);
            self->_buffer = NULL;
        }
    }
}

/*
 * Reset to empty string without freeing buffer memory, only used in the
 * following situation:
 *
 * Someone calls `memcpy` to do a shallow copy which means the `self->buffer`
 * ownership has moved away.
 */
void Str_reset_to_empty_without_freeing_buffer(String self) {
    if (self != NULL) {
        self->_len      = 0;
        self->_capacity = 0;
        self->_buffer   = NULL;
    }
}

/*
 * Free allocated memory, reset length to 0 and internal buffer to `NULL`
 */
void Str_free(String self) {
    if (self == NULL) return;

    if (self->_buffer != NULL) {
        void *ptr_to_free = self->_buffer;
        self->_buffer     = NULL;
        free(ptr_to_free);
    }

    self->_len      = 0;
    self->_capacity = 0;
    free(self);
}

/*
 * Free allocated memory, reset length to 0 and internal buffer to `NULL`
 * But NOT free `self`. Usually, use this on stack-allocated variable
 */
void Str_free_buffer_only(String self) {
    if (self == NULL) return;

    if (self->_buffer != NULL) {
        void *ptr_to_free = self->_buffer;
        self->_buffer     = NULL;
        free(ptr_to_free);
    }

    self->_len      = 0;
    self->_capacity = 0;
}

/*
 * Auto free string call
 */
void auto_free_string(String *ptr) {
#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(String,
              auto_free_string,
              "out of scope with string ptr: %p, as_str: %s",
              *ptr,
              Str_as_str(*ptr));
#endif
    Str_free(*ptr);
}
