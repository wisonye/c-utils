#ifndef __UTILS_STRING_H__
#define __UTILS_STRING_H__

#include "data_types.h"

//
// Heap allocated string
//
typedef struct {
    usize _len;
    char *_buffer;
} String, Str;

//
// Create from `char[]` or `char *`
//
Str Str_from_arr(const char arr[]);
Str Str_from_str(const char *str);

//
//
//
usize Str_length(const Str *str);
const char *Str_as_str(const Str *str);

//
// Free
//
void Str_free(Str *str);

#endif
