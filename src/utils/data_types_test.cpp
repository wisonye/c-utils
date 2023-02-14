#include <gtest/gtest.h>

extern "C" {
#include <stddef.h>
#include <string.h>

#include "data_types.h"
}

TEST(DataTypes, TYPE_NAME) {
    char *string_value = (char *)"Wison Ye";
    char char_value = 'c';
    u8 u8_value = 255;
    u16 u16_value = 65535;
    u32 u32_value = 99999;
    u64 u64_value = 99999;
    usize usize_value = 99999;
    i8 i8_value = 127;
    i16 i16_value = 65535 / 2;
    i32 i32_value = -99999;
    i64 i64_value = -2299999;
    int int_value = 999999;
    long long_value = 999999;
    long long long_long_value = 999999;
    float float_value = 123.123;
    double double_value = 99999.123;
    long double long_double_value = 99999.123;
    bool bool_value = true;

    ASSERT_EQ(strcmp("char", TYPE_NAME(char_value)), 0);
    ASSERT_EQ(strcmp("unsigned char", TYPE_NAME(u8_value)), 0);
    ASSERT_EQ(strcmp("unsigned short int", TYPE_NAME(u16_value)), 0);
    ASSERT_EQ(strcmp("unsigned int", TYPE_NAME(u32_value)), 0);
#if defined(__APPLE__)
    ASSERT_EQ(strcmp("unsigned long long int", TYPE_NAME(u64_value)), 0);
#elif defined(__FreeBSD__)
    ASSERT_EQ(strcmp("unsigned long int", TYPE_NAME(u64_value)), 0);
#endif
    ASSERT_EQ(strcmp("unsigned long int", TYPE_NAME(usize_value)), 0);
    ASSERT_EQ(strcmp("signed char", TYPE_NAME(i8_value)), 0);
    ASSERT_EQ(strcmp("short int", TYPE_NAME(i16_value)), 0);
    ASSERT_EQ(strcmp("int", TYPE_NAME(i32_value)), 0);
#if defined(__APPLE__)
    ASSERT_EQ(strcmp("long long int", TYPE_NAME(i64_value)), 0);
#elif defined(__FreeBSD__)
    ASSERT_EQ(strcmp("long int", TYPE_NAME(i64_value)), 0);
#endif
    ASSERT_EQ(strcmp("int", TYPE_NAME(int_value)), 0);
    ASSERT_EQ(strcmp("long int", TYPE_NAME(long_value)), 0);
    ASSERT_EQ(strcmp("long long int", TYPE_NAME(long_long_value)), 0);
    ASSERT_EQ(strcmp("float", TYPE_NAME(float_value)), 0);
    ASSERT_EQ(strcmp("double", TYPE_NAME(double_value)), 0);
    ASSERT_EQ(strcmp("long double", TYPE_NAME(long_double_value)), 0);
    ASSERT_EQ(strcmp("bool", TYPE_NAME(bool_value)), 0);
}

TEST(DataTypes, IS_THE_SAME_TYPE) {
    size_t aaa = 100;
    usize bbb = 99;
    ASSERT_EQ(IS_THE_SAME_TYPE(aaa, bbb), true);
}

TEST(DataTypes, TYPE_NAME_TO_STRING) {
    ASSERT_EQ(strcmp("char", TYPE_NAME_TO_STRING(char)), 0);
    ASSERT_EQ(strcmp("unsigned char", TYPE_NAME_TO_STRING(unsigned char)), 0);
    ASSERT_EQ(
        strcmp("unsigned short int", TYPE_NAME_TO_STRING(unsigned short int)),
        0);
    ASSERT_EQ(strcmp("unsigned int", TYPE_NAME_TO_STRING(unsigned int)), 0);
    ASSERT_EQ(
        strcmp("unsigned long int", TYPE_NAME_TO_STRING(unsigned long int)), 0);
    ASSERT_EQ(strcmp("signed char", TYPE_NAME_TO_STRING(signed char)), 0);
    ASSERT_EQ(strcmp("short int", TYPE_NAME_TO_STRING(short int)), 0);
    ASSERT_EQ(strcmp("int", TYPE_NAME_TO_STRING(int)), 0);
    ASSERT_EQ(strcmp("long int", TYPE_NAME_TO_STRING(long int)), 0);
    ASSERT_EQ(strcmp("int", TYPE_NAME_TO_STRING(int)), 0);
    ASSERT_EQ(strcmp("long int", TYPE_NAME_TO_STRING(long int)), 0);
    ASSERT_EQ(strcmp("long long int", TYPE_NAME_TO_STRING(long long int)), 0);
    ASSERT_EQ(strcmp("float", TYPE_NAME_TO_STRING(float)), 0);
    ASSERT_EQ(strcmp("double", TYPE_NAME_TO_STRING(double)), 0);
    ASSERT_EQ(strcmp("long double", TYPE_NAME_TO_STRING(long double)), 0);
    ASSERT_EQ(strcmp("bool", TYPE_NAME_TO_STRING(bool)), 0);
}

