#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include <stddef.h>
#include <stdint.h>

//
// Rust integer types
//
typedef uint8_t u8;
typedef uint8_t uint8;
typedef uint16_t u16;
typedef uint16_t uint16;
typedef uint32_t u32;
typedef uint32_t uint32;
typedef uint64_t u64;
typedef uint64_t uint64;
typedef size_t usize;

//
// Rust string literal
//
typedef char* _str;

//
// Get back data type name as static `char *`
//
#define TYPE_NAME(x) \
    _Generic((x),                                                   \
    _Bool: "_Bool",                                                 \
    unsigned char: "unsigned char",                                 \
    char: "char",                                                   \
    signed char: "signed char",                                     \
    short int: "short int",                                         \
    unsigned short int: "unsigned short int",                       \
    int: "int",                                                     \
    unsigned int: "unsigned int",                                   \
    long int: "long int",                                           \
    unsigned long int: "unsigned long int",                         \
    long long int: "long long int",                                 \
    unsigned long long int: "unsigned long long int",               \
    float: "float",                                                 \
    double: "double",                                               \
    long double: "long double",                                     \
    char *: "pointer to char",                                      \
    void *: "pointer to void",                                      \
    _Bool *: "pointer to Bool",                                     \
    unsigned char *: "pointer to unsigned char",                    \
    signed char *: "pointer to signed char",                        \
    short int *: "pointer to short int",                            \
    unsigned short int *: "pointer to unsigned short int",          \
    int *: "pointer to int",                                        \
    unsigned int *: "pointer to unsigned int",                      \
    long int *: "pointer to long int",                              \
    unsigned long int *: "pointer to unsigned long int",            \
    long long int *: "pointer to long long int",                    \
    unsigned long long int *: "pointer to unsigned long long int",  \
    float *: "pointer to float",                                    \
    double *: "pointer to double",                                  \
    long double *: "pointer to long double",                        \
    default: "other")

//
//
//
#define IS_IT_THE_SAME_TYPE(a, b)                                            \
    ({                                                                       \
        char _a_type[50] = TYPE_NAME((a));                                   \
        char _b_type[50] = TYPE_NAME((b));                                   \
        _Bool is_same_str_non_case_sensitive = strcasecmp(_a_type, _b_type); \
        (is_same_str_non_case_sensitive == 0);                               \
    })


#endif
