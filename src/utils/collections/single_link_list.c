#include "single_link_list.h"

#if ENABLE_DEBUG_LOG
#include <stdio.h>

#include "../log.h"
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------
// LinkListNdoe
//----------------------------------------------------------------------------

struct LLNode {
    // The heap-allocated `data` should own by copyit via the `CloneFromFunc`
    // if `data` is NOT a primitive type.
    void *_data;
    struct LLNode *_next;
};

/*
 * Return node data pointer
 */
void *LLNode_get_data(const LinkListNode self) { return self->_data; }

/*
 * Return next node pointer
 */
LinkListNode LL_get_next(const LinkListNode self) { return self->_next; }

//----------------------------------------------------------------------------
// LinkList
//----------------------------------------------------------------------------
struct LL {
    size_t _len;
    LinkListNode _head;
    LinkListNode _tail;
};

/*
 * Create empty list
 */
LinkList LL_from_empty() {
    LinkList list = malloc(sizeof(struct LL));
#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(SingleLinkList, from_empty, "self ptr: %p", list);
#endif
    *list = (struct LL){
        ._len = 0,
        ._head = NULL,
        ._tail = NULL,
    };

    return list;
}

/*
 * Create list and insert first node that copies from value
 */
LinkList LL_from_value(size_t item_size, void *value,
                       CloneFromFunc clone_from_func) {
    // Create first node
    LinkListNode node = malloc(sizeof(struct LLNode));
    *node = (struct LLNode){
        ._data = malloc(item_size),
        ._next = NULL,
    };

    // Copy data
    memcpy(node->_data, value, item_size);

#if ENABLE_DEBUG_LOG
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
    LinkList list = malloc(sizeof(struct LL));
#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(SingleLinkList, from_value, "self ptr: %p, from node ptr: %",
              list);
#endif
    *list = (struct LL){
        ._len = 1,
        ._head = node,
        ._tail = node,
    };

    return list;
}

/*
 * Create list and insert first node that copies from value
 */
LinkList LL_from_array(size_t item_size, void *array,
                       CloneFromFunc clone_from_func) {}

/*
 * Return the link length
 */
size_t LL_length(const LinkList self) { return self->_len; }

/*
 * Return the header (first node) pointer
 */
const LinkListNode LL_get_head(const LinkList self) { return self->_head; }

/*
 * Return the header (first node) data pointer
 */
const void *LL_get_head_data(const LinkList self) {
    return (self->_head != NULL) ? self->_head->_data : NULL;
}

/*
 * Return the tail (last node) pointer
 */
const LinkListNode LL_get_tail(const LinkList self) { return self->_tail; }

/*
 * Return the tail (last node) data pointer
 */
const void *LL_get_tail_data(const LinkList self) {
    return (self->_tail != NULL) ? self->_tail->_data : NULL;
}

/*
 * Append to the tail
 *
 * Example:
 *
 * ```c
 * // Append a few nodes
 * LL short_int_list = LL_from_empty();
 * size_t values[] = {111, 222, 333, 444, 555};
 * LL_append_value(&short_int_list, sizeof(uint16_t), &values[0], NULL);
 * LL_append_value(&short_int_list, sizeof(uint16_t), &values[1], NULL);
 * LL_append_value(&short_int_list, sizeof(uint16_t), &values[2], NULL);
 * LL_append_value(&short_int_list, sizeof(uint16_t), &values[3], NULL);
 * LL_append_value(&short_int_list, sizeof(uint16_t), &values[4], NULL);
 * ```
 *
 */
void LL_append_value(LinkList self, size_t item_size, void *value,
                     CloneFromFunc clone_from_func) {
    // Create append node
    LinkListNode node = malloc(sizeof(struct LLNode));
    *node = (struct LLNode){
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

//----------------------------------------------------------------------------
// Iterator
//----------------------------------------------------------------------------

/*
 * Return a `Iterator` pointer from the `LinkLiist`:
 *
 * `Iterator.length`: Shows how many data pointer in `Iterator.data_arr`.
 *
 * `Iterator.data_arr`: Stores all list node data pointer, you need to convert
 *                      the correct data type before using it. If
 * `Iterator.length` is zeor, DO NOT access this array!!!
 *
 * The returned `Iterator` pointer has to be freed by calling `LL_free_iter()`.
 *
 * Example:
 *
 * ```c
 *
 * // Get back the iter and check all data
 * LL short_int_list = LL_from_empty();
 * // .... append_value
 * LLIterator *iter = LL_iter(&short_int_list);
 * for (size_t iter_index = 0; iter_index < iter->length; iter_index++) {
 *     size_t temp_value = *((uint16_t *)iter->data_arr[iter_index]);
 *     printf("\n>>>> temp_value: %lu", temp_value);
 * }
 * LL_free_iter(iter);
 *
 * ```
 */
LLIterator *LL_iter(const LinkList self) {
    if (self->_len <= 0) {
        LLIterator *iter = malloc(sizeof(LLIterator));
        iter->length = 0;

        return iter;
    }

    LLIterator *iter = malloc(sizeof(LLIterator) + self->_len * sizeof(void *));
    iter->length = self->_len;

    // Pointer to first node
    LinkListNode current = self->_head;

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

/*
 * Free the given `LLIterator`
 */
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
LinkListNode LL_find(const void *query);

/*
 * `free_func`:
 *
 * When freeing a `LLNode` instance, the best way to avoid memory issue
 * is to call the original `DataType.free(node->data)`, just in case `data` is
 * a complicated struct instance
 */
void LL_free(LinkList self, FreeFunc free_func) {
    if (self == NULL) return;

#ifdef ENABLE_DEBUG_LOG
    size_t free_node_data_amount = 0;
    size_t free_node_amount = 0;
#endif

    // Current node
    LinkListNode current = self->_head;

    while (current != NULL) {
        // Free current node data
        if (current->_data != NULL) {
            if (free_func != NULL) {
                free_func(current->_data);
            } else {
                free(current->_data);
            }
#ifdef ENABLE_DEBUG_LOG
            free_node_data_amount++;
#endif
            current->_data = NULL;
        }

        LinkListNode node_to_free = current;

        // Point to next node
        current = current->_next;

        // Free current node
        free(node_to_free);
#ifdef ENABLE_DEBUG_LOG
        free_node_amount++;
#endif
    }

    self->_len = 0;
    self->_head = NULL;
    self->_tail = NULL;
    free(self);

#ifdef ENABLE_DEBUG_LOG
    DEBUG_LOG(SingleLinkList, free,
              "self ptr: %p, total free node amount: %lu, total free node data "
              "amount: %lu",
              self, free_node_amount, free_node_data_amount);
#endif
}