TEST(DataTypes, TYPE_SIZE) {
    char *string_value = (char *)"Wison Ye";
    char char_value = 'c';
    u8 u8_value = 255;
    u16 u16_value = 65535;
    u32 u32_value = 99999;
    u64 u64_value = 99999;
    usize usize_value = 99999;
    i8 i8_value = 127;
    i16 i16_value = 65535 / 2;
    i32 i32_value = -99999;
    i64 i64_value = -2299999;
    int int_value = 999999;
    long long_value = 999999;
    long long long_long_value = 999999;
    float float_value = 123.123;
    double double_value = 99999.123;
    long double long_double_value = 99999.123;
    bool bool_value = true;

    struct Point {
        int x;
        int y;
    };
    Point temp_point = {.x = 1, .y = 2};

    ASSERT_EQ(sizeof(char *), TYPE_SIZE(string_value));
    ASSERT_EQ(sizeof(char), TYPE_SIZE(char_value));
    ASSERT_EQ(sizeof(unsigned char), TYPE_SIZE(u8_value));
    ASSERT_EQ(sizeof(unsigned short int), TYPE_SIZE(u16_value));
    ASSERT_EQ(sizeof(unsigned int), TYPE_SIZE(u32_value));
    ASSERT_EQ(sizeof(unsigned long int), TYPE_SIZE(u64_value));
    ASSERT_EQ(sizeof(unsigned long int), TYPE_SIZE(usize_value));
    ASSERT_EQ(sizeof(signed char), TYPE_SIZE(i8_value));
    ASSERT_EQ(sizeof(short int), TYPE_SIZE(i16_value));
    ASSERT_EQ(sizeof(int), TYPE_SIZE(i32_value));
    ASSERT_EQ(sizeof(long int), TYPE_SIZE(i64_value));
    ASSERT_EQ(sizeof(int), TYPE_SIZE(int_value));
    ASSERT_EQ(sizeof(long int), TYPE_SIZE(long_value));
    ASSERT_EQ(sizeof(long long int), TYPE_SIZE(long_long_value));
    ASSERT_EQ(sizeof(float), TYPE_SIZE(float_value));
    ASSERT_EQ(sizeof(double), TYPE_SIZE(double_value));
    ASSERT_EQ(sizeof(long double), TYPE_SIZE(long_double_value));
    ASSERT_EQ(sizeof(bool), TYPE_SIZE(bool_value));
    ASSERT_EQ(0, TYPE_SIZE(temp_point));

    void *void_ptr = &string_value;
    bool *bool_ptr = &bool_value;
    u8 *u8_ptr = &u8_value;
    u16 *u16_ptr = &u16_value;
    u32 *u32_ptr = &u32_value;
    u64 *u64_ptr = &u64_value;
    usize *usize_ptr = &usize_value;
    i8 *i8_ptr = &i8_value;
    i16 *i16_ptr = &i16_value;
    i32 *i32_ptr = &i32_value;
    i64 *i64_ptr = &i64_value;
    float *float_ptr = &float_value;
    double *double_ptr = &double_value;
    long double *long_double_ptr = &long_double_value;

    ASSERT_EQ(sizeof(void *), TYPE_SIZE(void_ptr));
    ASSERT_EQ(sizeof(bool *), TYPE_SIZE(bool_ptr));
    ASSERT_EQ(sizeof(u8 *), TYPE_SIZE(u8_ptr));
    ASSERT_EQ(sizeof(u16 *), TYPE_SIZE(u16_ptr));
    ASSERT_EQ(sizeof(u32 *), TYPE_SIZE(u32_ptr));
    ASSERT_EQ(sizeof(u64 *), TYPE_SIZE(u64_ptr));
    ASSERT_EQ(sizeof(usize *), TYPE_SIZE(usize_ptr));
    ASSERT_EQ(sizeof(i8 *), TYPE_SIZE(i8_ptr));
    ASSERT_EQ(sizeof(i16 *), TYPE_SIZE(i16_ptr));
    ASSERT_EQ(sizeof(i32 *), TYPE_SIZE(i32_ptr));
    ASSERT_EQ(sizeof(i64 *), TYPE_SIZE(i64_ptr));
    ASSERT_EQ(sizeof(float *), TYPE_SIZE(float_ptr));
    ASSERT_EQ(sizeof(double *), TYPE_SIZE(double_ptr));
    ASSERT_EQ(sizeof(long double *), TYPE_SIZE(long_double_ptr));
}

TEST(DataTypes, TYPE_SIZE_FROM_TYPE) {
    ASSERT_EQ(sizeof(char), TYPE_SIZE_FROM_TYPE(char));
    ASSERT_EQ(sizeof(unsigned char), TYPE_SIZE_FROM_TYPE(unsigned char));
    ASSERT_EQ(sizeof(unsigned short int),
              TYPE_SIZE_FROM_TYPE(unsigned short int));
    ASSERT_EQ(sizeof(unsigned int), TYPE_SIZE_FROM_TYPE(unsigned int));
    ASSERT_EQ(sizeof(unsigned long int),
              TYPE_SIZE_FROM_TYPE(unsigned long int));
    ASSERT_EQ(sizeof(signed char), TYPE_SIZE_FROM_TYPE(signed char));
    ASSERT_EQ(sizeof(short int), TYPE_SIZE_FROM_TYPE(short int));
    ASSERT_EQ(sizeof(int), TYPE_SIZE_FROM_TYPE(int));
    ASSERT_EQ(sizeof(long int), TYPE_SIZE_FROM_TYPE(long int));
    ASSERT_EQ(sizeof(int), TYPE_SIZE_FROM_TYPE(int));
    ASSERT_EQ(sizeof(long int), TYPE_SIZE_FROM_TYPE(long int));
    ASSERT_EQ(sizeof(long long int), TYPE_SIZE_FROM_TYPE(long long int));
    ASSERT_EQ(sizeof(float), TYPE_SIZE_FROM_TYPE(float));
    ASSERT_EQ(sizeof(double), TYPE_SIZE_FROM_TYPE(double));
    ASSERT_EQ(sizeof(long double), TYPE_SIZE_FROM_TYPE(long double));
    ASSERT_EQ(sizeof(bool), TYPE_SIZE_FROM_TYPE(bool));
}
