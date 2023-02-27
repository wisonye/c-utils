#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "utils/bits.h"
#include "utils/collections/single_link_list.h"
#include "utils/collections/vector.h"
#include "utils/data_types.h"
#include "utils/file.h"
#include "utils/hex_buffer.h"
#include "utils/log.h"
#include "utils/memory.h"
#include "utils/smart_ptr.h"
#include "utils/string.h"
#include "utils/timer.h"

//
//
//
LinkList create_integer_list_on_heap(void) {
    usize stack_value = 9999;
    LinkList list = LL_from_value(sizeof(usize), &stack_value, NULL);
    return list;
}

//
//
//
struct LL create_integer_list_on_stack(usize init_value) {
    struct LL list;
    LL_init_empty(&list);
    LL_append_value(&list, sizeof(usize), &init_value, NULL);
    printf("\n>>> create_integer_list_on_stack, list ptr: %p", (void *)&list);
    return list;
}

//
//
//
String create_string(const char str[]) {
    String temp_str = Str_from_arr(str);
    printf("\n>>> create_string - temp_str len: %lu, value: %s",
           Str_length(temp_str), Str_as_str(temp_str));

    SMART_STRING(temp_str_2) = Str_from_str("Hey Hey Hey!");
    return temp_str;
}

String clone_string(const String original) { return Str_clone_from(original); }

//
//
//
void test_link_list(void) {
    // Just for init the timer, so the following `Timer_get_current_time`
    // compare is more fair.
    long double no_use = Timer_get_current_time(TU_MICROSECONDS);

    int temp = 0;

    long double start_time_2 = Timer_get_current_time(TU_MICROSECONDS);

    struct LL stack_list;
    LL_init_empty(&stack_list);
    struct LL stack_int_list = create_integer_list_on_stack(8888);
    printf("\n>>> stack_int_list ptr: %p", (void *)&stack_int_list);
    struct LL stack_int_list_2 = create_integer_list_on_stack(1234);
    printf("\n>>> stack_int_list_2 ptr: %p", (void *)&stack_int_list_2);
    struct LL stack_short_int_list;
    LL_init_empty(&stack_short_int_list);

    long double end_time_2 = Timer_get_current_time(TU_MICROSECONDS);
    long double elapsed_time_2 = end_time_2 - start_time_2;
    DEBUG_LOG(Main, test_link_list,
              "Time to create 4 smart LinkList instance (stack-allocated): %Lf "
              "microseconds\n",
              elapsed_time_2);

    SMART_LINKLIST_ITERATOR(temp_iter) = LL_iter(&stack_int_list);
    for (usize iter_index = 0; iter_index < temp_iter->length; iter_index++) {
        usize temp_value = *((usize *)temp_iter->data_arr[iter_index]);
        printf("\n>>>> stack_int_list - node_value: %lu", temp_value);
    }
    SMART_LINKLIST_ITERATOR(temp_iter_2) = LL_iter(&stack_int_list_2);
    for (usize iter_index = 0; iter_index < temp_iter_2->length; iter_index++) {
        usize temp_value = *((usize *)temp_iter_2->data_arr[iter_index]);
        printf("\n>>>> stack_int_list_2 - node_value: %lu", temp_value);
    }

    LL_free(&stack_list, false, NULL);
    LL_free(&stack_short_int_list, false, NULL);
    LL_free(&stack_int_list, false, NULL);
    LL_free(&stack_int_list_2, false, NULL);

    long double start_time = Timer_get_current_time(TU_MICROSECONDS);

    SMART_LINKLIST(list) = LL_from_empty();
    /* SMART_LINKLIST(int_list) = create_integer_list_on_heap(); */
    /* SMART_LINKLIST(int_list_2) = create_integer_list_on_heap(); */
    SMART_LINKLIST(short_int_list) = LL_from_empty();

    long double end_time = Timer_get_current_time(TU_MICROSECONDS);
    long double elapsed_time = end_time - start_time;
    DEBUG_LOG(Main, test_link_list,
              "Time to create 4 smart LinkList instance (heap-allocated): %Lf "
              "microseconds\n",
              elapsed_time);

    // Append a few nodes
    usize values[] = {111, 222, 333, 444, 555};
    LL_append_value(short_int_list, sizeof(uint16), &values[0], NULL);
    LL_append_value(short_int_list, sizeof(uint16), &values[1], NULL);
    LL_append_value(short_int_list, sizeof(uint16), &values[2], NULL);
    LL_append_value(short_int_list, sizeof(uint16), &values[3], NULL);
    LL_append_value(short_int_list, sizeof(uint16), &values[4], NULL);

    // Get back the iter and check all data
    SMART_LINKLIST_ITERATOR(iter) = LL_iter(short_int_list);
    for (usize iter_index = 0; iter_index < iter->length; iter_index++) {
        usize temp_value = *((uint16_t *)iter->data_arr[iter_index]);
        printf("\n>>>> temp_value: %lu", temp_value);
    }
}

