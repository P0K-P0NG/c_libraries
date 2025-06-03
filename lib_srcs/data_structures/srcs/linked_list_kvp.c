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
#include <stdlib.h>
#include <string.h>

struct LListKVP *LListKVPCreate() { return calloc(1, sizeof(struct LListKVP)); }

void LListKVPClear(struct LListKVP **list, void (*free_key)(void *),
                   void (*free_data)(void *))
{
    struct LListKVPNode *curr = (*list)->head;
    while (curr != NULL) {
        struct LListKVPNode *prev = curr;
        curr = curr->next;
        if (free_key != NULL) {
            free_key(prev->key);
        }
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*list);
    *list = NULL;
}

bool LListKVPRemoveHead(struct LListKVP *list, void (*free_key)(void *),
                        void (*free_data)(void *))
{
    if (list->count == 0) {
        return false;
    }

    struct LListKVPNode *prev_head = list->head;
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

void *LListKVPRemove(struct LListKVP *list, void *key,
                     int (*comp_key)(const void *, const void *),
                     void (*free_key)(void *))
{
    struct LListKVPNode *expired = list->head;
    struct LListKVPNode *prev = NULL;
    void *data;
    while (expired != NULL && comp_key(expired->key, key) != 0) {
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

void LListKVPRemoveAll(struct LListKVP *list, void (*free_key)(void *),
                       void (*free_data)(void *))
{
    struct LListKVPNode *curr = list->head;
    while (curr != NULL) {
        struct LListKVPNode *prev = curr;
        curr = curr->next;
        if (free_key != NULL) {
            free_key(prev->key);
        }
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(struct LListKVP));
}

bool LListKVPAddHead(struct LListKVP *list, void *key, void *data)
{
    struct LListKVPNode *new_head = calloc(1, sizeof(struct LListKVPNode));
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

bool LListKVPAddTail(struct LListKVP *list, void *key, void *data)
{
    struct LListKVPNode *new_tail = calloc(1, sizeof(struct LListKVPNode));
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

bool LListKVPAdd(struct LListKVP *list, void *key, void *data,
                 int (*comp_key)(const void *, const void *))
{
    struct LListKVPNode *new_node = calloc(1, sizeof(struct LListKVPNode));
    if (new_node == NULL) {
        return false;
    }

    struct LListKVPNode *prev = NULL;
    struct LListKVPNode *curr = list->head;
    while (curr != NULL && comp_key(curr->key, key) < 0) {
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

void *LListKVPFind(struct LListKVP *list, const void *key,
                   int (*comp_key)(const void *, const void *))
{
    struct LListKVPNode *curr = list->head;
    while (curr != NULL && comp_key(curr->key, key) != 0) {
        curr = curr->next;
    }
    return curr->data;
}

int LListKVPFindAll(struct LListKVP *list, const void *key, void ***data_arr,
                    int (*comp_key)(const void *, const void *))
{
    struct LListKVP *data_list = LListKVPCreate();
    if (data_list == NULL) {
        return -1;
    }
    struct LListKVPNode *curr = list->head;
    for (int i = 0; curr != NULL; i++) {
        if (comp_key(curr->key, key) == 0
            && LListKVPAddTail(data_list, NULL, curr->data) == 0) {
            return -1;
        }
        curr = curr->next;
    }
    int count = data_list->count;
    *data_arr = malloc(count * sizeof(void *));
    if (*data_arr == NULL) {
        return -1;
    }
    LListKVPToPointerArr(data_list, *data_arr, count);
    LListKVPClear(&data_list, NULL, NULL);
    return count;
}

int LListKVPCountRepeats(struct LListKVP *list, const void *key,
                         int (*comp_key)(const void *, const void *))
{
    int count = 0;
    struct LListKVPNode *curr = list->head;
    while (curr != NULL) {
        if (comp_key(curr->key, key) == 0) {
            count++;
        }
        curr = curr->next;
    }
    return count;
}

void LListKVPTraverse(struct LListKVP *list, void (*func)(void *, void *))
{
    struct LListKVPNode *curr = list->head;
    while (curr != NULL) {
        func(curr->key, curr->data);
        curr = curr->next;
    }
}

void LListKVPToPointerArr(struct LListKVP *list, void **arr, int len)
{
    int min_len = len;
    if (min_len > list->count) {
        min_len = list->count;
    }
    struct LListKVPNode *curr = list->head;
    for (int i = 0; i < min_len; i++) {
        arr[i] = curr->data;
        curr = curr->next;
    }
}

void LListKVPToArr(struct LListKVP *list, void *arr, int len, size_t item_size)
{
    int min_len = len;
    if (min_len > list->count) {
        min_len = list->count;
    }
    struct LListKVPNode *curr = list->head;
    for (int i = 0; i < min_len; i++) {
        memcpy(arr + i * item_size, curr->data, item_size);
        curr = curr->next;
    }
}