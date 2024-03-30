#include <gtest/gtest.h>

extern "C" {
#include "../../../utils/heap_string.h"
}

TEST(String, StrInit) {
    struct HeapString str;
    HS_init(&str);
    ASSERT_EQ(HS_length(&str), 0);
    ASSERT_EQ(HS_capacity(&str), 0);
    ASSERT_EQ(HS_as_str(&str), nullptr);

    HS_push_str(&str, "12345");
    ASSERT_EQ(HS_length(&str), 5);
    ASSERT_EQ(HS_capacity(&str), HS_length(&str) + 1);
    ASSERT_EQ(strcmp(HS_as_str(&str), "12345"), 0);
    HS_free_buffer_only(&str);
}

TEST(String, StrInitWithCapacity) {
    struct HeapString str;
    HS_init_with_capacity(&str, 10);
    ASSERT_EQ(HS_length(&str), 0);
    ASSERT_EQ(HS_capacity(&str), 10);
    ASSERT_NE(HS_as_str(&str), nullptr);

    HS_push_str(&str, "12345");
    ASSERT_EQ(HS_length(&str), 5);
    ASSERT_EQ(HS_capacity(&str), 10);
    ASSERT_EQ(strcmp(HS_as_str(&str), "12345"), 0);

    HS_push_str(&str, "ABCD");
    ASSERT_EQ(HS_length(&str), strlen("12345ABCD"));
    ASSERT_EQ(HS_capacity(&str), 10);
    ASSERT_EQ(strcmp(HS_as_str(&str), "12345ABCD"), 0);

    // The next push should case realloc!!!
    HS_push_str(&str, "qwerty");
    ASSERT_EQ(HS_length(&str), strlen("12345ABCDqwerty"));
    ASSERT_EQ(HS_capacity(&str), HS_length(&str) + 1);
    ASSERT_EQ(strcmp(HS_as_str(&str), "12345ABCDqwerty"), 0);

    HS_free_buffer_only(&str);
}

TEST(String, EmptyString) {
    defer_string(empty_str) = HS_from_str(nullptr);
    ASSERT_EQ(HS_length(empty_str), 0);
    ASSERT_EQ(HS_capacity(empty_str), 0);
    ASSERT_EQ(HS_as_str(empty_str), nullptr);
}

TEST(String, EmptyStringWithCapacity) {
    defer_string(empty_str) = HS_from_empty_with_capacity(10);
    ASSERT_EQ(HS_length(empty_str), 0);
    ASSERT_EQ(HS_capacity(empty_str), 10);
    ASSERT_NE(HS_as_str(empty_str), nullptr);

    HS_push_str(empty_str, "12345");
    ASSERT_EQ(HS_length(empty_str), 5);
    ASSERT_EQ(HS_capacity(empty_str), 10);
    ASSERT_EQ(strcmp(HS_as_str(empty_str), "12345"), 0);

    HS_push_str(empty_str, "ABCD");
    ASSERT_EQ(HS_length(empty_str), strlen("12345ABCD"));
    ASSERT_EQ(HS_capacity(empty_str), 10);
    ASSERT_EQ(strcmp(HS_as_str(empty_str), "12345ABCD"), 0);

    // The next push should case realloc!!!
    HS_push_str(empty_str, "qwerty");
    ASSERT_EQ(HS_length(empty_str), strlen("12345ABCDqwerty"));
    ASSERT_EQ(HS_capacity(empty_str), HS_length(empty_str) + 1);
    ASSERT_EQ(strcmp(HS_as_str(empty_str), "12345ABCDqwerty"), 0);
}

TEST(String, StringFromArray) {
    char arr[]        = "Unit Test:)";
    defer_string(str) = HS_from_arr(arr);
    ASSERT_EQ(HS_length(str), strlen(arr));
    ASSERT_EQ(HS_capacity(str), HS_length(str) + 1);
    ASSERT_EQ(strcmp(HS_as_str(str), arr), 0);
}

