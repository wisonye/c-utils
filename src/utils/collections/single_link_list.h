#ifndef __SINGLE_LINK_LIST_H__
#define __SINGLE_LINK_LIST_H__

#include <stddef.h>
#include <stdint.h>

//
// When creating a `LLNode` instance, the best way to avoid memory issue
// is to copy/clone the `original_value` to `LinkListNod.data`. That said the
// `LLNode` own the heap-allocated `data`.
//
typedef void *(*CloneFromFunc)(void *original_value);

//
// When freeing a `LLNode` instance, the best way to avoid memory issue
// is to call the original DataType.free(node->data), just in case `data` is
// a complicated struct instance
//
typedef void *(*FreeFunc)(void *data_to_free);

//----------------------------------------------------------------------------
// LinkListNdoe
//----------------------------------------------------------------------------

//
//
//
typedef struct LLNode {
    // The heap-allocated `data` should own by copyit via the `CloneFromFunc`
    // if `data` is NOT a primitive type.
    void *_data;
    struct LLNode *_next;

} LLNode, LLNode;

//
//
//
void *LL_get_data(const LLNode *self);
LLNode *LL_get_next(const LLNode *self);

//----------------------------------------------------------------------------
// LinkList
//----------------------------------------------------------------------------

//
//
//
typedef struct {
    size_t _len;
    LLNode *_head;
    LLNode *_tail;

} LinkList, LL;

//
//
//
LL LL_from_empty();

//
// Create list and insert first node that copies from value
//
// `clone_from_func`:
//
// When creating a `LLNode` instance, the best way to avoid memory issue
// is to copy/clone the `original_value` to `LinkListNod.data`. That said the
// `LLNode` own the heap-allocated `data`.
//
LL LL_from_value(size_t item_size, void *value, CloneFromFunc clone_from_func);

//
// Create list and insert first node that copies from value
//
//
// `clone_from_func`:
//
// When creating a `LLNode` instance, the best way to avoid memory issue
// is to copy/clone the `original_value` to `LinkListNod.data`. That said the
// `LLNode` own the heap-allocated `data`.
//
LL LL_from_array(size_t item_size, void *array, CloneFromFunc clone_from_func);

//
// Getters
//
size_t LL_length(const LL *self);
const LLNode *LL_get_head(const LL *self);
const void *LL_get_head_data(const LL *self);
const LLNode *LL_get_tail(const LL *self);
const void *LL_get_tail_data(const LL *self);

//
// Append to the tail
//
void LL_append_value(LL *self, size_t item_size, void *value,
                     CloneFromFunc clone_from_func);

//
// Iterator
//
typedef struct {
    size_t length;
    void *data_arr[];
} LLIterator;

//
// Return a `Iterator` pointer from the `LinkLiist`:
//
// `Iterator.length`: Shows how many data pointer in `Iterator.data_arr`.
//
// `Iterator.data_arr`: Stores all list node data pointer, you need to convert
//                      the correct data type before using it. If
//                      `Iterator.length` is zeor, DO NOT access this array!!!
//
// The returned `Iterator` pointer has to be freed by calling `LL_free_iter()`.
//
LLIterator *LL_iter(const LL *self);
void LL_free_iter(LLIterator *iter);

//
// Querys
//
LLNode *LL_find(const void *query);

//
// `free_func`:
//
// When freeing a `LLNode` instance, the best way to avoid memory issue
// is to call the original `DataType.free(node->data)`, just in case `data` is
// a complicated struct instance
//
void LL_free(LL *self, FreeFunc free_func);

#endif
