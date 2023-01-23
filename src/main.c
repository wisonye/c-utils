#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include "utils/collections/single_link_list.h"
#include "utils/data_types.h"
#include "utils/log.h"
#include "utils/string.h"

//
//
//
LL create_integer_list() {
    usize stack_value = 9999;
    LL list = LL_from_value(sizeof(usize), &stack_value, NULL);
    return list;
}

//
//
//
Str create_string(const char str[]) {
    Str temp_str = Str_from_arr(str);
    printf("\n>>> create_string - temp_str len: %lu, value: %s",
           Str_length(&temp_str), Str_as_str(&temp_str));

    Str temp_str_2 = Str_from_str("Hey Hey Hey!");
    Str_free(&temp_str_2);
    return temp_str;
}

Str clone_string(const Str *original) { return Str_clone(original); }

//
//
//
void test_link_list() {
    LinkList list = LL_from_empty();
    LinkList int_list = create_integer_list();
    LL int_list_2 = create_integer_list();
    LL_free(&list, NULL);
    LL_free(&int_list, NULL);
    LL_free(&int_list_2, NULL);

    LL short_int_list = LL_from_empty();

    // Append a few nodes
    usize values[] = {111, 222, 333, 444, 555};
    LL_append_value(&short_int_list, sizeof(uint16), &values[0], NULL);
    LL_append_value(&short_int_list, sizeof(uint16), &values[1], NULL);
    LL_append_value(&short_int_list, sizeof(uint16), &values[2], NULL);
    LL_append_value(&short_int_list, sizeof(uint16), &values[3], NULL);
    LL_append_value(&short_int_list, sizeof(uint16), &values[4], NULL);

    // Get back the iter and check all data
    LLIterator *iter = LL_iter(&short_int_list);
    for (usize iter_index = 0; iter_index < iter->length; iter_index++) {
        usize temp_value = *((uint16_t *)iter->data_arr[iter_index]);
        printf("\n>>>> temp_value: %lu", temp_value);
    }
    LL_free_iter(iter);

    //
    LL_free(&short_int_list, NULL);
}

