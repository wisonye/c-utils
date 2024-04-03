#include "./string_test.h"

#include <string.h>
#include <unity.h>

#include "../../utils/heap_string.h"

void test_string_init(void) {
    struct HeapString str;
    HS_init(&str);
    TEST_ASSERT_EQUAL_UINT(HS_length(&str), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(&str), 0);
    TEST_ASSERT_NULL(HS_as_str(&str));

    HS_push_str(&str, "12345");
    TEST_ASSERT_EQUAL_UINT(HS_length(&str), 5);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(&str), HS_length(&str) + 1);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(&str), "12345");
    HS_free_buffer_only(&str);
}

void test_string_init_with_capacity(void) {
    struct HeapString str;
    HS_init_with_capacity(&str, 10);
    TEST_ASSERT_EQUAL_UINT(HS_length(&str), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(&str), 10);
    TEST_ASSERT_NOT_NULL(HS_as_str(&str));

    HS_push_str(&str, "12345");
    TEST_ASSERT_EQUAL_UINT(HS_length(&str), 5);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(&str), 10);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(&str), "12345");

    HS_push_str(&str, "ABCD");
    TEST_ASSERT_EQUAL_UINT(HS_length(&str), strlen("12345ABCD"));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(&str), 10);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(&str), "12345ABCD");

    // The next push should case realloc!!!
    HS_push_str(&str, "qwerty");
    TEST_ASSERT_EQUAL_UINT(HS_length(&str), strlen("12345ABCDqwerty"));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(&str), HS_length(&str) + 1);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(&str), "12345ABCDqwerty");

    HS_free_buffer_only(&str);
}

void test_string_empty_string(void) {
    defer_string(empty_str) = HS_from_str(NULL);
    TEST_ASSERT_EQUAL_UINT(HS_length(empty_str), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(empty_str), 0);
    TEST_ASSERT_NULL(HS_as_str(empty_str));
}

void test_string_empty_string_with_capacity(void) {
    defer_string(empty_str) = HS_from_empty_with_capacity(10);
    TEST_ASSERT_EQUAL_UINT(HS_length(empty_str), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(empty_str), 10);
    TEST_ASSERT_NOT_NULL(HS_as_str(empty_str));

    HS_push_str(empty_str, "12345");
    TEST_ASSERT_EQUAL_UINT(HS_length(empty_str), 5);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(empty_str), 10);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(empty_str), "12345");

    HS_push_str(empty_str, "ABCD");
    TEST_ASSERT_EQUAL_UINT(HS_length(empty_str), strlen("12345ABCD"));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(empty_str), 10);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(empty_str), "12345ABCD");

    // The next push should case realloc!!!
    HS_push_str(empty_str, "qwerty");
    TEST_ASSERT_EQUAL_UINT(HS_length(empty_str), strlen("12345ABCDqwerty"));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(empty_str), HS_length(empty_str) + 1);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(empty_str), "12345ABCDqwerty");
}

void test_string_from_array(void) {
    char arr[]        = "Unit Test:)";
    defer_string(str) = HS_from_arr(arr);
    TEST_ASSERT_EQUAL_UINT(HS_length(str), strlen(arr));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(str), HS_length(str) + 1);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(str), arr);
}

void test_string_from_str_with_pos_and_count(void) {
    const char temp_str[]  = "ABCD";
    defer_string(from_str) = HS_from_str_with_pos(temp_str, 0, 4);
    TEST_ASSERT_EQUAL_UINT(HS_length(from_str), strlen(temp_str));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(from_str), HS_length(from_str) + 1);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(from_str), temp_str);

    defer_string(from_str_2) = HS_from_str_with_pos(temp_str, 2, 2);
    TEST_ASSERT_EQUAL_UINT(HS_length(from_str_2), 2);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(from_str_2), 3);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(from_str_2), "CD");

    defer_string(from_str_3) = HS_from_str_with_pos(temp_str, -1, 2);
    TEST_ASSERT_EQUAL_UINT(HS_length(from_str_3), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(from_str_3), 0);
    TEST_ASSERT_NULL(HS_as_str(from_str_3));

    defer_string(from_str_4) = HS_from_str_with_pos(temp_str, 0, -1);
    TEST_ASSERT_EQUAL_UINT(HS_length(from_str_4), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(from_str_4), 0);
    TEST_ASSERT_NULL(HS_as_str(from_str_4));
}

void test_string_clone(void) {
    char arr[]        = "Unit Test:)";
    defer_string(str) = HS_from_arr(arr);
    TEST_ASSERT_EQUAL_UINT(HS_length(str), strlen(arr));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(str), HS_length(str) + 1);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(str), arr);

    defer_string(clone_1) = HS_clone_from(str);
    TEST_ASSERT_EQUAL_UINT(HS_length(clone_1), strlen(arr));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(clone_1), HS_length(clone_1) + 1);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(clone_1), arr);

    defer_string(empty_str)        = HS_from_str("");
    defer_string(clone_from_empty) = HS_clone_from(empty_str);
    TEST_ASSERT_EQUAL_UINT(HS_length(clone_from_empty), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(clone_from_empty), 0);
    TEST_ASSERT_NULL(HS_as_str(clone_from_empty));
}

