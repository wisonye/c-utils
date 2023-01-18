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
}
