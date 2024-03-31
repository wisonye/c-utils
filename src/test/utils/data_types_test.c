#include "./data_types_test.h"

#include <stddef.h>
#include <string.h>
#include <unity.h>

#include "../../utils/data_types.h"

////
////
////
void test_data_types_type_name(void) {
    char char_value               = 'c';
    u8 u8_value                   = 255;
    u16 u16_value                 = 65535;
    u32 u32_value                 = 99999;
    u64 u64_value                 = 99999;
    usize usize_value             = 99999;
    i8 i8_value                   = 127;
    i16 i16_value                 = 65535 / 2;
    i32 i32_value                 = -99999;
    i64 i64_value                 = -2299999;
    int int_value                 = 999999;
    long long_value               = 999999;
    long long long_long_value     = 999999;
    float float_value             = 123.123;
    double double_value           = 99999.123;
    long double long_double_value = 99999.123;
    bool bool_value               = true;

    TEST_ASSERT_EQUAL_STRING("char", TYPE_NAME(char_value));
    TEST_ASSERT_EQUAL_STRING("unsigned char", TYPE_NAME(u8_value));
    TEST_ASSERT_EQUAL_STRING("unsigned short int", TYPE_NAME(u16_value));
    TEST_ASSERT_EQUAL_STRING("unsigned int", TYPE_NAME(u32_value));
#if defined(__APPLE__)
    TEST_ASSERT_EQUAL_STRING("unsigned long long int", TYPE_NAME(u64_value));
#elif defined(__FreeBSD__)
    TEST_ASSERT_EQUAL_STRING("unsigned long int", TYPE_NAME(u64_value));
#endif
    TEST_ASSERT_EQUAL_STRING("unsigned long int", TYPE_NAME(usize_value));
    TEST_ASSERT_EQUAL_STRING("signed char", TYPE_NAME(i8_value));
    TEST_ASSERT_EQUAL_STRING("short int", TYPE_NAME(i16_value));
    TEST_ASSERT_EQUAL_STRING("int", TYPE_NAME(i32_value));
#if defined(__APPLE__)
    TEST_ASSERT_EQUAL_STRING("long long int", TYPE_NAME(i64_value));
#elif defined(__FreeBSD__)
    TEST_ASSERT_EQUAL_STRING("long int", TYPE_NAME(i64_value));
#endif
    TEST_ASSERT_EQUAL_STRING("int", TYPE_NAME(int_value));
    TEST_ASSERT_EQUAL_STRING("long int", TYPE_NAME(long_value));
    TEST_ASSERT_EQUAL_STRING("long long int", TYPE_NAME(long_long_value));
    TEST_ASSERT_EQUAL_STRING("float", TYPE_NAME(float_value));
    TEST_ASSERT_EQUAL_STRING("double", TYPE_NAME(double_value));
    TEST_ASSERT_EQUAL_STRING("long double", TYPE_NAME(long_double_value));
    TEST_ASSERT_EQUAL_STRING("bool", TYPE_NAME(bool_value));
}

////
////
////
void test_data_types_is_the_same_type(void) {
    size_t aaa  = 100;
    usize bbb   = 99;
    bool result = false;
    IS_THE_SAME_TYPE(aaa, bbb, result);
    TEST_ASSERT_EQUAL(result, true);
}

////
////
////
void test_data_types_type_name_to_string(void) {
    TEST_ASSERT_EQUAL_STRING("char", TYPE_NAME_TO_STRING(char));
    TEST_ASSERT_EQUAL_STRING("unsigned char",
                             TYPE_NAME_TO_STRING(unsigned char));
    TEST_ASSERT_EQUAL_STRING("unsigned short int",
                             TYPE_NAME_TO_STRING(unsigned short int));
    TEST_ASSERT_EQUAL_STRING("unsigned int", TYPE_NAME_TO_STRING(unsigned int));
    TEST_ASSERT_EQUAL_STRING("unsigned long int",
                             TYPE_NAME_TO_STRING(unsigned long int));
    TEST_ASSERT_EQUAL_STRING("signed char", TYPE_NAME_TO_STRING(signed char));
    TEST_ASSERT_EQUAL_STRING("short int", TYPE_NAME_TO_STRING(short int));
    TEST_ASSERT_EQUAL_STRING("int", TYPE_NAME_TO_STRING(int));
    TEST_ASSERT_EQUAL_STRING("long int", TYPE_NAME_TO_STRING(long int));
    TEST_ASSERT_EQUAL_STRING("int", TYPE_NAME_TO_STRING(int));
    TEST_ASSERT_EQUAL_STRING("long int", TYPE_NAME_TO_STRING(long int));
    TEST_ASSERT_EQUAL_STRING("long long int",
                             TYPE_NAME_TO_STRING(long long int));
    TEST_ASSERT_EQUAL_STRING("float", TYPE_NAME_TO_STRING(float));
    TEST_ASSERT_EQUAL_STRING("double", TYPE_NAME_TO_STRING(double));
    TEST_ASSERT_EQUAL_STRING("long double", TYPE_NAME_TO_STRING(long double));
    TEST_ASSERT_EQUAL_STRING("bool", TYPE_NAME_TO_STRING(bool));
}

