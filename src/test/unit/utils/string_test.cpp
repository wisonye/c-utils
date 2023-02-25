#include <gtest/gtest.h>

extern "C" {
#include "../../../utils/string.h"
}

TEST(String, StrInit) {
    struct Str str;
    Str_init(&str);
    ASSERT_EQ(Str_length(&str), 0);
    ASSERT_EQ(Str_capacity(&str), 0);
    ASSERT_EQ(Str_as_str(&str), nullptr);

    Str_push_str(&str, "12345");
    ASSERT_EQ(Str_length(&str), 5);
    ASSERT_EQ(Str_capacity(&str), Str_length(&str) + 1);
    ASSERT_EQ(strcmp(Str_as_str(&str), "12345"), 0);
    Str_free_buffer_only(&str);
}

TEST(String, StrInitWithCapacity) {
    struct Str str;
    Str_init_with_capacity(&str, 10);
    ASSERT_EQ(Str_length(&str), 0);
    ASSERT_EQ(Str_capacity(&str), 10);
    ASSERT_NE(Str_as_str(&str), nullptr);

    Str_push_str(&str, "12345");
    ASSERT_EQ(Str_length(&str), 5);
    ASSERT_EQ(Str_capacity(&str), 10);
    ASSERT_EQ(strcmp(Str_as_str(&str), "12345"), 0);

    Str_push_str(&str, "ABCD");
    ASSERT_EQ(Str_length(&str), strlen("12345ABCD"));
    ASSERT_EQ(Str_capacity(&str), 10);
    ASSERT_EQ(strcmp(Str_as_str(&str), "12345ABCD"), 0);

    // The next push should case realloc!!!
    Str_push_str(&str, "qwerty");
    ASSERT_EQ(Str_length(&str), strlen("12345ABCDqwerty"));
    ASSERT_EQ(Str_capacity(&str), Str_length(&str) + 1);
    ASSERT_EQ(strcmp(Str_as_str(&str), "12345ABCDqwerty"), 0);

    Str_free_buffer_only(&str);
}

TEST(String, EmptyString) {
    SMART_STRING(empty_str) = Str_from_str(nullptr);
    ASSERT_EQ(Str_length(empty_str), 0);
    ASSERT_EQ(Str_capacity(empty_str), 0);
    ASSERT_EQ(Str_as_str(empty_str), nullptr);
}

TEST(String, EmptyStringWithCapacity) {
    SMART_STRING(empty_str) = Str_from_empty_with_capacity(10);
    ASSERT_EQ(Str_length(empty_str), 0);
    ASSERT_EQ(Str_capacity(empty_str), 10);
    ASSERT_NE(Str_as_str(empty_str), nullptr);

    Str_push_str(empty_str, "12345");
    ASSERT_EQ(Str_length(empty_str), 5);
    ASSERT_EQ(Str_capacity(empty_str), 10);
    ASSERT_EQ(strcmp(Str_as_str(empty_str), "12345"), 0);

    Str_push_str(empty_str, "ABCD");
    ASSERT_EQ(Str_length(empty_str), strlen("12345ABCD"));
    ASSERT_EQ(Str_capacity(empty_str), 10);
    ASSERT_EQ(strcmp(Str_as_str(empty_str), "12345ABCD"), 0);

    // The next push should case realloc!!!
    Str_push_str(empty_str, "qwerty");
    ASSERT_EQ(Str_length(empty_str), strlen("12345ABCDqwerty"));
    ASSERT_EQ(Str_capacity(empty_str), Str_length(empty_str) + 1);
    ASSERT_EQ(strcmp(Str_as_str(empty_str), "12345ABCDqwerty"), 0);
}

TEST(String, StringFromArray) {
    char arr[] = "Unit Test:)";
    SMART_STRING(str) = Str_from_arr(arr);
    ASSERT_EQ(Str_length(str), strlen(arr));
    ASSERT_EQ(Str_capacity(str), Str_length(str) + 1);
    ASSERT_EQ(strcmp(Str_as_str(str), arr), 0);
}

