/**
 * @file linked_list_kvp.c
 *
 * @brief
 *  Structs and functions for key-value pair linked lists.
 *
 * @implements
 *  linked_list_kvp.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#include "linked_list_kvp.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

LListKVP_t *LListKVPCreate(int (*comp_key)(const void *, const void *))
{
    assert(comp_key != NULL);

    LListKVP_t *new_list = calloc(1, sizeof(LListKVP_t));
    new_list->comp_key = comp_key;
    return new_list;
}

void LListKVPClear(LListKVP_t **p_list, void (*free_key)(void *),
                   void (*free_data)(void *))
{
    assert(p_list != NULL);
    assert(*p_list != NULL);

    LListKVPNode_t *curr = (*p_list)->head;
    while (curr != NULL) {
        LListKVPNode_t *prev = curr;
        curr = curr->next;
        if (free_key != NULL) {
            free_key(prev->key);
        }
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*p_list);
    *p_list = NULL;
}

bool LListKVPRemoveHead(LListKVP_t *list, void (*free_key)(void *),
                        void (*free_data)(void *))
{
    assert(list != NULL);

    if (list->count == 0) {
        return false;
    }

    LListKVPNode_t *prev_head = list->head;
    if (list->head == list->tail) {
        list->tail = NULL;
    }
    list->head = list->head->next;
    list->count -= 1;
    if (free_key != NULL) {
        free_key(prev_head->key);
    }
    if (free_data != NULL) {
        free_data(prev_head->data);
    }
    free(prev_head);
    return true;
}

void *LListKVPRemove(LListKVP_t *list, void *key, void (*free_key)(void *))
{
    assert(list != NULL);

    LListKVPNode_t *expired = list->head;
    LListKVPNode_t *prev = NULL;
    void *data;
    while (expired != NULL && list->comp_key(expired->key, key) != 0) {
        prev = expired;
        expired = expired->next;
    }
    if (expired == NULL) {
        return NULL;
    }

    list->count -= 1;
    if (expired == list->head) {
        list->head = expired->next;
    } else {
        prev->next = expired->next;
    }
    if (expired == list->tail) {
        list->tail = prev;
    }
    if (free_key != NULL) {
        free_key(expired->key);
    }
    data = expired->data;
    free(expired);
    return data;
}

void LListKVPRemoveAll(LListKVP_t *list, void (*free_key)(void *),
                       void (*free_data)(void *))
{
    assert(list != NULL);

    LListKVPNode_t *curr = list->head;
    while (curr != NULL) {
        LListKVPNode_t *prev = curr;
        curr = curr->next;
        if (free_key != NULL) {
            free_key(prev->key);
        }
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(LListKVP_t));
}

bool LListKVPAddHead(LListKVP_t *list, void *key, void *data)
{
    assert(list != NULL);

    LListKVPNode_t *new_head = calloc(1, sizeof(LListKVPNode_t));
    if (new_head == NULL) {
        return false;
    }

    if (list->tail == NULL) {
        list->tail = new_head;
    }
    new_head->next = list->head;
    new_head->key = key;
    new_head->data = data;
    list->head = new_head;
    list->count += 1;
    return true;
}

bool LListKVPAddTail(LListKVP_t *list, void *key, void *data)
{
    assert(list != NULL);

    LListKVPNode_t *new_tail = calloc(1, sizeof(LListKVPNode_t));
    if (new_tail == NULL) {
        return false;
    }

    if (list->head == NULL) {
        list->head = new_tail;
    } else {
        list->tail->next = new_tail;
    }
    new_tail->key = key;
    new_tail->data = data;
    list->tail = new_tail;
    list->count += 1;
    return true;
}

bool LListKVPAdd(LListKVP_t *list, void *key, void *data)
{
    assert(list != NULL);

    LListKVPNode_t *new_node = calloc(1, sizeof(LListKVPNode_t));
    if (new_node == NULL) {
        return false;
    }

    LListKVPNode_t *prev = NULL;
    LListKVPNode_t *curr = list->head;
    while (curr != NULL && list->comp_key(curr->key, key) < 0) {
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

void *LListKVPFind(LListKVP_t *list, const void *key)
{
    assert(list != NULL);

    LListKVPNode_t *curr = list->head;
    while (curr != NULL && list->comp_key(curr->key, key) != 0) {
        curr = curr->next;
    }
    return curr->data;
}

bool LListKVPFindAll(LListKVP_t *list, const void *key, void ***ptr_arr,
                     size_t *count)
{
    assert(list != NULL);
    LListKVP_t *data_list = LListKVPCreate(list->comp_key);
    if (data_list == NULL) {
        return false;
    }
    LListKVPNode_t *curr = list->head;
    for (size_t i = 0; curr != NULL; i++) {
        if (list->comp_key(curr->key, key) == 0
            && LListKVPAddTail(data_list, NULL, curr->data) == 0) {
            return false;
        }
        curr = curr->next;
    }
    *ptr_arr = malloc(data_list->count * sizeof(void *));
    if (*ptr_arr == NULL) {
        return false;
    }
    LListKVPToPointerArr(data_list, *ptr_arr, data_list->count);
    LListKVPClear(&data_list, NULL, NULL);
    *count = data_list->count;
    return true;
}

size_t LListKVPCountRepeats(LListKVP_t *list, const void *key)
{
    assert(list != NULL);

    size_t count = 0;
    LListKVPNode_t *curr = list->head;
    while (curr != NULL) {
        if (list->comp_key(curr->key, key) == 0) {
            count++;
        }
        curr = curr->next;
    }
    return count;
}

void LListKVPTraverse(LListKVP_t *list, void (*func)(void *, void *))
{
    assert(list != NULL);

    LListKVPNode_t *curr = list->head;
    while (curr != NULL) {
        func(curr->key, curr->data);
        curr = curr->next;
    }
}

void LListKVPToPointerArr(LListKVP_t *list, void **arr, size_t len)
{
    assert(list != NULL);
    assert(arr != NULL);

    size_t min_len = len;
    if (min_len > list->count) {
        min_len = list->count;
    }
    LListKVPNode_t *curr = list->head;
    for (size_t i = 0; i < min_len; i++) {
        arr[i] = curr->data;
        curr = curr->next;
    }
}

void LListKVPToArr(LListKVP_t *list, void *arr, size_t len,
                   size_t item_size)
{
    assert(list != NULL);
    assert(arr != NULL);

    size_t min_len = len;
    if (min_len > list->count) {
        min_len = list->count;
    }
    LListKVPNode_t *curr = list->head;
    for (size_t i = 0; i < min_len; i++) {
        memcpy(arr + i * item_size, curr->data, item_size);
        curr = curr->next;
    }
}