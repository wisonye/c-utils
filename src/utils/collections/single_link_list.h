#ifndef __SINGLE_LINK_LIST_H__
#define __SINGLE_LINK_LIST_H__

#include <stddef.h>
#include <stdint.h>

/*
 * When creating a `LLNode` instance, the best way to avoid memory issue
 * is to copy/clone the `original_value` to `LinkListNod.data`. That said the
 * `LLNode` own the heap-allocated `data`.
 */
typedef void *(*CloneFromFunc)(void *original_value);

/*
 * When freeing a `LLNode` instance, the best way to avoid memory issue
 * is to call the original DataType.free(node->data), just in case `data` is
 * a complicated struct instance
 */
typedef void *(*FreeFunc)(void *data_to_free);

//----------------------------------------------------------------------------
// LinkListNdoe opaque pointer to `struct LLNode`
//----------------------------------------------------------------------------
typedef struct LLNode *LinkListNode;

/*
 * Return node data pointer
 */
void *LLNode_get_data(const LinkListNode self);

/*
 * Return next node pointer
 */
LinkListNode LLNode_get_next(const LinkListNode self);

//----------------------------------------------------------------------------
// LinkList opaque pointer to `struct LL`
//----------------------------------------------------------------------------
typedef struct LL *LinkList;

/*
 * Auto free `LinkList`
 */
void auto_free_linklist(LinkList *ptr);

/*
 * Define smart `LinkList` var that calls `LL_free()` automatically when the
 * variable is out of the scope
 *
 * ```c
 * SMART_LINKLIST(temp_list) = LL_from_empty();
 *
 * // (D) [ SingleLinkList ] > free - self ptr: 0x5472040, total free node
 * amount: 0, total free node data amount: 0
 * ```
 */
#define SMART_LINKLIST(x) __attribute__((cleanup(auto_free_linklist))) LinkList x

/*
 * Create empty list
 */
LinkList LL_from_empty();

/*
 * Create list and insert first node that copies from value
 */
LinkList LL_from_value(size_t item_size, void *value,
                       CloneFromFunc clone_from_func);

/*
 * Create list and insert first node that copies from value
 */
LinkList LL_from_array(size_t item_size, void *array,
                       CloneFromFunc clone_from_func);

/*
 * Return the link length
 */
size_t LL_length(const LinkList self);

/*
 * Return the header (first node) pointer
 */
const LinkListNode LL_get_head(const LinkList self);

/*
 * Return the header (first node) data pointer
 */
const void *LL_get_head_data(const LinkList self);

/*
 * Return the tail (last node) pointer
 */
const LinkListNode LL_get_tail(const LinkList self);

/*
 * Return the tail (last node) data pointer
 */
const void *LL_get_tail_data(const LinkList self);

/*
 * Append to the tail
 *
 * LinkList executes a shallow copy which means doesn't copy the internal
 * heap-allocated content!!!
 *
 * Example:
 *
 * ```c
 * // Append a few nodes
 * LinkList short_int_list = LL_from_empty();
 * size_t values[] = {111, 222, 333, 444, 555};
 * LL_append_value(short_int_list, sizeof(uint16_t), &values[0], NULL);
 * LL_append_value(short_int_list, sizeof(uint16_t), &values[1], NULL);
 * LL_append_value(short_int_list, sizeof(uint16_t), &values[2], NULL);
 * LL_append_value(short_int_list, sizeof(uint16_t), &values[3], NULL);
 * LL_append_value(short_int_list, sizeof(uint16_t), &values[4], NULL);
 * ```
 *
 */
void LL_append_value(LinkList self, size_t item_size, void *value,
                     CloneFromFunc clone_from_func);

/*
 * Iterator
 */
typedef struct {
    size_t length;
    void *data_arr[];
} LLIterator;

/*
 *
 */
void auto_free_linklist_iter(LLIterator **ptr);

/*
 * Define smart `LinkList` var that calls `LL_free()` automatically when the
 * variable is out of the scope
 *
 * ```c
 *  // Get back the iter and check all data
 *  SMART_LINKLIST_ITERATOR(iter) = LL_iter(short_int_list);
 *  for (usize iter_index = 0; iter_index < iter->length; iter_index++) {
 *      usize temp_value = *((uint16_t *)iter->data_arr[iter_index]);
 *      printf("\n>>>> temp_value: %lu", temp_value);
 *  }
 *
 * //
 * ```
 */
#define SMART_LINKLIST_ITERATOR(x) __attribute__((cleanup(auto_free_linklist_iter))) LLIterator *x

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
LLIterator *LL_iter(const LinkList self);

/*
 * Free the given `LLIterator`
 */
void LL_free_iter(LLIterator *iter);

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
void LL_free(LinkList self, FreeFunc free_func);

#endif
