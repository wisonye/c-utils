#ifndef __SINGLE_LINK_LIST_H__
#define __SINGLE_LINK_LIST_H__

#include <stddef.h>
#include <stdint.h>

//
// When creating a `LinkListNode` instance, the best way to avoid memory issue
// is to copy/clone the `original_value` to `LinkListNod.data`. That said the
// `LinkListNode` own the heap-allocated `data`.
//
typedef void *(*CloneFromFunc)(void *original_value);

//
// When freeing a `LinkListNode` instance, the best way to avoid memory issue
// is to call the original DataType.free(node->data), just in case `data` is
// a complicated struct instance
//
typedef void *(*FreeFunc)(void *data_to_free);

//
//
//
typedef struct LinkListNode {
    // The heap-allocated `data` should own by copyit via the `CloneFromFunc`
    // if `data` is NOT a primitive type.
    void *data;
    struct LinkListNode *next;

} LinkListNode;

//
//
//
typedef struct {
    size_t len;
    LinkListNode *head;
    LinkListNode *tail;

} LinkList;

//
//
//
LinkList LinkList_from_empty();

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
                             CloneFromFunc clone_from_func);

//
// Create list and insert first node that copies from value
//
//
// `clone_from_func`:
//
// When creating a `LinkListNode` instance, the best way to avoid memory issue
// is to copy/clone the `original_value` to `LinkListNod.data`. That said the
// `LinkListNode` own the heap-allocated `data`.
//
LinkList LinkList_from_array(size_t item_size, void *array,
                             CloneFromFunc clone_from_func);

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
void LinkList_free(LinkList *self, FreeFunc free_func);

#endif
