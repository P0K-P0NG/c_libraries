/**
 * @file doubly_linked_list.c
 *
 * @brief
 *  Structs and functions for doubly linked lists.
 *
 * @implements
 *  doubly_linked_list.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#include "doubly_linked_list.h"
#include <stdlib.h>
#include <string.h>

struct DLList *DLListCreate() { return calloc(1, sizeof(struct DLList)); }

void DLListClear(struct DLList **list, void (*free_data)(void *))
{
    struct DLListNode *curr_node = (*list)->head;
    while (curr_node != NULL) {
        struct DLListNode *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*list);
    *list = NULL;
}

int DLListRemove(struct DLList *list, struct DLListNode *node,
                 void (*free_data)(void *))
{
    if (node == NULL)
        return 0;

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
    return 1;
}

void DLListRemoveAll(struct DLList *list, void (*free_data)(void *))
{
    struct DLListNode *curr_node = list->head;
    while (curr_node != NULL) {
        struct DLListNode *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(struct DLList));
}

struct DLListNode *DLListAddHead(struct DLList *list, void *data)
{
    struct DLListNode *new_head = calloc(1, sizeof(struct DLListNode));
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

struct DLListNode *DLListAddTail(struct DLList *list, void *data)
{
    struct DLListNode *new_tail = calloc(1, sizeof(struct DLListNode));
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

struct DLListNode *DLListAddAt(struct DLList *list,
                               struct DLListNode *curr_node, void *data)
{
    struct DLListNode *new_node = calloc(1, sizeof(struct DLListNode));
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

struct DLListNode *DLListAddByCompare(struct DLList *list, void *data,
                                      int (*comp_func)(const void *,
                                                       const void *))
{
    struct DLListNode *new_node = calloc(1, sizeof(struct DLListNode));
    if (new_node == NULL) {
        return NULL;
    }

    struct DLListNode *curr_node = list->head;
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

struct DLListNode *DLListAt(struct DLList *list, int idx)
{
    if (idx >= list->count || idx < 0)
        return NULL;

    int diff = list->count - idx - 1;
    struct DLListNode *curr_node;
    if (diff > idx) {
        curr_node = list->tail;
        for (int i = 0; i < diff; i++) {
            curr_node = curr_node->prev;
        }
    } else {
        curr_node = list->head;
        for (int i = 0; i < idx; i++) {
            curr_node = curr_node->next;
        }
    }
    return curr_node;
}

struct DLListNode *DLListFind(struct DLList *list, const void *key,
                              int (*comp_func)(const void *, const void *))
{
    struct DLListNode *curr_node = list->head;
    while (curr_node != NULL && comp_func(curr_node->data, key) != 0) {
        curr_node = curr_node->next;
    }
    return curr_node;
}

void DLListTraverse(struct DLList *list, void (*func)(void *))
{
    struct DLListNode *curr_node = list->head;
    while (curr_node != NULL) {
        func(curr_node->data);
        curr_node = curr_node->next;
    }
}