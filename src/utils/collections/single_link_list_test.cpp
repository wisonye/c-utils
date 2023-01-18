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
    LinkList list = LinkList_from_empty();
    ASSERT_EQ(list._len, 0);
    ASSERT_EQ(list._head, NULL);
    ASSERT_EQ(list._tail, NULL);

    LinkList_free(&list, NULL);
}

//
//
//
LinkList create_integer_list() {
    size_t stack_value = 9999;
    LinkList list = LinkList_from_value(sizeof(size_t), &stack_value, NULL);
    return list;
}

TEST(SingleLinkList, IntegerList) {
    LinkList int_list = create_integer_list();
    ASSERT_EQ(int_list._len, 1);
    ASSERT_NE(int_list._head, NULL);
    ASSERT_NE(int_list._tail, NULL);
    ASSERT_EQ(int_list._head->_next, NULL);
    ASSERT_EQ(*((size_t *)LinkList_get_head_data(&int_list)), 9999);
    ASSERT_EQ(*((size_t *)int_list._head->_data), 9999);

    LinkList_free(&int_list, NULL);
    ASSERT_EQ(int_list._len, 0);
    ASSERT_EQ(int_list._head, NULL);
    ASSERT_EQ(int_list._tail, NULL);
}

//
//
//
LinkList create_double_list() {
    double stack_value = 8888.888;
    LinkList list = LinkList_from_value(sizeof(double), &stack_value, NULL);

    return list;
}

TEST(SingleLinkList, DoubleList) {
    LinkList double_list = create_double_list();
    ASSERT_EQ(double_list._len, 1);
    ASSERT_NE(double_list._head, NULL);
    ASSERT_NE(double_list._tail, NULL);
    ASSERT_EQ(double_list._head->_next, NULL);
    /* double double_data = *((double *)double_list.head->data); */
    /* printf("\n>>> double_data: %f", double_data); */
    ASSERT_EQ(*((double *)LinkList_get_head_data(&double_list)), 8888.888);
    ASSERT_EQ(*((double *)double_list._head->_data), 8888.888);

    LinkList_free(&double_list, NULL);
    ASSERT_EQ(double_list._len, 0);
    ASSERT_EQ(double_list._head, NULL);
    ASSERT_EQ(double_list._tail, NULL);
}
