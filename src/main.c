#include "stdio.h"
#include "utils/collections/single_link_list.h"

//
//
//
LL create_integer_list() {
    size_t stack_value = 9999;
    LL list = LL_from_value(sizeof(size_t), &stack_value, NULL);
    return list;
}

//
//
//
int main(int argc, char **argv) {
    LL list = LL_from_empty();
    LL int_list = create_integer_list();
    LL int_list_2 = create_integer_list();
    LL_free(&list, NULL);
    LL_free(&int_list, NULL);
    LL_free(&int_list_2, NULL);

    LL short_int_list = LL_from_empty();

    // Append a few nodes
    size_t values[] = {111, 222, 333, 444, 555};
    LL_append_value(&short_int_list, sizeof(uint16_t), &values[0], NULL);
    LL_append_value(&short_int_list, sizeof(uint16_t), &values[1], NULL);
    LL_append_value(&short_int_list, sizeof(uint16_t), &values[2], NULL);
    LL_append_value(&short_int_list, sizeof(uint16_t), &values[3], NULL);
    LL_append_value(&short_int_list, sizeof(uint16_t), &values[4], NULL);

    // Get back the iter and check all data
    LLIterator *iter = LL_iter(&short_int_list);
    for (size_t iter_index = 0; iter_index < iter->length; iter_index++) {
        size_t temp_value = *((uint16_t *)iter->data_arr[iter_index]);
        printf("\n>>>> temp_value: %lu", temp_value);
    }
    LL_free_iter(iter);

    //
    LL_free(&short_int_list, NULL);
}
