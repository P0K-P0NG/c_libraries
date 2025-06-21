/**
 * @file doubly_linked_list.c
 *
 * @brief
 *  Structs and functions for doubly linked lists.
 *
 * @implements
 *  doubly_linked_list.h
 *  _extend_doubly_linked_list.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#include "doubly_linked_list.h"
#include "_extend_doubly_linked_list.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

DLList_t *DLListCreate() { return calloc(1, sizeof(DLList_t)); }

void DLListClear(DLList_t **p_list, void (*free_data)(void *))
{
    assert(p_list != NULL);
    assert(*p_list != NULL);

    DLListNode_t *curr_node = (*p_list)->head;
    while (curr_node != NULL) {
        DLListNode_t *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*p_list);
    *p_list = NULL;
}

void DLListRemove(DLList_t *list, DLListNode_t *node,
                  void (*free_data)(void *))
{
    assert(list != NULL);
    assert(node != NULL);

    list->count -= 1;
    if (node == list->head) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }
    if (node == list->tail) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }
    if (free_data != NULL) {
        free_data(node->data);
    }
    free(node);
}

void DLListRemoveAll(DLList_t *list, void (*free_data)(void *))
{
    assert(list != NULL);

    DLListNode_t *curr_node = list->head;
    while (curr_node != NULL) {
        DLListNode_t *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(DLList_t));
}

DLListNode_t *DLListAddHead(DLList_t *list, void *data)
{
    assert(list != NULL);

    DLListNode_t *new_head = calloc(1, sizeof(DLListNode_t));
    if (new_head == NULL) {
        return NULL;
    }

    if (list->tail == NULL) {
        list->tail = new_head;
    } else {
        list->head->prev = new_head;
    }
    new_head->next = list->head;
    new_head->data = data;
    list->head = new_head;
    list->count += 1;
    return new_head;
}

DLListNode_t *DLListAddTail(DLList_t *list, void *data)
{
    assert(list != NULL);

    DLListNode_t *new_tail = calloc(1, sizeof(DLListNode_t));
    if (new_tail == NULL) {
        return NULL;
    }

    if (list->head == NULL) {
        list->head = new_tail;
    } else {
        list->tail->next = new_tail;
    }
    new_tail->prev = list->tail;
    new_tail->data = data;
    list->tail = new_tail;
    list->count += 1;
    return new_tail;
}

DLListNode_t *DLListAddAt(DLList_t *list,
                               DLListNode_t *curr_node, void *data)
{
    assert(list != NULL);
    assert(curr_node != NULL);

    DLListNode_t *new_node = calloc(1, sizeof(DLListNode_t));
    if (new_node == NULL) {
        return NULL;
    }

    if (curr_node == list->head) {
        list->head = new_node;
    } else {
        curr_node->prev->next = new_node;
    }
    if (curr_node == NULL) {
        new_node->prev = list->tail;
        list->tail = new_node;
    } else {
        curr_node->next->prev = new_node;
        new_node->prev = curr_node->prev;
    }
    new_node->next = curr_node;
    new_node->data = data;
    list->count += 1;
    return new_node;
}

DLListNode_t *DLListAddByCompare(DLList_t *list, void *data,
                                      int (*comp_func)(const void *,
                                                       const void *))
{
    assert(list != NULL);
    assert(comp_func != NULL);

    DLListNode_t *new_node = calloc(1, sizeof(DLListNode_t));
    if (new_node == NULL) {
        return NULL;
    }

    DLListNode_t *curr_node = list->head;
    while (curr_node != NULL && comp_func(curr_node->data, data) < 0) {
        curr_node = curr_node->next;
    }
    if (curr_node == list->head) {
        list->head = new_node;
    } else {
        curr_node->prev->next = new_node;
    }
    if (curr_node == NULL) {
        new_node->prev = list->tail;
        list->tail = new_node;
    } else {
        curr_node->next->prev = new_node;
        new_node->prev = curr_node->prev;
    }
    new_node->next = curr_node;
    new_node->data = data;
    list->count += 1;
    return new_node;
}

DLListNode_t *DLListAt(DLList_t *list, size_t idx)
{
    assert(list != NULL);

    if (idx >= list->count || idx < 0)
        return NULL;

    size_t diff = list->count - idx - 1;
    DLListNode_t *curr_node;
    if (diff > idx) {
        curr_node = list->tail;
        for (size_t i = 0; i < diff; i++) {
            curr_node = curr_node->prev;
        }
    } else {
        curr_node = list->head;
        for (size_t i = 0; i < idx; i++) {
            curr_node = curr_node->next;
        }
    }
    return curr_node;
}

DLListNode_t *DLListFind(DLList_t *list, const void *key,
                              int (*comp_func)(const void *, const void *))
{
    assert(list != NULL);

    DLListNode_t *curr_node = list->head;
    while (curr_node != NULL && comp_func(curr_node->data, key) != 0) {
        curr_node = curr_node->next;
    }
    return curr_node;
}

void DLListTraverse(DLList_t *list, void (*func)(void *))
{
    assert(list != NULL);
    assert(func != NULL);

    DLListNode_t *curr_node = list->head;
    while (curr_node != NULL) {
        func(curr_node->data);
        curr_node = curr_node->next;
    }
}

void _extend_DLListTraverse(DLList_t *list, void *(*extract_func)(void *),
                            void (*func)(void *))
{
    assert(list != NULL);
    assert(func != NULL);

    DLListNode_t *curr_node = list->head;
    while (curr_node != NULL) {
        func(extract_func(curr_node->data));
        curr_node = curr_node->next;
    }
}