//
//
//
void test_string(void) {
    //
    // String
    //
    SMART_STRING(my_name) = Str_from_str("Wison Ye:)");

    SMART_STRING(empty_str_1) = Str_from_str(NULL);
    SMART_STRING(empty_str_2) = Str_from_str("");
    printf("\n>> empty_str_1 len: %lu, value: %s", Str_length(empty_str_1),
           Str_as_str(empty_str_1) == NULL ? "NULL" : Str_as_str(empty_str_1));
    printf("\n>> empty_str_2 len: %lu, value: '%s'", Str_length(empty_str_2),
           Str_as_str(empty_str_2) == NULL ? "NULL" : Str_as_str(empty_str_2));

    SMART_STRING(clone_from_empty_str) = Str_clone_from(empty_str_2);
    printf("\n>> clone_from_empty_str len: %lu, value: '%s'",
           Str_length(clone_from_empty_str),
           Str_as_str(clone_from_empty_str) == NULL
               ? "NULL"
               : Str_as_str(clone_from_empty_str));

    char temp_id[] = "123456789";
    char temp_id_2[] = {'A', 'B', 'C', 'D', '\0'};
    printf("\n>>> temp_id: %s", temp_id);
    printf("\n>>> temp_id_2: %s", temp_id_2);

    SMART_STRING(str_1) = Str_from_arr(temp_id);
    SMART_STRING(str_2) = Str_from_arr(temp_id_2);

    printf("\n>> str_1 len: %lu, value: %s", Str_length(str_1),
           Str_as_str(str_1));
    printf("\n>> str_2 len: %lu, value: %s", Str_length(str_2),
           Str_as_str(str_2));

    char order[] = "MyOrder-ZXCVB";
    SMART_STRING(str_3) = create_string(order);
    printf("\n>> str_3 len: %lu, value: %s", Str_length(str_3),
           Str_as_str(str_3));

    SMART_STRING(clone_from_order_str) = Str_clone_from(str_3);
    printf("\n>> clone_from_order_str len: %lu, value: %s",
           Str_length(clone_from_order_str),
           Str_as_str(clone_from_order_str) == NULL
               ? "NULL"
               : Str_as_str(clone_from_order_str));

    SMART_STRING(original_str) = Str_from_str("Wison Ye:)");
    printf("\n>>> Search '' in '%s', index: %li", Str_as_str(original_str),
           Str_index_of(original_str, ""));
    printf("\n>>> Search NULL in '%s', index: %li", Str_as_str(original_str),
           Str_index_of(original_str, NULL));
    printf("\n>>> Search ' ' in '%s', index: %li", Str_as_str(original_str),
           Str_index_of(original_str, " "));
    printf("\n>>> Search 'w' in '%s', index: %li", Str_as_str(original_str),
           Str_index_of(original_str, "w"));
    printf("\n>>> Search 'W' in '%s', index: %li", Str_as_str(original_str),
           Str_index_of(original_str, "W"));
    printf("\n>>> Search ':)' in '%s', index: %li", Str_as_str(original_str),
           Str_index_of(original_str, ":)"));
    printf("\n>>> Search 'a' in '%s', index: %li", Str_as_str(original_str),
           Str_index_of(original_str, "a"));
    printf("\n>>> Search 'w' (case-sensitive) in '%s', index: %li",
           Str_as_str(original_str),
           Str_index_of_case_sensitive(original_str, "w"));
    printf("\n>>> Search 'Y' (case-sensitive) in '%s', index: %li",
           Str_as_str(original_str),
           Str_index_of_case_sensitive(original_str, "Y"));
    printf("\n>>> Check whether contains ':)' in '%s', containers: %s",
           Str_as_str(original_str),
           Str_contains(original_str, ":)") ? "TRUE" : "FALSE");
    printf("\n>>> Check whether contains 'on' in '%s', containers: %s",
           Str_as_str(original_str),
           Str_contains(original_str, "fi") ? "TRUE" : "FALSE");

    SMART_STRING(src_str) = Str_from_str("Hey:)");
    SMART_STRING(cloned_str) = clone_string(src_str);

    printf("\n>> cloned_str len: %lu, value: %s", Str_length(cloned_str),
           Str_as_str(cloned_str));

    // String push to the end
    SMART_STRING(temp_str) = Str_from_str("Hey-->");
    SMART_STRING(empty_str_before_push) = Str_from_empty();
    Str_push_str(empty_str_before_push, "");
    Str_push_str(empty_str_before_push, NULL);
    Str_push_str(empty_str_before_push, "My name is: ");
    Str_push_str(empty_str_before_push, "Wison Ye");
    Str_push_str(empty_str_before_push, ":)");
    printf("\n>> empty_str_before_push len: %lu, value: %s",
           Str_length(empty_str_before_push),
           Str_as_str(empty_str_before_push));

    Str_push_str(empty_str_before_push, Str_as_str(temp_str));
    printf("\n>> empty_str_before_push len: %lu, value: %s",
           Str_length(empty_str_before_push),
           Str_as_str(empty_str_before_push));

    Str_reset_to_empty(empty_str_before_push);
    printf("\n>> empty_str_before_push len: %lu, value: %s",
           Str_length(empty_str_before_push),
           Str_as_str(empty_str_before_push));

    // String insert to the beginning
    SMART_STRING(empty_str_before_insert) = Str_from_empty();
    Str_insert_str_to_begin(empty_str_before_insert, "");
    Str_insert_str_to_begin(empty_str_before_insert, NULL);
    Str_insert_str_to_begin(empty_str_before_insert, "My name is: ");
    Str_insert_str_to_begin(empty_str_before_insert, "Wison Ye");
    Str_insert_str_to_begin(empty_str_before_insert, ":)");
    printf("\n>> empty_str_before_insert len: %lu, value: %s",
           Str_length(empty_str_before_insert),
           Str_as_str(empty_str_before_insert));

    Str_reset_to_empty(empty_str_before_insert);
    printf("\n>> empty_str_before_insert len: %lu, value: %s",
           Str_length(empty_str_before_insert),
           Str_as_str(empty_str_before_insert));

    SMART_STRING(other_str) = Str_from_str("I'm other str.");
    Str_insert_str_to_begin(empty_str_before_insert, "Hey:)");
    Str_insert_other_to_begin(empty_str_before_insert, other_str);
    printf("\n>> empty_str_before_insert len: %lu, value: %s",
           Str_length(empty_str_before_insert),
           Str_as_str(empty_str_before_insert));

    SMART_STRING(s1) = Str_from_str("123456");
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(String, s1, Str_struct_size());

    SMART_STRING(clone_from_s1) = Str_clone_from(s1);
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(String, clone_from_s1, Str_struct_size());

    SMART_STRING(move_from_clone_s1) = Str_move_from(clone_from_s1);

    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(String, clone_from_s1, Str_struct_size());
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(String, move_from_clone_s1,
                                      Str_struct_size());

    printf("\n>>> clone_from_1 - len: %lu, value: %s",
           Str_length(clone_from_s1), Str_as_str(clone_from_s1));
    printf("\n>>> move_from_clone_s1 - len: %lu, value: %s",
           Str_length(move_from_clone_s1), Str_as_str(move_from_clone_s1));
}

