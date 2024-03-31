#include <string.h>
#include <unity.h>

#include "./test/utils/data_types_test.h"
#include "./test/utils/file_test.h"
#include "./test/utils/hex_buffer_test.h"
#include "./test/utils/string_test.h"

///
/// This is run before EACH TEST
///
void setUp(void) {}

///
/// This is run after EACH TEST
///
void tearDown(void) {}

//
//
//
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_hex_buffer_empty_hex_buffer);
    RUN_TEST(test_hex_buffer_invalid_buffer);
    RUN_TEST(test_hex_buffer_valid_buffer);

    RUN_TEST(test_data_types_type_name);
    RUN_TEST(test_data_types_is_the_same_type);
    RUN_TEST(test_data_types_type_name_to_string);
    RUN_TEST(test_data_types_type_size);
    RUN_TEST(test_data_types_type_size_from_type);

    RUN_TEST(test_file_open_should_fail);
    RUN_TEST(test_file_open_should_success);
    RUN_TEST(test_file_read_should_success);

    RUN_TEST(test_string_init);
    RUN_TEST(test_string_init_with_capacity);
    RUN_TEST(test_string_empty_string);
    RUN_TEST(test_string_empty_string_with_capacity);
    RUN_TEST(test_string_from_array);
    RUN_TEST(test_string_from_str_with_pos_and_count);
    RUN_TEST(test_string_clone);
    RUN_TEST(test_string_find_substring);
    RUN_TEST(test_string_contain_substring);
    RUN_TEST(test_string_reset_to_empty);
    RUN_TEST(test_string_reset_to_empty_without_freeing_buffer);
    RUN_TEST(test_string_push);
    RUN_TEST(test_string_insert_at_begin);
    RUN_TEST(test_string_move_semantic);

    UNITY_END();
    return 0;
}