TEST(String, StringClone) {
    char arr[] = "Unit Test:)";
    SMART_STRING(str) = Str_from_arr(arr);
    ASSERT_EQ(Str_length(str), strlen(arr));
    ASSERT_EQ(Str_capacity(str), Str_length(str) + 1);
    ASSERT_EQ(strcmp(Str_as_str(str), arr), 0);

    SMART_STRING(clone_1) = Str_clone_from(str);
    ASSERT_EQ(Str_length(clone_1), strlen(arr));
    ASSERT_EQ(Str_capacity(clone_1), Str_length(clone_1) + 1);
    ASSERT_EQ(strcmp(Str_as_str(clone_1), arr), 0);

    SMART_STRING(empty_str) = Str_from_str("");
    SMART_STRING(clone_from_empty) = Str_clone_from(empty_str);
    ASSERT_EQ(Str_length(clone_from_empty), 0);
    ASSERT_EQ(Str_capacity(clone_from_empty), 0);
    ASSERT_EQ(Str_as_str(clone_from_empty), nullptr);
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
    ASSERT_EQ(Str_capacity(temp_str), 0);
    ASSERT_EQ(Str_as_str(temp_str), nullptr);
}

TEST(String, Push) {
    SMART_STRING(empty_str) = Str_from_empty();
    SMART_STRING(init_empty_str) = Str_from_empty();
    SMART_STRING(original_str) = Str_from_str("Wison Ye:)");
    SMART_STRING(other_str) = Str_from_str("Other string.");

    Str_push_str(init_empty_str, Str_as_str(original_str));
    ASSERT_EQ(Str_length(init_empty_str), Str_length(original_str));
    ASSERT_EQ(Str_capacity(init_empty_str), Str_length(original_str) + 1);
    ASSERT_EQ(Str_length(init_empty_str), strlen(Str_as_str(original_str)));

    Str_push_str(original_str, Str_as_str(original_str));
    ASSERT_EQ(Str_length(original_str), Str_length(init_empty_str) * 2);
    ASSERT_EQ(Str_capacity(original_str), Str_length(original_str) + 1);

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
    ASSERT_EQ(Str_capacity(original_str), Str_length(original_str) + 1);
}

TEST(String, InsertAtBegin) {
    SMART_STRING(empty_str) = Str_from_empty();
    SMART_STRING(init_empty_str) = Str_from_empty_with_capacity(14);
    SMART_STRING(other_str) = Str_from_str("12345");

    ASSERT_EQ(Str_capacity(empty_str), 0);
    ASSERT_EQ(Str_capacity(init_empty_str), 14);
    ASSERT_EQ(Str_capacity(other_str), Str_length(other_str) + 1);

    Str_push_str(init_empty_str, "6789");
    Str_insert_other_to_begin(init_empty_str, other_str);
    Str_insert_str_to_begin(init_empty_str, "0000");

    ASSERT_EQ(Str_length(init_empty_str), strlen("0000123456789"));
    ASSERT_EQ(Str_capacity(init_empty_str), Str_length(init_empty_str) + 1);
}

TEST(String, MoveSemantic) {
    SMART_STRING(s1) = Str_from_str("123456");
    SMART_STRING(clone_from_s1) = Str_clone_from(s1);
    ASSERT_EQ(Str_length(clone_from_s1), Str_length(s1));
    ASSERT_EQ(Str_capacity(clone_from_s1), Str_length(clone_from_s1) + 1);
    ASSERT_EQ(strcmp(Str_as_str(clone_from_s1), Str_as_str(s1)), 0);

    SMART_STRING(move_from_clone_s1) = Str_move_from(clone_from_s1);
    ASSERT_EQ(Str_length(move_from_clone_s1), Str_length(s1));
    ASSERT_EQ(Str_capacity(move_from_clone_s1),
              Str_length(move_from_clone_s1) + 1);
    ASSERT_EQ(strcmp(Str_as_str(move_from_clone_s1), Str_as_str(s1)), 0);

    // `clone_from_s1` should be empty after MOVE to `move_from_clone_s1`
    ASSERT_EQ(Str_length(clone_from_s1), 0);
    ASSERT_EQ(Str_capacity(clone_from_s1), 0);
    ASSERT_EQ(Str_as_str(clone_from_s1), nullptr);
}
