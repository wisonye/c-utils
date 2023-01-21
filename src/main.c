#include "stdio.h"
#include "utils/collections/single_link_list.h"
#include "utils/data_types.h"
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

//
//
//
int main(int argc, char **argv) {
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
    Str_free(&original_str);
}