TEST(String, StringFromStrWithPosAndCount) {
    const char temp_str[]  = "ABCD";
    defer_string(from_str) = HS_from_str_with_pos(temp_str, 0, 4);
    ASSERT_EQ(HS_length(from_str), strlen(temp_str));
    ASSERT_EQ(HS_capacity(from_str), HS_length(from_str) + 1);
    ASSERT_EQ(strcmp(HS_as_str(from_str), temp_str), 0);

    defer_string(from_str_2) = HS_from_str_with_pos(temp_str, 2, 2);
    ASSERT_EQ(HS_length(from_str_2), 2);
    ASSERT_EQ(HS_capacity(from_str_2), 3);
    ASSERT_EQ(strcmp(HS_as_str(from_str_2), "CD"), 0);

    defer_string(from_str_3) = HS_from_str_with_pos(temp_str, -1, 2);
    ASSERT_EQ(HS_length(from_str_3), 0);
    ASSERT_EQ(HS_capacity(from_str_3), 0);
    ASSERT_EQ(HS_as_str(from_str_3), nullptr);

    defer_string(from_str_4) = HS_from_str_with_pos(temp_str, 0, -1);
    ASSERT_EQ(HS_length(from_str_4), 0);
    ASSERT_EQ(HS_capacity(from_str_4), 0);
    ASSERT_EQ(HS_as_str(from_str_4), nullptr);
}

TEST(String, StringClone) {
    char arr[]        = "Unit Test:)";
    defer_string(str) = HS_from_arr(arr);
    ASSERT_EQ(HS_length(str), strlen(arr));
    ASSERT_EQ(HS_capacity(str), HS_length(str) + 1);
    ASSERT_EQ(strcmp(HS_as_str(str), arr), 0);

    defer_string(clone_1) = HS_clone_from(str);
    ASSERT_EQ(HS_length(clone_1), strlen(arr));
    ASSERT_EQ(HS_capacity(clone_1), HS_length(clone_1) + 1);
    ASSERT_EQ(strcmp(HS_as_str(clone_1), arr), 0);

    defer_string(empty_str)        = HS_from_str("");
    defer_string(clone_from_empty) = HS_clone_from(empty_str);
    ASSERT_EQ(HS_length(clone_from_empty), 0);
    ASSERT_EQ(HS_capacity(clone_from_empty), 0);
    ASSERT_EQ(HS_as_str(clone_from_empty), nullptr);
}

TEST(String, FindSubString) {
    defer_string(original_str) = HS_from_str("Wison Ye:)");

    ASSERT_EQ(HS_index_of(original_str, ""), -1);
    ASSERT_EQ(HS_index_of(original_str, " "), 5);
    ASSERT_EQ(HS_index_of(original_str, "w"), 0);
    ASSERT_EQ(HS_index_of(original_str, "W"), 0);
    ASSERT_EQ(HS_index_of(original_str, ":)"), 8);
    ASSERT_EQ(HS_index_of(original_str, "b"), -1);
    ASSERT_EQ(HS_index_of_case_sensitive(original_str, "w"), -1);
    ASSERT_EQ(HS_index_of_case_sensitive(original_str, "Y"), 6);
}

TEST(String, CheckContainsSubString) {
    defer_string(original_str) = HS_from_str("Wison Ye:)");

    ASSERT_EQ(HS_contains(original_str, (char *)""), false);
    ASSERT_EQ(HS_contains(original_str, (char *)" "), true);
    ASSERT_EQ(HS_contains(original_str, (char *)"w"), true);
    ASSERT_EQ(HS_contains(original_str, (char *)"W"), true);
    ASSERT_EQ(HS_contains(original_str, (char *)":)"), true);
    ASSERT_EQ(HS_contains(original_str, (char *)"b"), false);
    ASSERT_EQ(HS_contains(original_str, (char *)"fi"), false);
}

TEST(String, ResetToEmpty) {
    defer_string(temp_str) = HS_from_str("Wison Ye:)");
    HS_reset_to_empty(temp_str);

    ASSERT_EQ(HS_length(temp_str), 0);
    ASSERT_EQ(HS_capacity(temp_str), 0);
    ASSERT_EQ(HS_as_str(temp_str), nullptr);
}

