#include "string.h"

#include <stdlib.h>
#include <string.h>

//
// Create from `char[]` or `char *`
//
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

//
//
//
usize Str_length(const Str *str) { return (str != NULL) ? str->_len : 0; }

const char *Str_as_str(const Str *str) {
    return (str != NULL && str->_buffer != NULL) ? str->_buffer : NULL;
}

//
// Free
//
void Str_free(Str *str) {
    if (str != NULL && str->_buffer != NULL) {
        free(str->_buffer);
        str->_len = 0;
        str->_buffer = NULL;
    }
}