void test_string_find_substring(void) {
    defer_string(original_str) = HS_from_str("Wison Ye:)");

    TEST_ASSERT_EQUAL_INT(HS_index_of(original_str, ""), -1);
    TEST_ASSERT_EQUAL_INT(HS_index_of(original_str, " "), 5);
    TEST_ASSERT_EQUAL_INT(HS_index_of(original_str, "w"), 0);
    TEST_ASSERT_EQUAL_INT(HS_index_of(original_str, "W"), 0);
    TEST_ASSERT_EQUAL_INT(HS_index_of(original_str, ":)"), 8);
    TEST_ASSERT_EQUAL_INT(HS_index_of(original_str, "b"), -1);
    TEST_ASSERT_EQUAL_INT(HS_index_of_case_sensitive(original_str, "w"), -1);
    TEST_ASSERT_EQUAL_INT(HS_index_of_case_sensitive(original_str, "Y"), 6);
}

void test_string_contain_substring(void) {
    defer_string(original_str) = HS_from_str("Wison Ye:)");

    TEST_ASSERT_EQUAL(HS_contains(original_str, (char *)""), false);
    TEST_ASSERT_EQUAL(HS_contains(original_str, (char *)" "), true);
    TEST_ASSERT_EQUAL(HS_contains(original_str, (char *)"w"), true);
    TEST_ASSERT_EQUAL(HS_contains(original_str, (char *)"W"), true);
    TEST_ASSERT_EQUAL(HS_contains(original_str, (char *)":)"), true);
    TEST_ASSERT_EQUAL(HS_contains(original_str, (char *)"b"), false);
    TEST_ASSERT_EQUAL(HS_contains(original_str, (char *)"fi"), false);
}

void test_string_reset_to_empty(void) {
    defer_string(temp_str) = HS_from_str("Wison Ye:)");
    HS_reset_to_empty(temp_str);

    TEST_ASSERT_EQUAL_UINT(HS_length(temp_str), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(temp_str), 0);
    TEST_ASSERT_NULL(HS_as_str(temp_str));
}

void test_string_reset_to_empty_without_freeing_buffer(void) {
    defer_string(temp_str) = HS_from_str("Wison Ye:)");
    HS_reset_to_empty_without_freeing_buffer(temp_str);

    TEST_ASSERT_EQUAL_UINT(HS_length(temp_str), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(temp_str), 0);
    TEST_ASSERT_NULL(HS_as_str(temp_str));
}

void test_string_push(void) {
    defer_string(init_empty_str) = HS_from_empty();
    defer_string(original_str)   = HS_from_str("Wison Ye:)");
    defer_string(other_str)      = HS_from_str("Other string.");

    HS_push_str(init_empty_str, HS_as_str(original_str));
    TEST_ASSERT_EQUAL_UINT(HS_length(init_empty_str), HS_length(original_str));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(init_empty_str),
                           HS_length(original_str) + 1);
    TEST_ASSERT_EQUAL_UINT(HS_length(init_empty_str),
                           strlen(HS_as_str(original_str)));

    HS_push_str(original_str, HS_as_str(original_str));
    TEST_ASSERT_EQUAL_UINT(HS_length(original_str),
                           HS_length(init_empty_str) * 2);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(original_str),
                           HS_length(original_str) + 1);

    HS_reset_to_empty(original_str);
    HS_push_other(original_str, other_str);
    HS_push_other(original_str, other_str);
    /* printf( */
    /*     "\n>>> defer_string(Push - orignal aftger push with other, len: %lu,
     * value:
     * " */
    /*     "%s", */
    /*     HS_length(original_str), HS_as_str(original_str)); */
    TEST_ASSERT_EQUAL_UINT(HS_length(original_str), HS_length(other_str) * 2);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(original_str),
                           HS_length(original_str) + 1);
}

void test_string_insert_at_begin(void) {
    defer_string(empty_str)      = HS_from_empty();
    defer_string(init_empty_str) = HS_from_empty_with_capacity(14);
    defer_string(other_str)      = HS_from_str("12345");

    TEST_ASSERT_EQUAL_UINT(HS_capacity(empty_str), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(init_empty_str), 14);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(other_str), HS_length(other_str) + 1);

    HS_push_str(init_empty_str, "6789");
    HS_insert_other_to_begin(init_empty_str, other_str);
    HS_insert_str_to_begin(init_empty_str, "0000");

    TEST_ASSERT_EQUAL_UINT(HS_length(init_empty_str), strlen("0000123456789"));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(init_empty_str),
                           HS_length(init_empty_str) + 1);
}

void test_string_move_semantic(void) {
    defer_string(s1)            = HS_from_str("123456");
    defer_string(clone_from_s1) = HS_clone_from(s1);
    TEST_ASSERT_EQUAL_UINT(HS_length(clone_from_s1), HS_length(s1));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(clone_from_s1),
                           HS_length(clone_from_s1) + 1);
    TEST_ASSERT_EQUAL_UINT(strcmp(HS_as_str(clone_from_s1), HS_as_str(s1)), 0);

    defer_string(move_from_clone_s1) = HS_move_from(clone_from_s1);
    TEST_ASSERT_EQUAL_UINT(HS_length(move_from_clone_s1), HS_length(s1));
    TEST_ASSERT_EQUAL_UINT(HS_capacity(move_from_clone_s1),
                           HS_length(move_from_clone_s1) + 1);
    TEST_ASSERT_EQUAL_STRING(HS_as_str(move_from_clone_s1), HS_as_str(s1));

    // `clone_from_s1` should be empty after MOVE to `move_from_clone_s1`
    TEST_ASSERT_EQUAL_UINT(HS_length(clone_from_s1), 0);
    TEST_ASSERT_EQUAL_UINT(HS_capacity(clone_from_s1), 0);
    TEST_ASSERT_NULL(HS_as_str(clone_from_s1));
}