//
//
//
typedef struct Point {
    float x;
    float y;
} Point;

void test_log_macro(void) {
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

void unimplemented_function(void) {
    assert(false && "This function doesn't implement yet.");
}

//
//
//
void test_hex_buffer(void) {
    char hex_str_1[] = "AABBCCDD";
    HexBuffer buffer_1 = Hex_from_string(hex_str_1);
    HexBufferIteractor hex_iter = Hex_iter(buffer_1);
    for (usize index = 0; index < hex_iter.length; index++) {
        printf("\n>>> hex_iter[%lu]: 0x%02X", index, hex_iter.arr[index]);
    }

    // `+1` is for the `null-terminated` character
    usize out_buffer_size = Hex_length(buffer_1) * 2 + 1;

    // Create return `char *` buffer and init to all `0`
    char hex_string[out_buffer_size];
    memset(hex_string, 0, out_buffer_size);
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(char[], hex_string, out_buffer_size);
    usize return_hex_len = Hex_to_string(buffer_1, hex_string, out_buffer_size);
    DEBUG_LOG(Main, test_hex_buffer, "return_hex_len: %lu", return_hex_len);
    if (return_hex_len > 0) {
        DEBUG_LOG(Main, test_hex_buffer, "hex_string len: %lu, value: %s",
                  strlen(hex_string), hex_string);
    }
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(char[], hex_string, out_buffer_size);

    HexBuffer buffer_2 = Hex_from_string(
        " A $%@@!!@!@!`"
        ""
        ""
        "`&*())@$%%   B C D ");
    char hex_string_2[Hex_length(buffer_2) * 2];
    usize return_hex_len_2 =
        Hex_to_string(buffer_2, hex_string_2, Hex_length(buffer_2) * 2);
    DEBUG_LOG(Main, test_hex_buffer, "return_hex_len_2: %lu", return_hex_len_2);
    if (return_hex_len_2 > 0) {
        DEBUG_LOG(Main, test_hex_buffer, "hex_string_2: %s", hex_string_2);
    }

    Hex_free(buffer_1);
    Hex_free(buffer_2);
}

//
//
//
typedef struct {
    char first_name[10];
    char last_name[10];
    u8 age;
} Person;

String get_person_desc(Person *self) {
    usize buffer_size = sizeof(Person) + 34 + 1;
    char buffer[sizeof(Person) + 34 + 1] = {0};
    snprintf(buffer, buffer_size, "(first_name: %s, last_name: %s, age: %u)",
             self->first_name, self->last_name, self->age);
    String desc = Str_from_str(buffer);
    return desc;
}

void test_vector(void) {
    //
    // Bool vec
    //
    SMART_VECTOR_WITH_CAPACITY(bool_vec, bool, 5, NULL);
    bool true_value = true;
    bool false_value = false;
    Vec_push(bool_vec, &true_value);
    Vec_push(bool_vec, &true_value);
    Vec_push(bool_vec, &false_value);
    Vec_push(bool_vec, &false_value);
    Vec_push(bool_vec, &true_value);
    String bool_vec_desc = Vec_join(bool_vec, " , ", NULL);
    printf("\n>>> bool_vec_desc: %s\n", Str_as_str(bool_vec_desc));
    Str_free(bool_vec_desc);

    //
    // Empty vec
    //
    SMART_VECTOR(empty_vec, usize, NULL);

    //
    // u16 vec
    //
    SMART_VECTOR_WITH_CAPACITY(u16_vec, u16, 10, NULL);
    //
    // `capacity` should NOT change and no `realloc` will be called before
    // pushing the 11th elements
    //
    u16 short_arr[] = {5000, 5001, 5002, 5003, 5004, 5005,
                       5006, 5007, 5008, 5009, 6000};
    Vec_push(u16_vec, &short_arr[0]);
    Vec_push(u16_vec, &short_arr[1]);
    Vec_push(u16_vec, &short_arr[2]);
    Vec_push(u16_vec, &short_arr[3]);
    Vec_push(u16_vec, &short_arr[4]);
    Vec_push(u16_vec, &short_arr[5]);
    Vec_push(u16_vec, &short_arr[6]);
    Vec_push(u16_vec, &short_arr[7]);
    Vec_push(u16_vec, &short_arr[8]);
    Vec_push(u16_vec, &short_arr[9]);
    // `capacity` should change to `20`
    Vec_push(u16_vec, &short_arr[10]);
    // Element value check
    VectorIteractor short_arr_iter = Vec_iter(u16_vec);
    u16 *temp_short_arr = (u16 *)short_arr_iter.items;
    for (usize sa_index = 0; sa_index < short_arr_iter.length; sa_index++) {
        DEBUG_LOG(Main, test_vector, "short_arr_iter[%lu]: %d", sa_index,
                  temp_short_arr[sa_index]);
    }
    String u16_vec_desc = Vec_join(u16_vec, " , ", NULL);
    printf("\n>>> u16_vec_desc: %s\n", Str_as_str(u16_vec_desc));
    Str_free(u16_vec_desc);

    //
    // int vec
    //
    int int_arr[] = {100, 200, 300};
    SMART_VECTOR(int_vec, int, NULL);
    Vec_push(int_vec, &int_arr[0]);
    Vec_push(int_vec, &int_arr[1]);
    Vec_push(int_vec, &int_arr[2]);

    VectorIteractor int_arr_iter = Vec_iter(int_vec);
    int *temp_int_arr = (int *)int_arr_iter.items;
    for (usize index = 0; index < int_arr_iter.length; index++) {
        DEBUG_LOG(Main, test_vector, "int_arr_iter[%lu]: %d", index,
                  temp_int_arr[index]);
    }
    String int_vec_desc = Vec_join(int_vec, " , ", NULL);
    printf("\n>>> int_vec_desc: %s\n", Str_as_str(int_vec_desc));
    Str_free(int_vec_desc);

    //
    // String vec
    //
    SMART_STRING(temp_str_1) = Str_from_str("Vector works:)");
    SMART_STRING(temp_str_2) = Str_from_str("Generic vector works:)");
    SMART_STRING(temp_str_3) =
        Str_from_str("My Generic vector works, yeah!!!:)>>>>:(");

    SMART_VECTOR_WITH_CAPACITY(string_vec, struct Str, 3, NULL);
    Vec_push(string_vec, temp_str_1);
    Vec_push(string_vec, temp_str_2);
    Vec_push(string_vec, temp_str_3);

    String string_vec_desc = Vec_join(string_vec, " , ", NULL);
    printf("\n>>> string_vec: %s\n", Str_as_str(string_vec_desc));
    Str_free(string_vec_desc);

    //
    // Person list
    //
    Person wison = {.first_name = "Mr C", .last_name = "cool", .age = 88};
    Person fion = {.first_name = "Mr CPP", .last_name = "not bad", .age = 99};
    Person nobody = {
        .first_name = "Nobody", .last_name = "Nothing", .age = 100};
    SMART_VECTOR_WITH_CAPACITY(person_list, Person, 3, NULL);
    Vec_push(person_list, &wison);
    Vec_push(person_list, &fion);
    Vec_push(person_list, &nobody);

    VectorIteractor person_list_iter = Vec_iter(person_list);
    Person *temp_person_arr = (Person *)person_list_iter.items;
    for (usize index = 0; index < person_list_iter.length; index++) {
        DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].first_name: %s",
                  index, temp_person_arr[index].first_name);
        DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].last_name: %s",
                  index, temp_person_arr[index].last_name);
        DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].age: %u", index,
                  temp_person_arr[index].age);
    }
    String person_vec_desc = Vec_join(
        person_list, " , ", (struct Str * (*)(void *)) get_person_desc);
    printf("\n>>> person_vec: %s\n", Str_as_str(person_vec_desc));
    Str_free(person_vec_desc);

    // Double list
    double double_arr[] = {11.11, 22.22, 33.33};
    usize double_type_size = sizeof(double);
    usize double_arr_len = sizeof(double_arr) / sizeof(double_arr[0]);

    SMART_VECTOR_WITH_CAPACITY(double_vec, double, double_arr_len, NULL);
    for (usize di = 0; di < double_arr_len; di++) {
        Vec_push(double_vec, &double_arr[di]);
    }

    const double *d_value_1 = (const double *)Vec_get(double_vec, 0);
    const double *d_value_2 = (const double *)Vec_get(double_vec, 1);
    const double *d_value_3 = (const double *)Vec_get(double_vec, 2);

    DEBUG_LOG(Main, test_vector, "d_value_1: %f", *d_value_1);
    DEBUG_LOG(Main, test_vector, "d_value_2: %f", *d_value_2);
    DEBUG_LOG(Main, test_vector, "d_value_3: %f", *d_value_3);
}