TEST(String, ResetToEmptyWithoutFreeingBuffer) {
    defer_string(temp_str) = HS_from_str("Wison Ye:)");
    HS_reset_to_empty_without_freeing_buffer(temp_str);

    ASSERT_EQ(HS_length(temp_str), 0);
    ASSERT_EQ(HS_capacity(temp_str), 0);
    ASSERT_EQ(HS_as_str(temp_str), nullptr);
}

TEST(String, Push) {
    defer_string(empty_str)      = HS_from_empty();
    defer_string(init_empty_str) = HS_from_empty();
    defer_string(original_str)   = HS_from_str("Wison Ye:)");
    defer_string(other_str)      = HS_from_str("Other string.");

    HS_push_str(init_empty_str, HS_as_str(original_str));
    ASSERT_EQ(HS_length(init_empty_str), HS_length(original_str));
    ASSERT_EQ(HS_capacity(init_empty_str), HS_length(original_str) + 1);
    ASSERT_EQ(HS_length(init_empty_str), strlen(HS_as_str(original_str)));

    HS_push_str(original_str, HS_as_str(original_str));
    ASSERT_EQ(HS_length(original_str), HS_length(init_empty_str) * 2);
    ASSERT_EQ(HS_capacity(original_str), HS_length(original_str) + 1);

    HS_reset_to_empty(original_str);
    HS_push_other(original_str, other_str);
    HS_push_other(original_str, other_str);
    /* printf( */
    /*     "\n>>> defer_string(Push - orignal aftger push with other, len: %lu,
     * value:
     * " */
    /*     "%s", */
    /*     HS_length(original_str), HS_as_str(original_str)); */
    ASSERT_EQ(HS_length(original_str), HS_length(other_str) * 2);
    ASSERT_EQ(HS_capacity(original_str), HS_length(original_str) + 1);
}

TEST(String, InsertAtBegin) {
    defer_string(empty_str)      = HS_from_empty();
    defer_string(init_empty_str) = HS_from_empty_with_capacity(14);
    defer_string(other_str)      = HS_from_str("12345");

    ASSERT_EQ(HS_capacity(empty_str), 0);
    ASSERT_EQ(HS_capacity(init_empty_str), 14);
    ASSERT_EQ(HS_capacity(other_str), HS_length(other_str) + 1);

    HS_push_str(init_empty_str, "6789");
    HS_insert_other_to_begin(init_empty_str, other_str);
    HS_insert_str_to_begin(init_empty_str, "0000");

    ASSERT_EQ(HS_length(init_empty_str), strlen("0000123456789"));
    ASSERT_EQ(HS_capacity(init_empty_str), HS_length(init_empty_str) + 1);
}

TEST(String, MoveSemantic) {
    defer_string(s1)            = HS_from_str("123456");
    defer_string(clone_from_s1) = HS_clone_from(s1);
    ASSERT_EQ(HS_length(clone_from_s1), HS_length(s1));
    ASSERT_EQ(HS_capacity(clone_from_s1), HS_length(clone_from_s1) + 1);
    ASSERT_EQ(strcmp(HS_as_str(clone_from_s1), HS_as_str(s1)), 0);

    defer_string(move_from_clone_s1) = HS_move_from(clone_from_s1);
    ASSERT_EQ(HS_length(move_from_clone_s1), HS_length(s1));
    ASSERT_EQ(HS_capacity(move_from_clone_s1),
              HS_length(move_from_clone_s1) + 1);
    ASSERT_EQ(strcmp(HS_as_str(move_from_clone_s1), HS_as_str(s1)), 0);

    // `clone_from_s1` should be empty after MOVE to `move_from_clone_s1`
    ASSERT_EQ(HS_length(clone_from_s1), 0);
    ASSERT_EQ(HS_capacity(clone_from_s1), 0);
    ASSERT_EQ(HS_as_str(clone_from_s1), nullptr);
}