//
//
//
void test_string() {
    //
    // String
    //
    Str my_name = Str_from_str("Wison Ye:)");
    Str_free(&my_name);

    Str empty_str_1 = Str_from_str(NULL);
    Str empty_str_2 = Str_from_str("");
    printf(
        "\n>> empty_str_1 len: %lu, value: %s", Str_length(&empty_str_1),
        Str_as_str(&empty_str_1) == NULL ? "NULL" : Str_as_str(&empty_str_1));
    printf(
        "\n>> empty_str_2 len: %lu, value: '%s'", Str_length(&empty_str_2),
        Str_as_str(&empty_str_2) == NULL ? "NULL" : Str_as_str(&empty_str_2));

    Str clone_from_empty_str = Str_clone(&empty_str_2);
    printf("\n>> clone_from_empty_str len: %lu, value: '%s'",
           Str_length(&clone_from_empty_str),
           Str_as_str(&clone_from_empty_str) == NULL
               ? "NULL"
               : Str_as_str(&clone_from_empty_str));

    Str_free(&empty_str_1);
    Str_free(&empty_str_2);
    Str_free(&clone_from_empty_str);

    char temp_id[] = "123456789";
    char temp_id_2[] = {'A', 'B', 'C', 'D', '\0'};
    printf("\n>>> temp_id: %s", temp_id);
    printf("\n>>> temp_id_2: %s", temp_id_2);

    Str str_1 = Str_from_arr(temp_id);
    Str str_2 = Str_from_arr(temp_id_2);

    printf("\n>> str_1 len: %lu, value: %s", Str_length(&str_1),
           Str_as_str(&str_1));
    printf("\n>> str_2 len: %lu, value: %s", Str_length(&str_2),
           Str_as_str(&str_2));

    Str_free(&str_1);
    Str_free(&str_2);

    char order[] = "MyOrder-ZXCVB";
    Str str_3 = create_string(order);
    printf("\n>> str_3 len: %lu, value: %s", Str_length(&str_3),
           Str_as_str(&str_3));

    Str clone_from_order_str = Str_clone(&str_3);
    printf("\n>> clone_from_order_str len: %lu, value: %s",
           Str_length(&clone_from_order_str),
           Str_as_str(&clone_from_order_str) == NULL
               ? "NULL"
               : Str_as_str(&clone_from_order_str));
    Str_free(&str_3);
    Str_free(&clone_from_order_str);

    Str original_str = Str_from_str("Wison Ye:)");
    printf("\n>>> Search '' in '%s', index: %li", Str_as_str(&original_str),
           Str_index_of(&original_str, ""));
    printf("\n>>> Search NULL in '%s', index: %li", Str_as_str(&original_str),
           Str_index_of(&original_str, NULL));
    printf("\n>>> Search ' ' in '%s', index: %li", Str_as_str(&original_str),
           Str_index_of(&original_str, " "));
    printf("\n>>> Search 'w' in '%s', index: %li", Str_as_str(&original_str),
           Str_index_of(&original_str, "w"));
    printf("\n>>> Search 'W' in '%s', index: %li", Str_as_str(&original_str),
           Str_index_of(&original_str, "W"));
    printf("\n>>> Search ':)' in '%s', index: %li", Str_as_str(&original_str),
           Str_index_of(&original_str, ":)"));
    printf("\n>>> Search 'a' in '%s', index: %li", Str_as_str(&original_str),
           Str_index_of(&original_str, "a"));
    printf("\n>>> Search 'w' (case-sensitive) in '%s', index: %li",
           Str_as_str(&original_str),
           Str_index_of_case_sensitive(&original_str, "w"));
    printf("\n>>> Search 'Y' (case-sensitive) in '%s', index: %li",
           Str_as_str(&original_str),
           Str_index_of_case_sensitive(&original_str, "Y"));
    printf("\n>>> Check whether contains ':)' in '%s', containers: %s",
           Str_as_str(&original_str),
           Str_contains(&original_str, ":)") ? "TRUE" : "FALSE");
    printf("\n>>> Check whether contains 'on' in '%s', containers: %s",
           Str_as_str(&original_str),
           Str_contains(&original_str, "fi") ? "TRUE" : "FALSE");
    Str_free(&original_str);

    Str src_str = Str_from_str("Hey:)");
    Str cloned_str = clone_string(&src_str);
    Str_free(&src_str);

    printf("\n>> cloned_str len: %lu, value: %s", Str_length(&cloned_str),
           Str_as_str(&cloned_str));
    Str_free(&cloned_str);
    printf("\n>> cloned_str len: %lu, value: %s", Str_length(&cloned_str),
           Str_as_str(&cloned_str));

    // String push to the end
    Str temp_str = Str_from_str("Hey-->");
    Str empty_str_before_push = Str_from_empty();
    Str_push_str(&empty_str_before_push, "");
    Str_push_str(&empty_str_before_push, NULL);
    Str_push_str(&empty_str_before_push, "My name is: ");
    Str_push_str(&empty_str_before_push, "Wison Ye");
    Str_push_str(&empty_str_before_push, ":)");
    printf("\n>> empty_str_before_push len: %lu, value: %s",
           Str_length(&empty_str_before_push),
           Str_as_str(&empty_str_before_push));

    Str_push_str(&empty_str_before_push, Str_as_str(&temp_str));
    printf("\n>> empty_str_before_push len: %lu, value: %s",
           Str_length(&empty_str_before_push),
           Str_as_str(&empty_str_before_push));

    Str_reset_to_empty(&empty_str_before_push);
    printf("\n>> empty_str_before_push len: %lu, value: %s",
           Str_length(&empty_str_before_push),
           Str_as_str(&empty_str_before_push));

    Str_free(&temp_str);
    Str_free(&empty_str_before_push);

    // String insert to the beginning
    Str empty_str_before_insert = Str_from_empty();
    Str_insert_str_to_begin(&empty_str_before_insert, "");
    Str_insert_str_to_begin(&empty_str_before_insert, NULL);
    Str_insert_str_to_begin(&empty_str_before_insert, "My name is: ");
    Str_insert_str_to_begin(&empty_str_before_insert, "Wison Ye");
    Str_insert_str_to_begin(&empty_str_before_insert, ":)");
    printf("\n>> empty_str_before_insert len: %lu, value: %s",
           Str_length(&empty_str_before_insert),
           Str_as_str(&empty_str_before_insert));

    Str_reset_to_empty(&empty_str_before_insert);
    printf("\n>> empty_str_before_insert len: %lu, value: %s",
           Str_length(&empty_str_before_insert),
           Str_as_str(&empty_str_before_insert));

    Str other_str = Str_from_str("I'm other str.");
    Str_insert_str_to_begin(&empty_str_before_insert, "Hey:)");
    Str_insert_other_to_begin(&empty_str_before_insert, &other_str);
    printf("\n>> empty_str_before_insert len: %lu, value: %s",
           Str_length(&empty_str_before_insert),
           Str_as_str(&empty_str_before_insert));

    Str_free(&other_str);
    Str_free(&empty_str_before_insert);
}

