#include <gtest/gtest.h>

extern "C" {

//
// For comparing the pointer and `NULL`:
//
// Plz Make sure include inside `extern C`
// block. Otherwise, `gtest` will include `std::nullptr_t` (CPP type) which
// doesn't match the type, and you will end up with the following error:
//
// error: invalid operands to binary expression ('const LinkList' and 'const
// std::nullptr_t')
//
#include <stddef.h>

#include "single_link_list.h"
}

//
//
//
TEST(SingleLinkList, CreateEmptyList) {
    LinkList list = LL_from_empty();
    ASSERT_EQ(LL_length(list), 0);
    ASSERT_EQ(LL_get_head(list), NULL);
    ASSERT_EQ(LL_get_tail(list), NULL);

    LL_free(list, NULL);
}

//
//
//
LinkList create_integer_list() {
    size_t stack_value = 9999;
    LinkList list = LL_from_value(sizeof(size_t), &stack_value, NULL);
    return list;
}

TEST(SingleLinkList, IntegerListWithOneNode) {
    LinkList int_list = create_integer_list();
    LinkListNode head = LL_get_head(int_list);
    ASSERT_EQ(LL_length(int_list), 1);
    ASSERT_NE(head, NULL);
    ASSERT_NE(LL_get_tail(int_list), NULL);
    ASSERT_EQ(LLNode_get_next(head), NULL);
    ASSERT_EQ(*((size_t *)LL_get_head_data(int_list)), 9999);

    LL_free(int_list, NULL);
}

//
//
//
LinkList create_double_list() {
    double stack_value = 8888.888;
    LinkList list = LL_from_value(sizeof(double), &stack_value, NULL);

    return list;
}

TEST(SingleLinkList, DoubleListWithOneNode) {
    LinkList double_list = create_double_list();
    LinkListNode head = LL_get_head(double_list);
    ASSERT_EQ(LL_length(double_list), 1);
    ASSERT_NE(head, NULL);
    ASSERT_NE(LL_get_tail(double_list), NULL);
    ASSERT_EQ(LLNode_get_next(head), NULL);
    /* double double_data = *((double *)double_list.head->data); */
    /* printf("\n>>> double_data: %f", double_data); */
    ASSERT_EQ(*((double *)LL_get_head_data(double_list)), 8888.888);

    LL_free(double_list, NULL);
}

TEST(SingleLinkList, IntListAppendNode) {
    LinkList short_int_list = LL_from_empty();

    // Append a few nodes
    size_t values[] = {111, 222, 333, 444, 555};
    LL_append_value(short_int_list, sizeof(uint16_t), &values[0], NULL);
    LL_append_value(short_int_list, sizeof(uint16_t), &values[1], NULL);
    LL_append_value(short_int_list, sizeof(uint16_t), &values[2], NULL);
    LL_append_value(short_int_list, sizeof(uint16_t), &values[3], NULL);
    LL_append_value(short_int_list, sizeof(uint16_t), &values[4], NULL);

    ASSERT_EQ(LL_length(short_int_list), 5);
    ASSERT_NE(LL_get_head(short_int_list), NULL);
    ASSERT_NE(LL_get_tail(short_int_list), NULL);

    // Get back the iter and check all data
    LLIterator *iter = LL_iter(short_int_list);
    for (size_t iter_index = 0; iter_index < iter->length; iter_index++) {
        size_t temp_value = *((uint16_t *)iter->data_arr[iter_index]);
        // printf("\n>>> temp_value: %lu", temp_value);

        ASSERT_EQ(temp_value, values[iter_index]);
    }
    LL_free_iter(iter);

    //
    LL_free(short_int_list, NULL);
}
