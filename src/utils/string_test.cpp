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
    SMART_STRING(empty_str) = Str_from_str(NULL);
    ASSERT_EQ(Str_length(empty_str), 0);
    ASSERT_EQ(Str_as_str(empty_str), NULL);
}

TEST(String, StringFromArray) {
    char arr[] = "Unit Test:)";
    SMART_STRING(str) = Str_from_arr(arr);
    ASSERT_EQ(Str_length(str), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(str), arr), 0);
}

TEST(String, StringClone) {
    char arr[] = "Unit Test:)";
    SMART_STRING(str) = Str_from_arr(arr);
    ASSERT_EQ(Str_length(str), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(str), arr), 0);

    SMART_STRING(clone_1) = Str_clone(str);
    ASSERT_EQ(Str_length(clone_1), strlen(arr));
    ASSERT_EQ(strcmp(Str_as_str(clone_1), arr), 0);

    SMART_STRING(empty_str) = Str_from_str("");
    SMART_STRING(clone_from_empty) = Str_clone(empty_str);
    ASSERT_EQ(Str_length(clone_from_empty), 0);
    ASSERT_EQ(Str_as_str(clone_from_empty), NULL);
}

TEST(String, FindSubString) {
    SMART_STRING(original_str) = Str_from_str("Wison Ye:)");

    ASSERT_EQ(Str_index_of(original_str, ""), -1);
    ASSERT_EQ(Str_index_of(original_str, " "), 5);
    ASSERT_EQ(Str_index_of(original_str, "w"), 0);
    ASSERT_EQ(Str_index_of(original_str, "W"), 0);
    ASSERT_EQ(Str_index_of(original_str, ":)"), 8);
    ASSERT_EQ(Str_index_of(original_str, "b"), -1);
    ASSERT_EQ(Str_index_of_case_sensitive(original_str, "w"), -1);
    ASSERT_EQ(Str_index_of_case_sensitive(original_str, "Y"), 6);
}

TEST(String, CheckContainsSubString) {
    SMART_STRING(original_str) = Str_from_str("Wison Ye:)");

    ASSERT_EQ(Str_contains(original_str, (char *)""), false);
    ASSERT_EQ(Str_contains(original_str, (char *)" "), true);
    ASSERT_EQ(Str_contains(original_str, (char *)"w"), true);
    ASSERT_EQ(Str_contains(original_str, (char *)"W"), true);
    ASSERT_EQ(Str_contains(original_str, (char *)":)"), true);
    ASSERT_EQ(Str_contains(original_str, (char *)"b"), false);
    ASSERT_EQ(Str_contains(original_str, (char *)"fi"), false);
}

TEST(String, ResetToEmpty) {
    SMART_STRING(temp_str) = Str_from_str("Wison Ye:)");
    Str_reset_to_empty(temp_str);

    ASSERT_EQ(Str_length(temp_str), 0);
    ASSERT_EQ(Str_as_str(temp_str), NULL);
}

TEST(String, Push) {
    SMART_STRING(empty_str) = Str_from_empty();
    SMART_STRING(init_empty_str) = Str_from_empty();
    SMART_STRING(original_str) = Str_from_str("Wison Ye:)");
    SMART_STRING(other_str) = Str_from_str("Other string.");

    Str_push_str(init_empty_str, Str_as_str(original_str));
    ASSERT_EQ(Str_length(init_empty_str), Str_length(original_str));
    ASSERT_EQ(Str_length(init_empty_str), strlen(Str_as_str(original_str)));

    Str_push_str(original_str, Str_as_str(original_str));
    ASSERT_EQ(Str_length(original_str), Str_length(init_empty_str) * 2);

    Str_reset_to_empty(original_str);
    Str_push_other(original_str, other_str);
    Str_push_other(original_str, other_str);
    /* printf( */
    /*     "\n>>> SMART_STRING(Push - orignal aftger push with other, len: %lu,
     * value:
     * " */
    /*     "%s", */
    /*     Str_length(original_str), Str_as_str(original_str)); */
    ASSERT_EQ(Str_length(original_str), Str_length(other_str) * 2);
}

TEST(String, InsertAtBegin) {
    SMART_STRING(empty_str) = Str_from_empty();
    SMART_STRING(init_empty_str) = Str_from_empty();
    SMART_STRING(other_str) = Str_from_str("12345");

    Str_push_str(init_empty_str, "6789");
    Str_insert_other_to_begin(init_empty_str, other_str);
    Str_insert_str_to_begin(init_empty_str, "0000");
    /* printf("\n>>> SMART_STRING(InsertAtBegin - init_empty_str len: %lu,
     * value: %s",
     */
    /*        Str_length(init_empty_str), Str_as_str(init_empty_str)); */
    ASSERT_EQ(Str_length(init_empty_str), strlen("0000123456789"));
}