void test_vector_element_destructor(void) {
    SMART_VECTOR_WITH_CAPACITY(vec, String, 2, NULL);

    String str1 = Str_from_str("String in vector");
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Str, str1, Str_struct_size());
    String str2 = Str_from_str("Second string in vector");
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Str, str2, Str_struct_size());

    Vec_push(vec, str1);
    Vec_push(vec, str2);
    printf("\n>>> Str_struct_size(): %lu", Str_struct_size());

    /* const String ele1 = (const String)Vec_get(vec, 0, Str_struct_size()); */
    /* const String ele2 = (const String)Vec_get(vec, 1, Str_struct_size()); */
    /* printf("\n>>> ele1 ptr: %p, value: %s", ele1, Str_as_str(ele1)); */
    /* printf("\n>>> ele2 ptr: %p, value: %s", ele2, Str_as_str(ele2)); */

    /* const VectorIteractor vec_it = Vec_iter(vec); */
    /* void *it_string_item = vec_it.items; */
    /* for (usize i = 0; i < vec_it.length; i++) { */
    /*     String temp_str = (String)(it_string_item + i * Str_struct_size());
     */
    /*     DEBUG_LOG(Main, test_vector_element_destructor, */
    /*               "vec element ptr: %p, string value: %s", temp_str, */
    /*               Str_as_str(temp_str)); */
    /* } */

    DEBUG_LOG(Main, test_vector_element_destructor,
              "Before smart vector out of scope", "");
}

