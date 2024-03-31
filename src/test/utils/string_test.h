#ifndef __TEST_STRING_H__
#define __TEST_STRING_H__

void test_string_init(void);
void test_string_init_with_capacity(void);
void test_string_empty_string(void);
void test_string_empty_string_with_capacity(void);
void test_string_from_array(void);
void test_string_from_str_with_pos_and_count(void);
void test_string_clone(void);
void test_string_find_substring(void);
void test_string_contain_substring(void);
void test_string_reset_to_empty(void);
void test_string_reset_to_empty_without_freeing_buffer(void);
void test_string_push(void);
void test_string_insert_at_begin(void);
void test_string_move_semantic(void);

#endif
