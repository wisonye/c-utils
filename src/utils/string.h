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

//
// Create from `char[]` or `char *`
//
Str Str_from_arr(const char arr[]);
Str Str_from_str(const char *str);
Str Str_clone(const Str *src);

//
// Getter
//
usize Str_length(const Str *self);
const char *Str_as_str(const Str *self);

//
// Query
//
long Str_index_of(const Str *self, const char *str_to_find);
long Str_index_of_case_sensitive(const Str *self, const char *str_to_find);
bool Str_contains(const Str *self);

//
// Free
//
void Str_free(Str *self);

#endif