//
//
//
void test_timer(void) {
    long double start_time = Timer_get_current_time(TU_NANOSECONDS);
    long double end_time = Timer_get_current_time(TU_NANOSECONDS);
    long double elapsed_time = end_time - start_time;

    DEBUG_LOG(Main, test_timer, "elapsed_time: %Lf\n", elapsed_time);
}

struct Person {
    /* char first_name[10]; */
    /* char last_name[5]; */
    char birthday[9];
    u8 age;
};

//
//
//
void test_memory(void) {
    int data = 10;

    struct Person me = {
        .birthday = "19880531",
        .age = 0xAA,
    };
    PRINT_MEMORY_BLOCK(int, data);
    PRINT_MEMORY_BLOCK(struct Person, me)

    SMART_STRING(str1) = Str_from_str("String in vector");
    PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Str, str1, Str_struct_size());
    printf("\n>>>\n");
}

String return_string_on_the_heap(void) {
    String str_on_the_heap = Str_from_str("String allocated on the heap:)");
    return str_on_the_heap;
}

Vector return_vector_on_the_heap(void) {
    usize double_size = sizeof(double);
    Vector temp_vec =
        Vec_with_capacity(double_size, TYPE_NAME_TO_STRING(double), 5, NULL);
    double d = 888.88;
    Vec_push(temp_vec, &d);
    return temp_vec;
}

