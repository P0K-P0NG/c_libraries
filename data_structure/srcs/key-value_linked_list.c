/**
 * @file key-value_linked_list.c
 * 
 * @brief 
 *  Structs and functions for key-value pair linked lists.
 * 
 * @implements
 *  key-value_linked_list.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#include <stdlib.h>
#include <string.h>
#include "key-value_linked_list.h"

KVP_LIST_T *kvp_list_create()
{
    return calloc(1, sizeof(KVP_LIST_T));
}

void kvp_list_clear(
    KVP_LIST_T **list, void (*free_key)(void*), void (*free_data)(void*))
{
    KVP_NODE_T *curr = (*list)->head;
    while(curr != NULL)
    {
        KVP_NODE_T *prev = curr;
        curr = curr->next;
        if(free_key != NULL)
        {
            free_key(prev->key);
        }
        if(free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*list);
    *list = NULL;
}

int kvp_list_remove_head(
    KVP_LIST_T *list, void (*free_key)(void*), void (*free_data)(void*))
{
    if(list->count == 0)
    {
        return 0;
    }

    KVP_NODE_T *prev_head = list->head;
    if(list->head == list->tail)
    {
        list->tail = NULL;
    }
    list->head = list->head->next;
    list->count -= 1;
    if(free_key != NULL)
    {
        free_key(prev_head->key);
    }
    if(free_data != NULL)
    {
        free_data(prev_head->data);
    }
    free(prev_head);
    return 1;
}


void *kvp_list_remove(
    KVP_LIST_T *list,                           void *key,  
    int (*comp_key)(const void*, const void*),  void (*free_key)(void*))
{
    KVP_NODE_T *expired = list->head;
    KVP_NODE_T *prev = NULL;
    void *data;
    while(expired != NULL && comp_key(expired->key, key) != 0)
    {
        prev = expired;
        expired = expired->next;
    }
    if(expired == NULL)
    {
        return NULL;
    }

    list->count -= 1;
    if(expired == list->head)
    {
        list->head = expired->next;
    }
    else
    {
        prev->next = expired->next;
    }
    if(expired == list->tail)
    {
        list->tail = prev;
    }
    if(free_key != NULL)
    {
        free_key(expired->key);
    }
    data = expired->data;
    free(expired);
    return data;
}

void kvp_list_remove_all(
    KVP_LIST_T *list, void (*free_key)(void*), void (*free_data)(void*))
{
    KVP_NODE_T *curr = list->head;
    while(curr != NULL)
    {
        KVP_NODE_T *prev = curr;
        curr = curr->next;
        if(free_key != NULL)
        {
            free_key(prev->key);
        }
        if(free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(KVP_LIST_T));
}

int kvp_list_add_head(KVP_LIST_T *list, void *key, void *data)
{
    KVP_NODE_T *new_head = calloc(1, sizeof(KVP_NODE_T));
    if(new_head == NULL)
    {
        return 0;
    }

    if(list->tail == NULL)
    {
        list->tail = new_head;
    }
    new_head->next = list->head;
    new_head->key = key;
    new_head->data = data;
    list->head = new_head;
    list->count += 1;
    return 1;
}

int kvp_list_add_tail(KVP_LIST_T *list, void *key, void *data)
{
    KVP_NODE_T *new_tail = calloc(1, sizeof(KVP_NODE_T));
    if(new_tail == NULL)
    {
        return 0;
    }

    if(list->head == NULL)
    {
        list->head = new_tail;
    }
    else
    {
        list->tail->next = new_tail;
    }
    new_tail->key = key;
    new_tail->data = data;
    list->tail = new_tail;
    list->count += 1;
    return 1;
}

int kvp_list_add(
    KVP_LIST_T *list,   void *key, 
    void *data,         int (*comp_key)(const void*, const void*))
{
    KVP_NODE_T *new_node = calloc(1, sizeof(KVP_NODE_T));
    if(new_node == NULL)
    {
        return 0;
    }
    
    KVP_NODE_T *prev = NULL;
    KVP_NODE_T *curr = list->head;
    while(curr != NULL && comp_key(curr->key, key) < 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if(prev == NULL)
    {
        list->head = new_node;
    }
    else
    {
        prev->next = new_node;
    }
    if(curr == NULL)
    {
        list->tail = new_node;
    }
    new_node->data = data;
    new_node->next = curr;
    list->count += 1;
    return 1;
}

void *kvp_list_find(
    KVP_LIST_T *list, 
    const void *key, 
    int (*comp_key)(const void*, const void*))
{
    KVP_NODE_T *curr = list->head;
    while(curr != NULL && comp_key(curr->key, key) != 0)
    {
        curr = curr->next;
    }
    return curr->data;
}

int kvp_list_find_all(
    KVP_LIST_T *list, const void *key, 
    void ***data_arr, int (*comp_key)(const void*, const void*))
{
    KVP_LIST_T *data_list = kvp_list_create();
    if(data_list == NULL)
    {
        return -1;
    }
    KVP_NODE_T *curr = list->head;
    for(int i = 0; curr != NULL; i++)
    {
        if(comp_key(curr->key, key) == 0 
            && kvp_list_add_tail(data_list, NULL, curr->data) == 0)
        {
            return -1;
        }
        curr = curr->next;
    }
    int count = data_list->count;
    *data_arr = malloc(count*sizeof(void*));
    if(*data_arr == NULL)
    {
        return -1;
    }
    kvp_list_to_pointer_arr(data_list, *data_arr, count);
    kvp_list_clear(&data_list, NULL, NULL);
    return count;
}

int kvp_list_count_repeats(
    KVP_LIST_T *list, 
    const void *key, 
    int (*comp_key)(const void*, const void*))
{
    int count = 0;
    KVP_NODE_T *curr = list->head;
    while(curr != NULL)
    {
        if(comp_key(curr->key, key) == 0)
        {
            count++;
        }
        curr = curr->next;
    }
    return count;
}

void kvp_list_traverse(KVP_LIST_T *list, void (*func)(void*, void*))
{
    KVP_NODE_T *curr = list->head;
    while(curr != NULL)
    {
        func(curr->key, curr->data);
        curr = curr->next;
    }
}

void kvp_list_to_pointer_arr(KVP_LIST_T *list, void **arr, int len)
{
    int min_len = len;
    if(min_len > list->count)
    {
        min_len = list->count;
    }
    KVP_NODE_T *curr = list->head;
    for(int i = 0; i < min_len; i++)
    {
        arr[i] = curr->data;
        curr = curr->next;
    }
}

void kvp_list_to_arr(KVP_LIST_T *list, void *arr, int len, size_t item_size)
{
    int min_len = len;
    if(min_len > list->count)
    {
        min_len = list->count;
    }
    KVP_NODE_T *curr = list->head;
    for(int i = 0; i < min_len; i++)
    {
        memcpy(arr + i*item_size, curr->data, item_size);
        curr = curr->next;
    }
}