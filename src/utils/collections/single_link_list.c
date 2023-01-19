#include "single_link_list.h"

#if ENABLE_LINK_LIST_DEBUG
#include <stdio.h>
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------
// LinkListNdoe
//----------------------------------------------------------------------------

void *LLNode_get_data(const LLNode *self) { return self->_data; }

LLNode *LLNode_get_next(const LLNode *self) { return self->_next; }

//----------------------------------------------------------------------------
// LinkList
//----------------------------------------------------------------------------

//
// Create empty list
//
LL LL_from_empty() {
    LL list = {
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
LL LL_from_value(size_t item_size, void *value, CloneFromFunc clone_from_func) {
    // Create first node
    LLNode *node = malloc(sizeof(LLNode));
    *node = (LLNode){
        ._data = malloc(item_size),
        ._next = NULL,
    };

    // Copy data
    memcpy(node->_data, value, item_size);

#if ENABLE_LINK_LIST_DEBUG
    // printf("\n>>> LL_from_value - node->data: %lu\n", *((size_t
    // *)node->data)); printf("\n>>> LL_from_value - node->data: %f\n",
    // *((double *)node->data));
#endif

    /* if (clone_from_func != NULL) { */
    /*     clone_from_func(value) : value; */
    /* } else { */
    /*     memcpy(node->data, value, item_size); */
    /* } */

    // Create list
    LL list = {
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
LL LL_from_array(size_t item_size, void *array, CloneFromFunc clone_from_func) {
}

//
// Getters
//
size_t LL_length(const LL *self) { return self->_len; }

const LLNode *LL_get_head(const LL *self) { return self->_head; }

const LLNode *LL_get_tail(const LL *self) { return self->_tail; }

const void *LL_get_head_data(const LL *self) {
    return (self->_head != NULL) ? self->_head->_data : NULL;
}

const void *LL_get_tail_data(const LL *self) {
    return (self->_tail != NULL) ? self->_tail->_data : NULL;
}

//
// Append to the tail
//
void LL_append_value(LL *self, size_t item_size, void *value,
                     CloneFromFunc clone_from_func) {
    // Create append node
    LLNode *node = malloc(sizeof(LLNode));
    *node = (LLNode){
        ._data = malloc(item_size),
        ._next = NULL,
    };

    // Copy data
    memcpy(node->_data, value, item_size);

    /* if (clone_from_func != NULL) { */
    /*     clone_from_func(value) : value; */
    /* } else { */
    /*     memcpy(node->data, value, item_size); */
    /* } */

    // Empty list case
    if (self->_len <= 0) {
        self->_head = node;
        self->_tail = node;
    }
    // Append to tail
    else {
        // Update `tail`
        if (self->_tail != NULL) {
            self->_tail->_next = node;
        }

        // Replace `tail`
        self->_tail = node;
    }

    self->_len++;
}

//
// Iterator
//
//

//
// Return a `Iterator` pointer from the `LinkLiist`:
//
// `Iterator.length`: Shows how many data pointer in `Iterator.data_arr`.
//
// `Iterator.data_arr`: Stores all list node data pointer, you need to convert
//                      the correct data type before using it. If
//                      `Iterator.length` is zeor, DO NOT access this array!!!
//
// The returned `Iterator` pointer has to be freed by calling
// `LL_free_iter()`.
//
LLIterator *LL_iter(const LL *self) {
    if (self->_len <= 0) {
        LLIterator *iter = malloc(sizeof(LLIterator));
        iter->length = 0;

        return iter;
    }

    LLIterator *iter = malloc(sizeof(LLIterator) + self->_len * sizeof(void *));
    iter->length = self->_len;

    // Pointer to first node
    LLNode *current = self->_head;

    // Ptr indext to walk through the `iter->data_arr`
    size_t data_ptr_index = 0;

    while (current != NULL) {
        iter->data_arr[data_ptr_index] = current->_data;
        data_ptr_index++;

        // Point to next node
        current = current->_next;
    }

    return iter;
}

void LL_free_iter(LLIterator *iter) {
    if (iter != NULL) {
#ifdef ENABLE_LINK_LIST_DEBUG
        printf("\n>>> LL_free_iter, iter address: %p", iter);
#endif
        free(iter);
    }
}

//
// Querys
//
LLNode *LL_find(const void *query);

//
// `free_func`:
//
// When freeing a `LinkListNode` instance, the best way to avoid memory issue
// is to call the original `DataType.free(node->data)`, just in case `data` is
// a complicated struct instance
//
void LL_free(LL *self, FreeFunc free_func) {
    if (self == NULL) return;

#ifdef ENABLE_LINK_LIST_DEBUG
    size_t free_node_data_amount = 0;
    size_t free_node_amount = 0;
#endif

    // Current node
    LLNode *current = self->_head;

    while (current != NULL) {
        // Free current node data
        if (current->_data != NULL) {
            if (free_func != NULL) {
                free_func(current->_data);
            } else {
                free(current->_data);
            }
#ifdef ENABLE_LINK_LIST_DEBUG
            free_node_data_amount++;
#endif
            current->_data = NULL;
        }

        LLNode *node_to_free = current;

        // Point to next node
        current = current->_next;

        // Free current node
        free(node_to_free);
#ifdef ENABLE_LINK_LIST_DEBUG
        free_node_amount++;
#endif
    }

    self->_len = 0;
    self->_head = NULL;
    self->_tail = NULL;

#ifdef ENABLE_LINK_LIST_DEBUG
    printf(
        "\n>>> LinkListFree - list address: %p, total free node amount: %lu, "
        "total free node data amount: %lu",
        self, free_node_amount, free_node_data_amount);
#endif
}
