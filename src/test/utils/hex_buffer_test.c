#include "../../utils/hex_buffer.h"

#include <string.h>
#include <unity.h>

#include "./hex_buffer_test.h"

///
///
///
void test_hex_buffer_empty_hex_buffer(void) {
    HexBuffer b1 = Hex_from_string(NULL);
    TEST_ASSERT_NULL(b1);

    HexBuffer b2 = Hex_from_string("");
    TEST_ASSERT_NULL(b2);

    HexBuffer b3 = Hex_from_string("    ");
    TEST_ASSERT_NULL(b3);

    HexBuffer b4 = Hex_from_string("A");
    TEST_ASSERT_NULL(b4);

    HexBuffer b5 = Hex_from_string("ABC");
    TEST_ASSERT_NULL(b5);

    HexBuffer b6 = Hex_from_string("@##Q@#Q@$FSDDFSDFABC");
    TEST_ASSERT_NULL(b6);
}

///
///
///
void test_hex_buffer_invalid_buffer(void) {
    HexBuffer b1 = Hex_from_string("!@#$%^&*()");
    TEST_ASSERT_NULL(b1);

    HexBuffer b2 = Hex_from_string("GHikalbcop");
    TEST_ASSERT_NULL(b2);
}

///
///
///
void test_hex_buffer_valid_buffer(void) {
    HexBuffer b1 = Hex_from_string("112233445566AABBCCDD");
    TEST_ASSERT_NOT_NULL(b1);
    TEST_ASSERT_EQUAL_UINT(Hex_length(b1), 10);

    usize return_b1_buffer_size = Hex_length(b1) * 2 + 1;
    char b1_str[return_b1_buffer_size];
    usize return_b1_str_len = Hex_to_string(b1, b1_str, return_b1_buffer_size);
    TEST_ASSERT_EQUAL_UINT(return_b1_str_len, 20);
    TEST_ASSERT_EQUAL_UINT(strlen(b1_str), 20);
    TEST_ASSERT_EQUAL_STRING(b1_str, "112233445566AABBCCDD");

    HexBuffer b2 = Hex_from_string(" AA b B C D      e    f  &*@#($*&)");
    TEST_ASSERT_NOT_NULL(b2);
    TEST_ASSERT_EQUAL_UINT(Hex_length(b2), 4);

    usize return_b2_buffer_size = Hex_length(b2) * 2 + 1;
    char b2_str[return_b2_buffer_size];
    usize return_b2_str_len = Hex_to_string(b2, b2_str, return_b2_buffer_size);
    TEST_ASSERT_EQUAL_UINT(return_b2_str_len, 8);
    TEST_ASSERT_EQUAL_UINT(strlen(b2_str), 8);
    TEST_ASSERT_EQUAL_STRING(b2_str, "AABBCDEF");
}
