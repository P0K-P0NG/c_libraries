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
#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct LList *LListCreate()
{
    struct LList *list = calloc(1, sizeof(struct LList));
    return list;
}

void LListClear(struct LList **list, void (*free_data)(void *))
{
    struct LListNode *curr = (*list)->head;
    while (curr != NULL) {
        struct LListNode *prev = curr;
        curr = curr->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*list);
    *list = NULL;
}

int LListPop(struct LList *list, void (*free_data)(void *))
{
    if (list->count == 0)
        return 0;

    struct LListNode *prev_head = list->head;
    if (list->head == list->tail) {
        list->tail = NULL;
    }
    list->head = list->head->next;
    list->count -= 1;
    if (free_data != NULL) {
        free_data(prev_head->data);
    }
    free(prev_head);
    return 1;
}

int LListRemoveAt(struct LList *list, int idx, void (*free_data)(void *))
{
    if (idx >= list->count || idx < 0)
        return 0;

    struct LListNode *expired;
    struct LListNode *prev = NULL;
    list->count -= 1;
    if (idx == 0) {
        expired = list->head;
        list->head = expired->next;
    } else {
        prev = list->head;
        for (int i = 1; i < idx; i++) {
            prev = prev->next;
        }
        expired = prev->next;
        prev->next = expired->next;
    }
    if (expired == list->tail) {
        list->tail = prev;
    }
    if (free_data != NULL) {
        free_data(expired->data);
    }
    free(expired);
    return 1;
}

void LListRemoveAll(struct LList *list, void (*free_data)(void *))
{
    struct LListNode *curr = list->head;
    while (curr != NULL) {
        struct LListNode *prev = curr;
        curr = curr->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(struct LList));
}

int LListPush(struct LList *list, void *data)
{
    struct LListNode *new_head = calloc(1, sizeof(struct LListNode));
    if (new_head == NULL)
        return 0;

    if (list->tail == NULL) {
        list->tail = new_head;
    }
    new_head->next = list->head;
    new_head->data = data;
    list->head = new_head;
    list->count += 1;
    return 1;
}

int LListAddTail(struct LList *list, void *data)
{
    struct LListNode *new_tail = calloc(1, sizeof(struct LListNode));
    if (new_tail == NULL)
        return 0;

    if (list->head == NULL) {
        list->head = new_tail;
    } else {
        list->tail->next = new_tail;
    }
    new_tail->data = data;
    list->tail = new_tail;
    list->count += 1;
    return 1;
}

int LListAddAt(struct LList *list, void *data, int idx)
{
    if (idx >= list->count || idx < 0)
        return -1;

    struct LListNode *new_node = calloc(1, sizeof(struct LListNode));
    if (new_node == NULL)
        return 0;

    if (idx == 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        struct LListNode *prev = list->head;
        for (int i = 1; i < idx; i++) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;
    }
    new_node->data = data;
    list->count += 1;
    return 1;
}

int LListAddByCompare(struct LList *list, void *data,
                      int (*comp_func)(const void *, const void *))
{
    struct LListNode *new_node = calloc(1, sizeof(struct LListNode));
    if (new_node == NULL)
        return 0;

    struct LListNode *prev = NULL;
    struct LListNode *curr = list->head;
    while (curr != NULL && comp_func(curr->data, data) < 0) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {
        list->head = new_node;
    } else {
        prev->next = new_node;
    }
    if (curr == NULL) {
        list->tail = new_node;
    }
    new_node->data = data;
    new_node->next = curr;
    list->count += 1;
    return 1;
}

int LListEditAt(struct LList *list, void *data, int idx)
{
    if (idx >= list->count || idx < 0)
        return 0;

    struct LListNode *curr = list->head;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }
    curr->data = data;
    return 1;
}

void *LListDataAt(struct LList *list, int idx)
{
    if (idx >= list->count || idx < 0)
        return NULL;

    struct LListNode *curr = list->head;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }
    return curr->data;
}

void *LListData(struct LList *list, const void *key,
                int (*comp_func)(const void *, const void *))
{
    struct LListNode *curr = list->head;
    while (curr != NULL && comp_func(curr->data, key) != 0) {
        curr = curr->next;
    }
    return curr->data;
}

int LListAllData(struct LList *list, const void *key, void ***data_arr,
                 int (*comp_func)(const void *, const void *))
{
    struct LList *data_list = LListCreate();
    if (data_list == NULL)
        return -1;

    struct LListNode *curr = list->head;
    for (int i = 0; curr != NULL; i++) {
        if (comp_func(curr->data, key) == 0) {
            bool is_ok = LListAddTail(data_list, curr->data);
            if (!is_ok)
                return -1;
        }
        curr = curr->next;
    }
    int count = data_list->count;
    *data_arr = malloc(count * sizeof(void *));
    if (*data_arr == NULL) {
        return -1;
    }
    LListToPointerArr(data_list, *data_arr, count);
    LListClear(&data_list, NULL);
    return count;
}

int LListFindIdx(struct LList *list, const void *key,
                 int (*comp_func)(const void *, const void *))
{
    int i = 0;
    struct LListNode *curr = list->head;
    for (; curr != NULL && comp_func(curr->data, key) != 0; i++) {
        curr = curr->next;
    }
    if (curr == NULL) {
        i = -1;
    }
    return i;
}

int LListFindAllIdx(struct LList *list, const void *key, int **idx_arr,
                    int (*comp_func)(const void *, const void *))
{
    struct LList *idx_list = LListCreate();
    if (idx_list == NULL) {
        return -1;
    }
    struct LListNode *curr = list->head;
    for (int i = 0; curr != NULL; i++) {
        if (comp_func(curr->data, key) == 0) {
            int *new_idx = malloc(sizeof(int));
            if (new_idx == NULL) {
                return -1;
            }
            *new_idx = i;
            if (LListAddTail(idx_list, new_idx) == 0) {
                return -1;
            }
        }
        curr = curr->next;
    }
    int count = idx_list->count;
    *idx_arr = malloc(count * sizeof(int));
    if (*idx_arr == NULL) {
        return -1;
    }
    LListToArr(idx_list, (void *)*idx_arr, count, sizeof(int));
    LListClear(&idx_list, free);
    return count;
}

void LListTraverse(struct LList *list, void (*func)(void *))
{
    struct LListNode *curr = list->head;
    while (curr != NULL) {
        func(curr->data);
        curr = curr->next;
    }
}

void LListToPointerArr(struct LList *list, void **arr, int len)
{
    int min_len = len;
    if (min_len > list->count) {
        min_len = list->count;
    }
    struct LListNode *curr = list->head;
    for (int i = 0; i < min_len; i++) {
        arr[i] = curr->data;
        curr = curr->next;
    }
}

void LListToArr(struct LList *list, void *arr, int len, size_t item_size)
{
    int min_len = len;
    if (min_len > list->count) {
        min_len = list->count;
    }
    struct LListNode *curr = list->head;
    for (int i = 0; i < min_len; i++) {
        memcpy(arr + i * item_size, curr->data, item_size);
        curr = curr->next;
    }
}