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

#include "hex_buffer.h"
}

TEST(HexBuffer, EmptyHexBuffer) {
    HexBuffer *b1 = Hex_from_string(NULL);
    ASSERT_EQ(b1, NULL);

    HexBuffer *b2 = Hex_from_string("");
    ASSERT_EQ(b2, NULL);

    HexBuffer *b3 = Hex_from_string("    ");
    ASSERT_EQ(b3, NULL);

    HexBuffer *b4 = Hex_from_string("A");
    ASSERT_EQ(b4, NULL);

    HexBuffer *b5 = Hex_from_string("ABC");
    ASSERT_EQ(b5, NULL);

    HexBuffer *b6 = Hex_from_string("@##Q@#Q@$FSDDFSDFABC");
    ASSERT_EQ(b6, NULL);
}

TEST(HexBuffer, InvalidHexBuffer) {
    HexBuffer *b1 = Hex_from_string("!@#$%^&*()");
    ASSERT_EQ(b1, NULL);

    HexBuffer *b2 = Hex_from_string("GHikalbcop");
    ASSERT_EQ(b2, NULL);
}

TEST(HexBuffer, ValidHexBuffer) {
    HexBuffer *b1 = Hex_from_string("112233445566AABBCCDD");
    ASSERT_NE(b1, NULL);
    ASSERT_EQ(Hex_length(b1), 10);
    char b1_str[Hex_length(b1) * 2];
    usize return_b1_str_len = Hex_to_string(b1, b1_str, Hex_length(b1) * 2);
    ASSERT_EQ(return_b1_str_len, 20);
    ASSERT_EQ(strlen(b1_str), 20);
    ASSERT_EQ(strcmp(b1_str, "112233445566AABBCCDD"), 0);

    HexBuffer *b2 = Hex_from_string(" AA b B C D      e    f  &*@#($*&)");
    ASSERT_NE(b2, NULL);
    ASSERT_EQ(Hex_length(b2), 4);
    char b2_str[Hex_length(b2) * 2];
    usize return_b2_str_len = Hex_to_string(b2, b2_str, Hex_length(b2) * 2);
    ASSERT_EQ(return_b2_str_len, 8);
    ASSERT_EQ(strlen(b2_str), 8);
    ASSERT_EQ(strcmp(b2_str, "AABBCDEF"), 0);
}