void test_smart_ptr(void) {
    //
    // `return_str` will be destroyed by calling `auto_free_string` automatic
    //
    MAKE_UNIQUE_PTR(String return_str = return_string_on_the_heap(),
                    auto_free_string);

    //
    // `return_vector` will be destroyed by calling `auto_free_vector` automatic
    //
    MAKE_UNIQUE_PTR(Vector return_vec = return_vector_on_the_heap(),
                    auto_free_vector);

    DEBUG_LOG(Main, test_smart_ptr, "return_str: %p, value: %s", return_str,
              Str_as_str(return_str));
    DEBUG_LOG(Main, test_smart_ptr,
              "return_vec: %p, len: %lu, first elemnt: %f", return_vec,
              Vec_len(return_vec), *((double *)Vec_get(return_vec, 0)));
}

//
//
//
void test_bits(void) {
    unsigned char status = 0x3D;
    PRINT_BITS(status);

    unsigned short int status_16 = 0x376D;
    PRINT_BITS(status_16);

    int status_32 = 0x376DAA0B;
    PRINT_BITS(status_32);

    long long status_64 = 0x376DAA0B5F8E9ABC;
    PRINT_BITS(status_64);

    u8 v = 0x02;
    u8 which_bit = 2;
    printf("\n>>> bit %d in '0x%02X' is 1?: result: 0x%02X, %s\n", which_bit, v,
           v >> (which_bit - 1), v >> (which_bit - 1) & 0x01 ? "Yes" : "No");

    v = 0x08;
    which_bit = 4;
    printf("\n>>> bit %d in '0x%02X' is 1?: result: 0x%02X, %s\n", which_bit, v,
           v >> (which_bit - 1), v >> (which_bit - 1) & 0x01 ? "Yes" : "No");

    v = 0xCD;
    PRINT_BITS(v);
    which_bit = 1;
    printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
           v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
    which_bit = 2;
    printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
           v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
    which_bit = 3;
    printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
           v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
    which_bit = 4;
    printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
           v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
    which_bit = 5;
    printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
           v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
    which_bit = 6;
    printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
           v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
    which_bit = 7;
    printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
           v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
    which_bit = 8;
    printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
           v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
}

