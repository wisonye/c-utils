#include <gtest/gtest.h>

extern "C" {

//
// For comparing the pointer and `NULL`:
//
// Plz Make sure include inside `extern C`
// block. Otherwise, `gtest` will include `std::nullptr_t` (CPP type) which
// doesn't match the type, and you will end up with the following error:
//
// error: invalid operands to binary expression ('const LinkList' and 'const
// std::nullptr_t')
//
#include <stddef.h>
#include <string.h>

#include "string.h"
}

TEST(String, EmptyString) {
    Str empty_str = Str_from_str(NULL);
    ASSERT_EQ(Str_length(&empty_str), 0);
    ASSERT_EQ(Str_as_str(&empty_str), NULL);

    Str_free(&empty_str);
}

TEST(String, StringFromArray) {
    char arr[] = "Unit Test:)";
    Str str = Str_from_arr(arr);
    ASSERT_EQ(Str_length(&str), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(&str), arr), 0);

    Str_free(&str);
    ASSERT_EQ(Str_length(&str), 0);
    ASSERT_EQ(Str_as_str(&str), NULL);
}


TEST(String, StringClone) {
    char arr[] = "Unit Test:)";
    Str str = Str_from_arr(arr);
    ASSERT_EQ(Str_length(&str), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(&str), arr), 0);

    Str clone_1 = Str_clone(&str);
    ASSERT_EQ(Str_length(&clone_1), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(&clone_1), arr), 0);

    Str empty_str = Str_from_str("");
    Str clone_from_empty = Str_clone(&empty_str);
    ASSERT_EQ(Str_length(&clone_from_empty), 0);
    ASSERT_EQ(Str_as_str(&clone_from_empty), NULL);

    Str_free(&str);
    Str_free(&clone_1);
    Str_free(&empty_str);
    Str_free(&clone_from_empty);
}

