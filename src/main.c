#include "stdio.h"
#include "utils/collections/single_link_list.h"

//
//
//
LinkList create_integer_list() {
    size_t stack_value = 9999;
    LinkList list = LinkList_from_value(sizeof(size_t), &stack_value, NULL);
    return list;
}

//
//
//
int main(int argc, char **argv) {
    LinkList list = LinkList_from_empty();
    LinkList int_list = create_integer_list();
    LinkList int_list_2 = create_integer_list();
    LinkList_free(&list, NULL);
    LinkList_free(&int_list, NULL);
    LinkList_free(&int_list_2, NULL);

    LinkList short_int_list = LinkList_from_empty();

    // Append a few nodes
    size_t values[] = {111, 222, 333, 444, 555};
    LinkList_append_value(&short_int_list, sizeof(uint16_t), &values[0], NULL);
    LinkList_append_value(&short_int_list, sizeof(uint16_t), &values[1], NULL);
    LinkList_append_value(&short_int_list, sizeof(uint16_t), &values[2], NULL);
    LinkList_append_value(&short_int_list, sizeof(uint16_t), &values[3], NULL);
    LinkList_append_value(&short_int_list, sizeof(uint16_t), &values[4], NULL);

    // Get back the iter and check all data
    LinkListIterator *iter = LinkList_iter(&short_int_list);
    for (size_t iter_index = 0; iter_index < iter->length; iter_index++) {
        size_t temp_value = *((uint16_t *)iter->data_arr[iter_index]);
        printf("\n>>>> temp_value: %lu", temp_value);
    }
    LinkList_free_iter(iter);

    //
    LinkList_free(&short_int_list, NULL);
}
