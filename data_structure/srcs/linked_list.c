/**
 * @file linked_list.c
 *
 * @brief
 *  Structs and functions for linked lists.
 *
 * @implements
 *  linked_list.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

LList *LListCreate()
{
    LList *list = calloc(1, sizeof(LList));
    return list;
}

void LListClear(LList **list, void (*free_data)(void *))
{
    LListNode *curr = (*list)->head;
    while (curr != NULL)
    {
        LListNode *prev = curr;
        curr = curr->next;
        if (free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*list);
    *list = NULL;
}

int LListPop(LList *list, void (*free_data)(void *))
{
    if (list->count == 0)
    {
        return 0;
    }

    LListNode *prev_head = list->head;
    if (list->head == list->tail)
    {
        list->tail = NULL;
    }
    list->head = list->head->next;
    list->count -= 1;
    if (free_data != NULL)
    {
        free_data(prev_head->data);
    }
    free(prev_head);
    return 1;
}

int LListRemoveAt(LList *list, int idx, void (*free_data)(void *))
{
    if (idx >= list->count || idx < 0)
    {
        return 0;
    }
    /* MAIN LOGIC */

    LListNode *expired;
    LListNode *prev = NULL;
    list->count -= 1;
    if (idx == 0)
    {
        expired = list->head;
        list->head = expired->next;
    }
    else
    {
        prev = list->head;
        for (int i = 1; i < idx; i++)
        {
            prev = prev->next;
        }
        expired = prev->next;
        prev->next = expired->next;
    }
    if (expired == list->tail)
    {
        list->tail = prev;
    }
    if (free_data != NULL)
    {
        free_data(expired->data);
    }
    free(expired);
    return 1;
}

void LListRemoveAll(LList *list, void (*free_data)(void *))
{
    LListNode *curr = list->head;
    while (curr != NULL)
    {
        LListNode *prev = curr;
        curr = curr->next;
        if (free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(LList));
}

int LListPush(LList *list, void *data)
{
    LListNode *new_head = calloc(1, sizeof(LListNode));
    if (new_head == NULL)
    {
        return 0;
    }

    if (list->tail == NULL)
    {
        list->tail = new_head;
    }
    new_head->next = list->head;
    new_head->data = data;
    list->head = new_head;
    list->count += 1;
    return 1;
}

int LListAddTail(LList *list, void *data)
{
    LListNode *new_tail = calloc(1, sizeof(LListNode));
    if (new_tail == NULL)
    {
        return 0;
    }

    if (list->head == NULL)
    {
        list->head = new_tail;
    }
    else
    {
        list->tail->next = new_tail;
    }
    new_tail->data = data;
    list->tail = new_tail;
    list->count += 1;
    return 1;
}

int LListAddAt(LList *list, void *data, int idx)
{
    if (idx >= list->count || idx < 0)
    {
        return -1;
    }
    /* MAIN LOGIC */

    LListNode *new_node = calloc(1, sizeof(LListNode));
    if (new_node == NULL)
    {
        return 0;
    }

    if (idx == 0)
    {
        new_node->next = list->head;
        list->head = new_node;
    }
    else
    {
        LListNode *prev = list->head;
        for (int i = 1; i < idx; i++)
        {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;
    }
    new_node->data = data;
    list->count += 1;
    return 1;
}

int LListAddByCompare(
    LList *list,
    void *data,
    int (*comp_func)(const void *, const void *))
{
    LListNode *new_node = calloc(1, sizeof(LListNode));
    if (new_node == NULL)
    {
        return 0;
    }

    LListNode *prev = NULL;
    LListNode *curr = list->head;
    while (curr != NULL && comp_func(curr->data, data) < 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL)
    {
        list->head = new_node;
    }
    else
    {
        prev->next = new_node;
    }
    if (curr == NULL)
    {
        list->tail = new_node;
    }
    new_node->data = data;
    new_node->next = curr;
    list->count += 1;
    return 1;
}

int LListEditAt(LList *list, void *data, int idx)
{
    if (idx >= list->count || idx < 0)
    {
        return 0;
    }
    /* MAIN LOGIC */

    LListNode *curr = list->head;
    for (int i = 0; i < idx; i++)
    {
        curr = curr->next;
    }
    curr->data = data;
    return 1;
}

void *LListDataAt(LList *list, int idx)
{
    if (idx >= list->count || idx < 0)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    LListNode *curr = list->head;
    for (int i = 0; i < idx; i++)
    {
        curr = curr->next;
    }
    return curr->data;
}

void *LListData(LList *list, const void *key, int (*comp_func)(const void *, const void *))
{
    LListNode *curr = list->head;
    while (curr != NULL && comp_func(curr->data, key) != 0)
    {
        curr = curr->next;
    }
    return curr->data;
}

int LListAllData(LList *list, const void *key, void ***data_arr, int (*comp_func)(const void *, const void *))
{
    LList *data_list = LListCreate();
    if (data_list == NULL)
    {
        return -1;
    }
    LListNode *curr = list->head;
    for (int i = 0; curr != NULL; i++)
    {
        if (comp_func(curr->data, key) != 0)
            ;
        else if (LListAddTail(data_list, curr->data) == 0)
        {
            return -1;
        }
        curr = curr->next;
    }
    int count = data_list->count;
    *data_arr = malloc(count * sizeof(void *));
    if (*data_arr == NULL)
    {
        return -1;
    }
    LListToPointerArr(data_list, *data_arr, count);
    LListClear(&data_list, NULL);
    return count;
}

int LListFindIdx(LList *list, const void *key, int (*comp_func)(const void *, const void *))
{
    int i = 0;
    LListNode *curr = list->head;
    for (; curr != NULL && comp_func(curr->data, key) != 0; i++)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        i = -1;
    }
    return i;
}

int LListFindAllIdx(LList *list, const void *key, int **idx_arr, int (*comp_func)(const void *, const void *))
{
    LList *idx_list = LListCreate();
    if (idx_list == NULL)
    {
        return -1;
    }
    LListNode *curr = list->head;
    for (int i = 0; curr != NULL; i++)
    {
        if (comp_func(curr->data, key) == 0)
        {
            int *new_idx = malloc(sizeof(int));
            if (new_idx == NULL)
            {
                return -1;
            }
            *new_idx = i;
            if (LListAddTail(idx_list, new_idx) == 0)
            {
                return -1;
            }
        }
        curr = curr->next;
    }
    int count = idx_list->count;
    *idx_arr = malloc(count * sizeof(int));
    if (*idx_arr == NULL)
    {
        return -1;
    }
    LListToArr(idx_list, (void *)*idx_arr, count, sizeof(int));
    LListClear(&idx_list, free);
    return count;
}

void LListTraverse(LList *list, void (*func)(void *))
{
    LListNode *curr = list->head;
    while (curr != NULL)
    {
        func(curr->data);
        curr = curr->next;
    }
}

void LListToPointerArr(LList *list, void **arr, int len)
{
    int min_len = len;
    if (min_len > list->count)
    {
        min_len = list->count;
    }
    LListNode *curr = list->head;
    for (int i = 0; i < min_len; i++)
    {
        arr[i] = curr->data;
        curr = curr->next;
    }
}

void LListToArr(LList *list, void *arr, int len, size_t item_size)
{
    int min_len = len;
    if (min_len > list->count)
    {
        min_len = list->count;
    }
    LListNode *curr = list->head;
    for (int i = 0; i < min_len; i++)
    {
        memcpy(arr + i * item_size, curr->data, item_size);
        curr = curr->next;
    }
}