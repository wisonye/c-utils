#include <gtest/gtest.h>

extern "C" {
#include <string.h>

#include "hex_buffer.h"
}

TEST(HexBuffer, EmptyHexBuffer) {
    HexBuffer *b1 = Hex_from_string(nullptr);
    ASSERT_EQ(b1, nullptr);

    HexBuffer *b2 = Hex_from_string("");
    ASSERT_EQ(b2, nullptr);

    HexBuffer *b3 = Hex_from_string("    ");
    ASSERT_EQ(b3, nullptr);

    HexBuffer *b4 = Hex_from_string("A");
    ASSERT_EQ(b4, nullptr);

    HexBuffer *b5 = Hex_from_string("ABC");
    ASSERT_EQ(b5, nullptr);

    HexBuffer *b6 = Hex_from_string("@##Q@#Q@$FSDDFSDFABC");
    ASSERT_EQ(b6, nullptr);
}

TEST(HexBuffer, InvalidHexBuffer) {
    HexBuffer *b1 = Hex_from_string("!@#$%^&*()");
    ASSERT_EQ(b1, nullptr);

    HexBuffer *b2 = Hex_from_string("GHikalbcop");
    ASSERT_EQ(b2, nullptr);
}

TEST(HexBuffer, ValidHexBuffer) {
    HexBuffer *b1 = Hex_from_string("112233445566AABBCCDD");
    ASSERT_NE(b1, nullptr);
    ASSERT_EQ(Hex_length(b1), 10);
    char b1_str[Hex_length(b1) * 2];
    usize return_b1_str_len = Hex_to_string(b1, b1_str, Hex_length(b1) * 2);
    ASSERT_EQ(return_b1_str_len, 20);
    ASSERT_EQ(strlen(b1_str), 20);
    ASSERT_EQ(strcmp(b1_str, "112233445566AABBCCDD"), 0);

    HexBuffer *b2 = Hex_from_string(" AA b B C D      e    f  &*@#($*&)");
    ASSERT_NE(b2, nullptr);
    ASSERT_EQ(Hex_length(b2), 4);
    char b2_str[Hex_length(b2) * 2];
    usize return_b2_str_len = Hex_to_string(b2, b2_str, Hex_length(b2) * 2);
    ASSERT_EQ(return_b2_str_len, 8);
    ASSERT_EQ(strlen(b2_str), 8);
    ASSERT_EQ(strcmp(b2_str, "AABBCDEF"), 0);
}