//
//
//
typedef struct Point {
    float x;
    float y;
} Point;

void test_log_macro() {
    char *string_value = "Wison Ye";
    char char_value = 'c';
    u8 u8_value = 255;
    u16 u16_value = 65535;
    u32 u32_value = 99999;
    u64 u64_value = 99999;
    usize usize_value = 99999;
    i8 i8_value = 127;
    i16 i16_value = 65535 / 2;
    i32 i32_value = -99999;
    i64 i64_value = -2299999;
    int int_value = 999999;
    long long_value = 999999;
    long long long_long_value = 999999;
    float float_value = 123.123;
    double double_value = 99999.123;
    long double long_double_value = 99999.123;
    bool bool_value = true;

    printf("\n>>> char_value type: %s", TYPE_NAME(char_value));
    printf("\n>>> u8_value type: %s", TYPE_NAME(u8_value));
    printf("\n>>> u16_value type: %s", TYPE_NAME(u16_value));
    printf("\n>>> u32_value type: %s", TYPE_NAME(u32_value));
    printf("\n>>> u64_value type: %s", TYPE_NAME(u64_value));
    printf("\n>>> usize_value type: %s", TYPE_NAME(usize_value));
    printf("\n>>> i8_value type: %s", TYPE_NAME(i8_value));
    printf("\n>>> i16_value type: %s", TYPE_NAME(i16_value));
    printf("\n>>> i32_value type: %s", TYPE_NAME(i32_value));
    printf("\n>>> i64_value type: %s", TYPE_NAME(i64_value));
    printf("\n>>> int_value type: %s", TYPE_NAME(int_value));
    printf("\n>>> long_value type: %s", TYPE_NAME(long_value));
    printf("\n>>> long_long_value type: %s", TYPE_NAME(long_long_value));
    printf("\n>>> float_value type: %s", TYPE_NAME(float_value));
    printf("\n>>> double_value type: %s", TYPE_NAME(double_value));
    printf("\n>>> long_double_value type: %s", TYPE_NAME(long_double_value));
    printf("\n>>> bool_value type: %s", TYPE_NAME(bool_value));

    LOG_VAR(char_value);
    LOG_VAR(u8_value);
    LOG_VAR(u16_value);
    LOG_VAR(u32_value);
    LOG_VAR(u64_value);
    LOG_VAR(usize_value);
    LOG_VAR(i8_value);
    LOG_VAR(i16_value);
    LOG_VAR(i32_value);
    LOG_VAR(i64_value);
    LOG_VAR(int_value);
    LOG_VAR(long_value);
    LOG_VAR(long_long_value);
    LOG_VAR(float_value);
    LOG_VAR(double_value);
    LOG_VAR(long_double_value);
    LOG_VAR(bool_value);
    LOG_VAR(string_value);

    void *void_ptr = &string_value;
    bool *bool_ptr = &bool_value;
    u8 *u8_ptr = &u8_value;
    u16 *u16_ptr = &u16_value;
    u32 *u32_ptr = &u32_value;
    u64 *u64_ptr = &u64_value;
    usize *usize_ptr = &usize_value;
    i8 *i8_ptr = &i8_value;
    i16 *i16_ptr = &i16_value;
    i32 *i32_ptr = &i32_value;
    i64 *i64_ptr = &i64_value;
    float *float_ptr = &float_value;
    double *double_ptr = &double_value;
    long double *long_double_ptr = &long_double_value;

    printf("\n>>> void_ptr type: %s", TYPE_NAME(void_ptr));
    printf("\n>>> bool_ptr type: %s", TYPE_NAME(bool_ptr));
    printf("\n>>> u8_ptr type: %s", TYPE_NAME(u8_ptr));
    printf("\n>>> u16_ptr type: %s", TYPE_NAME(u16_ptr));
    printf("\n>>> u32_ptr type: %s", TYPE_NAME(u32_ptr));
    printf("\n>>> u64_ptr type: %s", TYPE_NAME(u64_ptr));
    printf("\n>>> usize_ptr type: %s", TYPE_NAME(usize_ptr));
    printf("\n>>> i8_ptr type: %s", TYPE_NAME(i8_ptr));
    printf("\n>>> i16_ptr type: %s", TYPE_NAME(i16_ptr));
    printf("\n>>> i32_ptr type: %s", TYPE_NAME(i32_ptr));
    printf("\n>>> i64_ptr type: %s", TYPE_NAME(i64_ptr));
    printf("\n>>> float_ptr type: %s", TYPE_NAME(float_ptr));
    printf("\n>>> double_ptr type: %s", TYPE_NAME(double_ptr));
    printf("\n>>> long_double_ptr type: %s", TYPE_NAME(long_double_ptr));
    LOG_VAR(void_ptr);
    LOG_VAR(bool_ptr);
    LOG_VAR(u8_ptr);
    LOG_VAR(u16_ptr);
    LOG_VAR(u32_ptr);
    LOG_VAR(u64_ptr);
    LOG_VAR(usize_ptr);
    LOG_VAR(i8_ptr);
    LOG_VAR(i16_ptr);
    LOG_VAR(i32_ptr);
    LOG_VAR(i64_ptr);
    LOG_VAR(float_ptr);
    LOG_VAR(double_ptr);
    LOG_VAR(long_double_ptr);

    char my_string[] = "My String:)";
    u8 my_u8_arr[] = {0x01, 0x02, 0x03};
    printf("\n>>> my_string type: %s", TYPE_NAME(my_string));
    printf("\n>>> my_u8_arr type: %s", TYPE_NAME(my_u8_arr));

    LOG_VAR(my_string);
    LOG_VAR(my_u8_arr);

    Point point = {.x = 1.1, .y = 2.2};
    printf("\n>>> point type: %s", TYPE_NAME(point));
    // LOG_VAR(point);
}

