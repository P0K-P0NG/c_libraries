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
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"

DLList *DLListCreate()
{
    return calloc(1, sizeof(DLList));
}

void DLListClear(DLList **list, void (*free_data)(void *))
{
    DLListNode *curr_node = (*list)->head;
    while (curr_node != NULL)
    {
        DLListNode *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*list);
    *list = NULL;
}

int DLListRemove(
    DLList *list, DLListNode *node, void (*free_data)(void *))
{
    if (node == NULL)
    {
        return 0;
    }
    /* MAIN LOGIC */

    list->count -= 1;
    if (node == list->head)
    {
        list->head = node->next;
    }
    else
    {
        node->prev->next = node->next;
    }
    if (node == list->tail)
    {
        list->tail = node->prev;
    }
    else
    {
        node->next->prev = node->prev;
    }
    if (free_data != NULL)
    {
        free_data(node->data);
    }
    free(node);
    return 1;
}

void DLListRemoveAll(DLList *list, void (*free_data)(void *))
{
    DLListNode *curr_node = list->head;
    while (curr_node != NULL)
    {
        DLListNode *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(DLList));
}

DLListNode *DLListAddHead(DLList *list, void *data)
{
    DLListNode *new_head = calloc(1, sizeof(DLListNode));
    if (new_head == NULL)
    {
        return NULL;
    }

    if (list->tail == NULL)
    {
        list->tail = new_head;
    }
    else
    {
        list->head->prev = new_head;
    }
    new_head->next = list->head;
    new_head->data = data;
    list->head = new_head;
    list->count += 1;
    return new_head;
}

DLListNode *DLListAddTail(DLList *list, void *data)
{
    DLListNode *new_tail = calloc(1, sizeof(DLListNode));
    if (new_tail == NULL)
    {
        return NULL;
    }

    if (list->head == NULL)
    {
        list->head = new_tail;
    }
    else
    {
        list->tail->next = new_tail;
    }
    new_tail->prev = list->tail;
    new_tail->data = data;
    list->tail = new_tail;
    list->count += 1;
    return new_tail;
}

DLListNode *DLListAddAt(
    DLList *list, DLListNode *curr_node, void *data)
{
    DLListNode *new_node = calloc(1, sizeof(DLListNode));
    if (new_node == NULL)
    {
        return NULL;
    }

    if (curr_node == list->head)
    {
        list->head = new_node;
    }
    else
    {
        curr_node->prev->next = new_node;
    }
    if (curr_node == NULL)
    {
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    else
    {
        curr_node->next->prev = new_node;
        new_node->prev = curr_node->prev;
    }
    new_node->next = curr_node;
    new_node->data = data;
    list->count += 1;
    return new_node;
}

DLListNode *DLListAddByCompare(
    DLList *list,
    void *data,
    int (*comp_func)(const void *, const void *))
{
    DLListNode *new_node = calloc(1, sizeof(DLListNode));
    if (new_node == NULL)
    {
        return NULL;
    }

    DLListNode *curr_node = list->head;
    while (curr_node != NULL && comp_func(curr_node->data, data) < 0)
    {
        curr_node = curr_node->next;
    }
    if (curr_node == list->head)
    {
        list->head = new_node;
    }
    else
    {
        curr_node->prev->next = new_node;
    }
    if (curr_node == NULL)
    {
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    else
    {
        curr_node->next->prev = new_node;
        new_node->prev = curr_node->prev;
    }
    new_node->next = curr_node;
    new_node->data = data;
    list->count += 1;
    return new_node;
}

DLListNode *DLListAt(DLList *list, int idx)
{
    if (idx >= list->count || idx < 0)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    int diff = list->count - idx - 1;
    DLListNode *curr_node;
    if (diff > idx)
    {
        curr_node = list->tail;
        for (int i = 0; i < diff; i++)
        {
            curr_node = curr_node->prev;
        }
    }
    else
    {
        curr_node = list->head;
        for (int i = 0; i < idx; i++)
        {
            curr_node = curr_node->next;
        }
    }
    return curr_node;
}

DLListNode *DLListFind(
    DLList *list,
    const void *key,
    int (*comp_func)(const void *, const void *))
{
    DLListNode *curr_node = list->head;
    while (curr_node != NULL && comp_func(curr_node->data, key) != 0)
    {
        curr_node = curr_node->next;
    }
    return curr_node;
}

void DLListTraverse(DLList *list, void (*func)(void *))
{
    DLListNode *curr_node = list->head;
    while (curr_node != NULL)
    {
        func(curr_node->data);
        curr_node = curr_node->next;
    }
}