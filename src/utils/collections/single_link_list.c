#include "single_link_list.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------
// LinkListNdoe
//----------------------------------------------------------------------------

void *LinkListNode_get_data(const LinkListNode *self) { return self->_data; }

LinkListNode *LinkListNode_get_next(const LinkListNode *self) {
    return self->_next;
}

//----------------------------------------------------------------------------
// LinkList
//----------------------------------------------------------------------------

//
// Create empty list
//
LinkList LinkList_from_empty() {
    LinkList list = {
        ._len = 0,
        ._head = NULL,
        ._tail = NULL,
    };

    return list;
}

//
// Create list and insert first node that copies from value
//
// `clone_from_func`:
//
// When creating a `LinkListNode` instance, the best way to avoid memory issue
// is to copy/clone the `original_value` to `LinkListNod.data`. That said the
// `LinkListNode` own the heap-allocated `data`.
//
LinkList LinkList_from_value(size_t item_size, void *value,
                             CloneFromFunc clone_from_func) {
    // Create first node
    LinkListNode *node = malloc(sizeof(LinkListNode));
    *node = (LinkListNode){
        ._data = malloc(item_size),
        ._next = NULL,
    };

    // Copy data
    memcpy(node->_data, value, item_size);

#if ENABLE_LINK_LIST_DEBUG
    // printf("\n>>> LinkList_from_value - node->data: %lu\n", *((size_t
    // *)node->data)); printf("\n>>> LinkList_from_value - node->data: %f\n",
    // *((double *)node->data));
#endif

    /* if (clone_from_func != NULL) { */
    /*     clone_from_func(value) : value; */
    /* } else { */
    /*     memcpy(node->data, value, item_size); */
    /* } */

    // Create list
    LinkList list = {
        ._len = 1,
        ._head = node,
        ._tail = node,
    };

    return list;
}

//
// Create list and insert first node that copies from value
//
// `clone_from_func`:
//
// When creating a `LinkListNode` instance, the best way to avoid memory issue
// is to copy/clone the `original_value` to `LinkListNod.data`. That said the
// `LinkListNode` own the heap-allocated `data`.
//
LinkList LinkList_from_array(size_t item_size, void *array,
                             CloneFromFunc clone_from_func) {}

//
//
//
size_t LinkList_length(const LinkList *self) { return self->_len; }

const LinkListNode *LinkList_get_head(const LinkList *self) {
    return self->_head;
}

const LinkListNode *LinkList_get_tail(const LinkList *self) {
    return self->_tail;
}

//
//
//
LinkListNode *LinkList_find(const void *query);

//
// `free_func`:
//
// When freeing a `LinkListNode` instance, the best way to avoid memory issue
// is to call the original `DataType.free(node->data)`, just in case `data` is
// a complicated struct instance
//
void LinkList_free(LinkList *self, FreeFunc free_func) {
    if (self == NULL) return;

    // Current node
    LinkListNode *current = self->_head;

    while (current != NULL) {
        // Free current node data
        if (current->_data != NULL) {
            if (free_func != NULL) {
                free_func(current->_data);
            } else {
                free(current->_data);
            }
            current->_data = NULL;
        }

        LinkListNode *node_to_free = current;

        // Point to next node
        current = current->_next;

        // Free current node
        free(node_to_free);
    }

    self->_len = 0;
    self->_head = NULL;
    self->_tail = NULL;
}