int add(int v1, int v2) { return v1 + v2; }

void unimplemented_function() {
    assert(false && "This function doesn't implement yet.");
}

//
//
//
int main(int argc, char **argv) {
    /* test_link_list(); */
    /* test_string(); */
    test_log_macro();
    LOG_VAR(sizeof(int));
    LOG_VAR(sizeof(long));
    LOG_VAR(sizeof(long int));
    LOG_VAR(sizeof(long long int));
    LOG_VAR(sizeof(unsigned long));
    LOG_VAR(sizeof(unsigned long int));
    LOG_VAR(sizeof(unsigned long long int));
    LOG_VAR(sizeof(size_t));

    // unimplemented_function();

    Str my_str = Str_from_str("My name is Wison Ye");
    DEBUG_LOG(Main, main, "add(2, 3): %d", add(2, 3));
    DEBUG_LOG(Main, main, "2 + 2 :%d", 2 + 2);
    DEBUG_LOG(Main, main, "my_str value is: %s", Str_as_str(&my_str));
    INFO_LOG(Main, main, "my_str value is: %s", Str_as_str(&my_str));
    WARN_LOG(Main, main, "my_str value is: %s", Str_as_str(&my_str));
    ERROR_LOG(Main, main, "my_str value is: %s", Str_as_str(&my_str));
    Str_free(&my_str);

    Str my_name_str = Str_from_str("Wison Ye");
    Str clone_from_empty_str = Str_clone(&my_name_str);
    DEBUG_LOG(Main, StringTest, "clone_from_empty_str len: %lu, value: %s",
              Str_length(&clone_from_empty_str),
              Str_as_str(&clone_from_empty_str) == NULL
                  ? "NULL"
                  : Str_as_str(&clone_from_empty_str));
    Str_free(&my_name_str);
    Str_free(&clone_from_empty_str);
}