////
////
////
void test_data_types_type_size(void) {
    char *string_value            = (char *)"Wison Ye";
    char char_value               = 'c';
    u8 u8_value                   = 255;
    u16 u16_value                 = 65535;
    u32 u32_value                 = 99999;
    u64 u64_value                 = 99999;
    usize usize_value             = 99999;
    i8 i8_value                   = 127;
    i16 i16_value                 = 65535 / 2;
    i32 i32_value                 = -99999;
    i64 i64_value                 = -2299999;
    int int_value                 = 999999;
    long long_value               = 999999;
    long long long_long_value     = 999999;
    float float_value             = 123.123;
    double double_value           = 99999.123;
    long double long_double_value = 99999.123;
    bool bool_value               = true;

    typedef struct {
        int x;
        int y;
    } Point;
    Point temp_point = {.x = 1, .y = 2};

    TEST_ASSERT_EQUAL_UINT(sizeof(char *), TYPE_SIZE(string_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(char), TYPE_SIZE(char_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned char), TYPE_SIZE(u8_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned short int), TYPE_SIZE(u16_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned int), TYPE_SIZE(u32_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned long int), TYPE_SIZE(u64_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned long int), TYPE_SIZE(usize_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(signed char), TYPE_SIZE(i8_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(short int), TYPE_SIZE(i16_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(int), TYPE_SIZE(i32_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(long int), TYPE_SIZE(i64_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(int), TYPE_SIZE(int_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(long int), TYPE_SIZE(long_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(long long int), TYPE_SIZE(long_long_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(float), TYPE_SIZE(float_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(double), TYPE_SIZE(double_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(long double), TYPE_SIZE(long_double_value));
    TEST_ASSERT_EQUAL_UINT(sizeof(bool), TYPE_SIZE(bool_value));
    TEST_ASSERT_EQUAL_UINT(0, TYPE_SIZE(temp_point));

    void *void_ptr               = &string_value;
    bool *bool_ptr               = &bool_value;
    u8 *u8_ptr                   = &u8_value;
    u16 *u16_ptr                 = &u16_value;
    u32 *u32_ptr                 = &u32_value;
    u64 *u64_ptr                 = &u64_value;
    usize *usize_ptr             = &usize_value;
    i8 *i8_ptr                   = &i8_value;
    i16 *i16_ptr                 = &i16_value;
    i32 *i32_ptr                 = &i32_value;
    i64 *i64_ptr                 = &i64_value;
    float *float_ptr             = &float_value;
    double *double_ptr           = &double_value;
    long double *long_double_ptr = &long_double_value;

    TEST_ASSERT_EQUAL_UINT(sizeof(void *), TYPE_SIZE(void_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(bool *), TYPE_SIZE(bool_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(u8 *), TYPE_SIZE(u8_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(u16 *), TYPE_SIZE(u16_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(u32 *), TYPE_SIZE(u32_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(u64 *), TYPE_SIZE(u64_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(usize *), TYPE_SIZE(usize_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(i8 *), TYPE_SIZE(i8_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(i16 *), TYPE_SIZE(i16_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(i32 *), TYPE_SIZE(i32_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(i64 *), TYPE_SIZE(i64_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(float *), TYPE_SIZE(float_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(double *), TYPE_SIZE(double_ptr));
    TEST_ASSERT_EQUAL_UINT(sizeof(long double *), TYPE_SIZE(long_double_ptr));
}

////
////
////
void test_data_types_type_size_from_type(void) {
    TEST_ASSERT_EQUAL_UINT(sizeof(char), TYPE_SIZE_FROM_TYPE(char));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned char),
                           TYPE_SIZE_FROM_TYPE(unsigned char));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned short int),
                           TYPE_SIZE_FROM_TYPE(unsigned short int));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned int),
                           TYPE_SIZE_FROM_TYPE(unsigned int));
    TEST_ASSERT_EQUAL_UINT(sizeof(unsigned long int),
                           TYPE_SIZE_FROM_TYPE(unsigned long int));
    TEST_ASSERT_EQUAL_UINT(sizeof(signed char),
                           TYPE_SIZE_FROM_TYPE(signed char));
    TEST_ASSERT_EQUAL_UINT(sizeof(short int), TYPE_SIZE_FROM_TYPE(short int));
    TEST_ASSERT_EQUAL_UINT(sizeof(int), TYPE_SIZE_FROM_TYPE(int));
    TEST_ASSERT_EQUAL_UINT(sizeof(long int), TYPE_SIZE_FROM_TYPE(long int));
    TEST_ASSERT_EQUAL_UINT(sizeof(int), TYPE_SIZE_FROM_TYPE(int));
    TEST_ASSERT_EQUAL_UINT(sizeof(long int), TYPE_SIZE_FROM_TYPE(long int));
    TEST_ASSERT_EQUAL_UINT(sizeof(long long int),
                           TYPE_SIZE_FROM_TYPE(long long int));
    TEST_ASSERT_EQUAL_UINT(sizeof(float), TYPE_SIZE_FROM_TYPE(float));
    TEST_ASSERT_EQUAL_UINT(sizeof(double), TYPE_SIZE_FROM_TYPE(double));
    TEST_ASSERT_EQUAL_UINT(sizeof(long double),
                           TYPE_SIZE_FROM_TYPE(long double));
    TEST_ASSERT_EQUAL_UINT(sizeof(bool), TYPE_SIZE_FROM_TYPE(bool));
}
