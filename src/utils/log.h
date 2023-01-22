#ifndef __UTILS_LOG_H__
#define __UTILS_LOG_H__

#include <stdbool.h>
#include <stdio.h>

#include "data_types.h"

/* void print_u8(char *v_name, u8 v) { printf("\n>>> %s: %u", v_name, v); } */

/* void print_u16(char *v_name, u16 v) { printf("\n>>> %s: %u", v_name, v); } */

void print_u32(char *v_name, u32 v) { printf("\n>>> %s: %u", v_name, v); }

void print_u64(char *v_name, u64 v) { printf("\n>>> %s: %llu", v_name, v); }

void print_usize(char *v_name, usize v) { printf("\n>>> %s: %lu", v_name, v); }

/* void print_i8(char *v_name, i8 v) { printf("\n>>> %s: %i", v_name, v); } */

/* void print_i16(char *v_name, i16 v) { printf("\n>>> %s: %i", v_name, v); } */

void print_i32(char *v_name, i32 v) { printf("\n>>> %s: %i", v_name, v); }

void print_i64(char *v_name, i64 v) { printf("\n>>> %s: %lli", v_name, v); }

void print_int(char *v_name, i64 v) { printf("\n>>> %s: %lli", v_name, v); }

void print_long(char *v_name, long v) { printf("\n>>> %s: %li", v_name, v); }

void print_char(char *v_name, char v) { printf("\n>>> %s: %c", v_name, v); }

void print_bool(char *v_name, bool v) {
    printf("\n>>> %s: %s", v_name, (v == true) ? "true" : "false");
}

void print_float(char *v_name, float v) { printf("\n>>> %s: %f", v_name, v); }

// void print_double(char *v_name, double v) { printf("\n>>> %s: %f", v_name,
// v); }
void print_long_double(char *v_name, long double v) {
    printf("\n>>> %s: %Lf", v_name, v);
}

void print_string(char *v_name, char *v) { printf("\n>>> %s: %s", v_name, v); }

void print_void_ptr(char *v_name, void *v) {
    printf("\n>>> %s (ptr): %p", v_name, v);
}

void print_bool_ptr(char *v_name, bool *v) {
    printf("\n>>> %s (ptr): %p, value: %s", v_name, v,
           (*v == true) ? "true" : "false");
}

void print_u8_ptr(char *v_name, u8 *v) {
    printf("\n>>> %s (ptr): %p, value: %u", v_name, v, *v);
}

void print_u16_ptr(char *v_name, u16 *v) {
    printf("\n>>> %s (ptr): %p, value: %u", v_name, v, *v);
}

void print_u32_ptr(char *v_name, u32 *v) {
    printf("\n>>> %s (ptr): %p, value: %u", v_name, v, *v);
}

void print_usize_ptr(char *v_name, usize *v) {
    printf("\n>>> %s (ptr): %p, value: %lu", v_name, v, *v);
}

void print_u64_ptr(char *v_name, u64 *v) {
    printf("\n>>> %s (ptr): %p, value: %llu", v_name, v, *v);
}

void print_i8_ptr(char *v_name, i8 *v) {
    printf("\n>>> %s (ptr): %p, value: %i", v_name, v, *v);
}

void print_i16_ptr(char *v_name, i16 *v) {
    printf("\n>>> %s (ptr): %p, value: %i", v_name, v, *v);
}

void print_i32_ptr(char *v_name, i32 *v) {
    printf("\n>>> %s (ptr): %p, value: %i", v_name, v, *v);
}

void print_i64_ptr(char *v_name, i64 *v) {
    printf("\n>>> %s (ptr): %p, value: %lli", v_name, v, *v);
}

void print_float_ptr(char *v_name, float *v) {
    printf("\n>>> %s (ptr): %p, value: %f", v_name, v, *v);
}

void print_double_ptr(char *v_name, double *v) {
    printf("\n>>> %s (ptr): %p, value: %f", v_name, v, *v);
}

void print_long_double_ptr(char *v_name, long double *v) {
    printf("\n>>> %s (ptr): %p, value: %Lf", v_name, v, *v);
}

/**
 * Log the variable value based the primitive type
 */
#define LOG_VAR(V) \
    _Generic((V), \
    _Bool: print_bool, \
    unsigned char: print_u32, \
    char: print_char, \
    signed char: print_i32, \
    short int: print_i32, \
    unsigned short int: print_u32, \
    int: print_int, \
    unsigned int: print_u32, \
    long int: print_long, \
    unsigned long int: print_usize, \
    long long int: print_i64, \
    unsigned long long int: print_u64, \
    float: print_float, \
    double: print_long_double, \
    long double: print_long_double, \
    char *: print_string, \
    void *: print_void_ptr, \
    _Bool *: print_bool_ptr, \
    unsigned char *: print_u8_ptr, \
    unsigned short int *: print_u16_ptr, \
    unsigned int *: print_u32_ptr, \
    unsigned long int *: print_usize_ptr,            \
    unsigned long long int *: print_u64_ptr,  \
    signed char *: print_i8_ptr, \
    short int *: print_i16_ptr, \
    int *: print_i32_ptr, \
    long int *: print_i32_ptr, \
    long long int *: print_i64_ptr, \
    float *: print_float_ptr, \
    double *: print_double_ptr, \
    long double *: print_long_double_ptr, \
    default : print_string)(#V, V)
#endif
