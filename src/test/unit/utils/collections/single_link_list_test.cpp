#include <gtest/gtest.h>

extern "C" {
#include "../../../../utils/collections/single_link_list.h"
}

//
//
//
TEST(SingleLinkList, CreateEmptyList) {
    SMART_LINKLIST(list) = LL_from_empty();
    ASSERT_EQ(LL_length(list), 0);
    ASSERT_EQ(LL_get_head(list), nullptr);
    ASSERT_EQ(LL_get_tail(list), nullptr);
}

//
//
//
LinkList create_integer_list() {
    size_t stack_value = 9999;
    LinkList list = LL_from_value(sizeof(size_t), &stack_value);
    return list;
}

TEST(SingleLinkList, IntegerListWithOneNode) {
    SMART_LINKLIST(int_list) = create_integer_list();
    LinkListNode head = LL_get_head(int_list);
    ASSERT_EQ(LL_length(int_list), 1);
    ASSERT_NE(head, nullptr);
    ASSERT_NE(LL_get_tail(int_list), nullptr);
    ASSERT_EQ(LLNode_get_next(head), nullptr);
    ASSERT_EQ(*((size_t *)LL_get_head_data(int_list)), 9999);
}

//
//
//
LinkList create_double_list() {
    double stack_value = 8888.888;
    LinkList list = LL_from_value(sizeof(double), &stack_value);

    return list;
}

TEST(SingleLinkList, DoubleListWithOneNode) {
    SMART_LINKLIST(double_list) = create_double_list();
    LinkListNode head = LL_get_head(double_list);
    ASSERT_EQ(LL_length(double_list), 1);
    ASSERT_NE(head, nullptr);
    ASSERT_NE(LL_get_tail(double_list), nullptr);
    ASSERT_EQ(LLNode_get_next(head), nullptr);
    /* double double_data = *((double *)double_list.head->data); */
    /* printf("\n>>> double_data: %f", double_data); */
    ASSERT_EQ(*((double *)LL_get_head_data(double_list)), 8888.888);
}

TEST(SingleLinkList, IntListAppendNode) {
    SMART_LINKLIST(short_int_list) = LL_from_empty();

    // Append a few nodes
    size_t values[] = {111, 222, 333, 444, 555};
    LL_append_value(short_int_list, sizeof(uint16_t), &values[0]);
    LL_append_value(short_int_list, sizeof(uint16_t), &values[1]);
    LL_append_value(short_int_list, sizeof(uint16_t), &values[2]);
    LL_append_value(short_int_list, sizeof(uint16_t), &values[3]);
    LL_append_value(short_int_list, sizeof(uint16_t), &values[4]);

    ASSERT_EQ(LL_length(short_int_list), 5);
    ASSERT_NE(LL_get_head(short_int_list), nullptr);
    ASSERT_NE(LL_get_tail(short_int_list), nullptr);

    // Get back the iter and check all data
    SMART_LINKLIST_ITERATOR(iter) = LL_iter(short_int_list);
    for (size_t iter_index = 0; iter_index < iter->length; iter_index++) {
        size_t temp_value = *((uint16_t *)iter->data_arr[iter_index]);
        // printf("\n>>> temp_value: %lu", temp_value);

        ASSERT_EQ(temp_value, values[iter_index]);
    }
}
