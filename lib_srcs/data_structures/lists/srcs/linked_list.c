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
#include <assert.h>
#include <stdlib.h>
#include <string.h>

LList_t *LListCreate() { return calloc(1, sizeof(LList_t)); }

void LListClear(LList_t **p_list, void (*free_data)(void *))
{
    assert(p_list != NULL);
    assert(*p_list != NULL);

    LListNode_t *curr = (*p_list)->head;
    while (curr != NULL) {
        LListNode_t *prev = curr;
        curr = curr->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*p_list);
    *p_list = NULL;
}

bool LListRemoveHead(LList_t *list, void (*free_data)(void *))
{
    assert(list != NULL);

    if (list->count == 0)
        return false;

    LListNode_t *prev_head = list->head;
    if (list->head == list->tail) {
        list->tail = NULL;
    }
    list->head = list->head->next;
    list->count -= 1;
    if (free_data != NULL) {
        free_data(prev_head->data);
    }
    free(prev_head);
    return true;
}

bool LListRemoveAt(LList_t *list, size_t idx, void (*free_data)(void *))
{
    assert(list != NULL);

    if (idx >= list->count || idx < 0)
        return false;

    LListNode_t *expired;
    LListNode_t *prev = NULL;
    list->count -= 1;
    if (idx == 0) {
        expired = list->head;
        list->head = expired->next;
    } else {
        prev = list->head;
        for (size_t i = 1; i < idx; i++) {
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
    return true;
}

void LListRemoveAll(LList_t *list, void (*free_data)(void *))
{
    assert(list != NULL);

    LListNode_t *curr = list->head;
    while (curr != NULL) {
        LListNode_t *prev = curr;
        curr = curr->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(LList_t));
}

bool LListAddHead(LList_t *list, void *data)
{
    assert(list != NULL);

    LListNode_t *new_head = calloc(1, sizeof(LListNode_t));
    if (new_head == NULL)
        return false;

    if (list->tail == NULL) {
        list->tail = new_head;
    }
    new_head->next = list->head;
    new_head->data = data;
    list->head = new_head;
    list->count += 1;
    return true;
}

bool LListAddTail(LList_t *list, void *data)
{
    assert(list != NULL);

    LListNode_t *new_tail = calloc(1, sizeof(LListNode_t));
    if (new_tail == NULL)
        return false;

    if (list->head == NULL) {
        list->head = new_tail;
    } else {
        list->tail->next = new_tail;
    }
    new_tail->data = data;
    list->tail = new_tail;
    list->count += 1;
    return true;
}

int LListAddAt(LList_t *list, void *data, size_t idx)
{
    assert(list != NULL);

    if (idx >= list->count)
        return -1;

    LListNode_t *new_node = calloc(1, sizeof(LListNode_t));
    if (new_node == NULL)
        return 0;

    if (idx == 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        LListNode_t *prev = list->head;
        for (size_t i = 1; i < idx; i++) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;
    }
    new_node->data = data;
    list->count += 1;
    return 1;
}

bool LListAddByCompare(LList_t *list, void *data,
                       int (*comp_func)(const void *, const void *))
{
    assert(list != NULL);
    assert(comp_func != NULL);

    LListNode_t *new_node = calloc(1, sizeof(LListNode_t));
    if (new_node == NULL)
        return false;

    LListNode_t *prev = NULL;
    LListNode_t *curr = list->head;
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
    return true;
}

bool LListEditAt(LList_t *list, void *data, size_t idx)
{
    assert(list != NULL);

    if (idx >= list->count || idx < 0)
        return false;

    LListNode_t *curr = list->head;
    for (size_t i = 0; i < idx; i++) {
        curr = curr->next;
    }
    curr->data = data;
    return true;
}

void *LListDataAt(LList_t *list, size_t idx)
{
    assert(list != NULL);

    if (idx >= list->count || idx < 0)
        return NULL;

    LListNode_t *curr = list->head;
    for (size_t i = 0; i < idx; i++) {
        curr = curr->next;
    }
    return curr->data;
}

void *LListData(LList_t *list, const void *key,
                int (*comp_func)(const void *, const void *))
{
    assert(list != NULL);
    assert(comp_func != NULL);

    LListNode_t *curr = list->head;
    while (curr != NULL && comp_func(curr->data, key) != 0) {
        curr = curr->next;
    }
    return curr->data;
}

bool LListAllData(LList_t *list, const void *key, void ***ptr_arr,
                  size_t *count, int (*comp_func)(const void *, const void *))
{
    assert(list != NULL);
    assert(ptr_arr != NULL);
    assert(comp_func != NULL);

    LList_t *data_list = LListCreate();
    if (data_list == NULL)
        return false;

    LListNode_t *curr = list->head;
    for (size_t i = 0; curr != NULL; i++) {
        if (comp_func(curr->data, key) == 0) {
            bool is_ok = LListAddTail(data_list, curr->data);
            if (!is_ok)
                return false;
        }
        curr = curr->next;
    }
    *ptr_arr = malloc(data_list->count * sizeof(void *));
    if (*ptr_arr == NULL) {
        return false;
    }
    LListToPointerArr(data_list, *ptr_arr, data_list->count);
    LListClear(&data_list, NULL);
    *count = data_list->count;
    return true;
}

bool LListFindIdx(LList_t *list, const void *key, size_t *idx,
                  int (*comp_func)(const void *, const void *))
{
    assert(list != NULL);
    assert(comp_func != NULL);

    size_t i = 0;
    LListNode_t *curr = list->head;
    for (; curr != NULL && comp_func(curr->data, key) != 0; i++) {
        curr = curr->next;
    }
    if (curr == NULL) {
        return false;
    }
    *idx = i;
    return true;
}

bool LListFindAllIdx(LList_t *list, const void *key, int **idx_arr,
                     size_t *count,
                     int (*comp_func)(const void *, const void *))
{
    assert(list != NULL);
    assert(idx_arr != NULL);
    assert(comp_func != NULL);

    LList_t *idx_list = LListCreate();
    if (idx_list == NULL) {
        return false;
    }
    LListNode_t *curr = list->head;
    for (size_t i = 0; curr != NULL; i++) {
        if (comp_func(curr->data, key) == 0) {
            int *new_idx = malloc(sizeof(int));
            if (new_idx == NULL) {
                return false;
            }
            *new_idx = i;
            if (LListAddTail(idx_list, new_idx) == 0) {
                return false;
            }
        }
        curr = curr->next;
    }
    *idx_arr = malloc(idx_list->count * sizeof(int));
    if (*idx_arr == NULL) {
        return false;
    }
    LListToArr(idx_list, (void *)*idx_arr, idx_list->count, sizeof(int));
    LListClear(&idx_list, free);
    *count = idx_list->count;
    return true;
}

void LListTraverse(LList_t *list, void (*func)(void *))
{
    assert(list != NULL);
    assert(func != NULL);

    LListNode_t *curr = list->head;
    while (curr != NULL) {
        func(curr->data);
        curr = curr->next;
    }
}

void LListToPointerArr(LList_t *list, void **arr, size_t len)
{
    assert(list != NULL);
    assert(arr != NULL);

    size_t min_len = len;
    if (min_len > list->count) {
        min_len = list->count;
    }
    LListNode_t *curr = list->head;
    for (size_t i = 0; i < min_len; i++) {
        arr[i] = curr->data;
        curr = curr->next;
    }
}

void LListToArr(LList_t *list, void *arr, size_t len, size_t item_size)
{
    assert(list != NULL);
    assert(arr != NULL);

    size_t min_len = len;
    if (min_len > list->count) {
        min_len = list->count;
    }
    LListNode_t *curr = list->head;
    for (size_t i = 0; i < min_len; i++) {
        memcpy(arr + i * item_size, curr->data, item_size);
        curr = curr->next;
    }
}