//
//
//
void test_file(void) {
    char *filename = NULL;
#if defined(__APPLE__)
    // filename = "/Users/wison/temp/temp.html";
    filename = "/Users/wison/my-shell/backup/README_openbsd.md";

#elif defined(__FreeBSD__)
    // filename = "/home/wison/my-shell/backup/README_openbsd.md";
    filename = "/home/wison/temp/test.js";
    // filename = "/home/wison/temp/test.logaaa";
#endif

    SMART_FILE(my_file) = File_open(filename, FM_READ_ONLY);
    if (File_is_open_successfully(my_file)) {
        usize read_bytes = File_load_into_buffer(my_file);
        const char *file_content = File_get_data(my_file);
        usize file_size = File_get_size(my_file);
        LOG_VAR(read_bytes);
        LOG_VAR(file_size);
        LOG_VAR(file_content);

    } else {
        fprintf(stderr, "Failed to open file '%s': %s\n", filename,
                File_get_error(my_file));
    }

#ifdef ENABLE_DEBUG_LOG
    File_print_debug_info(my_file);
#endif
}

//
//
//
int main(int argc, char **argv) {
    test_file();

    /* test_link_list(); */
    /* test_string(); */
    /* test_log_macro(); */
    /* test_vector(); */
    /* test_vector_element_destructor(); */
    /* LOG_VAR(sizeof(int)); */
    /* LOG_VAR(sizeof(long)); */
    /* LOG_VAR(sizeof(long int)); */
    /* LOG_VAR(sizeof(long long int)); */
    /* LOG_VAR(sizeof(unsigned long)); */
    /* LOG_VAR(sizeof(unsigned long int)); */
    /* LOG_VAR(sizeof(unsigned long long int)); */
    /* LOG_VAR(sizeof(size_t)); */

    // unimplemented_function();

    SMART_STRING(my_str) = Str_from_str("My name is Wison Ye");
    DEBUG_LOG(Main, main, "add(2, 3): %d", add(2, 3));
    DEBUG_LOG(Main, main, "2 + 2 :%d", 2 + 2);
    DEBUG_LOG(Main, main, "my_str value is: %s", Str_as_str(my_str));
    INFO_LOG(Main, main, "my_str value is: %s", Str_as_str(my_str));
    WARN_LOG(Main, main, "my_str value is: %s", Str_as_str(my_str));
    ERROR_LOG(Main, main, "my_str value is: %s", Str_as_str(my_str));

    // String my_name_str = Str_from_str("Wison Ye");
    // String clone_from_empty_str = Str_clone(&my_name_str);
    // DEBUG_LOG(Main, StringTest, "clone_from_empty_str len: %lu, value: %s",
    //           Str_length(&clone_from_empty_str),
    //           Str_as_str(&clone_from_empty_str) == NULL
    //               ? "NULL"
    //               : Str_as_str(&clone_from_empty_str));
    // Str_free(&my_name_str);
    // Str_free(&clone_from_empty_str);

    /* test_hex_buffer(); */
    /* test_memory(); */
    /* test_timer(); */
    /* test_smart_ptr(); */
    /* test_bits(); */

    return 0;
}
