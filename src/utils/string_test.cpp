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

#include "string.h"
}

TEST(String, EmptyString) {
    String empty_str = Str_from_str(NULL);
    ASSERT_EQ(Str_length(empty_str), 0);
    ASSERT_EQ(Str_as_str(empty_str), NULL);

    Str_free(empty_str);
}

TEST(String, StringFromArray) {
    char arr[] = "Unit Test:)";
    String str = Str_from_arr(arr);
    ASSERT_EQ(Str_length(str), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(str), arr), 0);

    Str_free(str);
}

TEST(String, StringClone) {
    char arr[] = "Unit Test:)";
    String str = Str_from_arr(arr);
    ASSERT_EQ(Str_length(str), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(str), arr), 0);

    String clone_1 = Str_clone(str);
    ASSERT_EQ(Str_length(clone_1), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(clone_1), arr), 0);

    String empty_str = Str_from_str("");
    String clone_from_empty = Str_clone(empty_str);
    ASSERT_EQ(Str_length(clone_from_empty), 0);
    ASSERT_EQ(Str_as_str(clone_from_empty), NULL);

    Str_free(str);
    Str_free(clone_1);
    Str_free(empty_str);
    Str_free(clone_from_empty);
}

TEST(String, FindSubString) {
    String original_str = Str_from_str("Wison Ye:)");

    ASSERT_EQ(Str_index_of(original_str, ""), -1);
    ASSERT_EQ(Str_index_of(original_str, " "), 5);
    ASSERT_EQ(Str_index_of(original_str, "w"), 0);
    ASSERT_EQ(Str_index_of(original_str, "W"), 0);
    ASSERT_EQ(Str_index_of(original_str, ":)"), 8);
    ASSERT_EQ(Str_index_of(original_str, "b"), -1);
    ASSERT_EQ(Str_index_of_case_sensitive(original_str, "w"), -1);
    ASSERT_EQ(Str_index_of_case_sensitive(original_str, "Y"), 6);

    Str_free(original_str);
}

TEST(String, CheckContainsSubString) {
    String original_str = Str_from_str("Wison Ye:)");

    ASSERT_EQ(Str_contains(original_str, (char *)""), false);
    ASSERT_EQ(Str_contains(original_str, (char *)" "), true);
    ASSERT_EQ(Str_contains(original_str, (char *)"w"), true);
    ASSERT_EQ(Str_contains(original_str, (char *)"W"), true);
    ASSERT_EQ(Str_contains(original_str, (char *)":)"), true);
    ASSERT_EQ(Str_contains(original_str, (char *)"b"), false);
    ASSERT_EQ(Str_contains(original_str, (char *)"fi"), false);

    Str_free(original_str);
}

TEST(String, ResetToEmpty) {
    String temp_str = Str_from_str("Wison Ye:)");
    Str_reset_to_empty(temp_str);

    ASSERT_EQ(Str_length(temp_str), 0);
    ASSERT_EQ(Str_as_str(temp_str), NULL);

    Str_free(temp_str);
}

TEST(String, Push) {
    String empty_str = Str_from_empty();
    String init_empty_str = Str_from_empty();
    String original_str = Str_from_str("Wison Ye:)");
    String other_str = Str_from_str("Other string.");

    Str_push_str(init_empty_str, Str_as_str(original_str));
    ASSERT_EQ(Str_length(init_empty_str), Str_length(original_str));
    ASSERT_EQ(Str_length(init_empty_str), strlen(Str_as_str(original_str)));

    Str_push_str(original_str, Str_as_str(original_str));
    ASSERT_EQ(Str_length(original_str), Str_length(init_empty_str) * 2);

    Str_reset_to_empty(original_str);
    Str_push_other(original_str, other_str);
    Str_push_other(original_str, other_str);
    /* printf( */
    /*     "\n>>> String Push - orignal aftger push with other, len: %lu, value:
     * " */
    /*     "%s", */
    /*     Str_length(original_str), Str_as_str(original_str)); */
    ASSERT_EQ(Str_length(original_str), Str_length(other_str) * 2);

    Str_free(empty_str);
    Str_free(init_empty_str);
    Str_free(original_str);
    Str_free(other_str);
}

TEST(String, InsertAtBegin) {
    String empty_str = Str_from_empty();
    String init_empty_str = Str_from_empty();
    String other_str = Str_from_str("12345");

    Str_push_str(init_empty_str, "6789");
    Str_insert_other_to_begin(init_empty_str, other_str);
    Str_insert_str_to_begin(init_empty_str, "0000");
    /* printf("\n>>> String InsertAtBegin - init_empty_str len: %lu, value: %s",
     */
    /*        Str_length(init_empty_str), Str_as_str(init_empty_str)); */
    ASSERT_EQ(Str_length(init_empty_str), strlen("0000123456789"));

    Str_free(empty_str);
    Str_free(init_empty_str);
    Str_free(other_str);
}
