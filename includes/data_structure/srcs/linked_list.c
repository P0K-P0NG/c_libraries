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

LINKED_LIST_T* list_create()
{
    LINKED_LIST_T *list = calloc(1, sizeof(LINKED_LIST_T));
    return list;
}

void list_clear(LINKED_LIST_T *list, void (*free_data)(void*))
{
    NODE_T* curr = list->head;
    while(curr != NULL)
    {
        NODE_T* prev = curr;
        curr = curr->next;
        if(free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    free(list);
    list = NULL;
}

int list_pop(LINKED_LIST_T *list, void (*free_data)(void*))
{
    if(list->count == 0)
    {
        return 0;
    }

    NODE_T* prev_head = list->head;
    if(list->head == list->tail)
    {
        list->tail = NULL;
    }
    list->head = list->head->next;
    list->count -= 1;
    if(free_data != NULL)
    {
        free_data(prev_head->data);
    }
    free(prev_head);
    return 1;
}


int list_remove_at(LINKED_LIST_T *list, int idx, void (*free_data)(void*))
{    
    if(idx >= list->count || idx < 0)
    {
        return 0;
    }
    /* MAIN LOGIC */

    NODE_T *expired;
    NODE_T *prev = NULL;
    list->count -= 1;
    if(idx == 0)
    {
        expired = list->head;
        list->head = expired->next;
    }
    else
    {
        prev = list->head;
        for(int i = 1; i < idx; i++)
        {
            prev = prev->next;
        }
        expired = prev->next;
        prev->next = expired->next;
    }
    if(expired == list->tail)
    {
        list->tail = prev;
    }
    if(free_data != NULL)
    {
        free_data(expired->data);
    }
    free(expired);
    return 1;
}

void list_remove_all(LINKED_LIST_T *list, void (*free_data)(void*))
{
    NODE_T* curr = list->head;
    while(curr != NULL)
    {
        NODE_T* prev = curr;
        curr = curr->next;
        if(free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    memset(list, 0, sizeof(LINKED_LIST_T));
}

int list_push(LINKED_LIST_T *list, void *data)
{
    NODE_T* new_head = calloc(1, sizeof(NODE_T));
    if(new_head == NULL)
    {
        return 0;
    }

    if(list->tail == NULL)
    {
        list->tail = new_head;
    }
    new_head->next = list->head;
    new_head->data = data;
    list->head = new_head;
    list->count += 1;
    return 1;
}

int list_add_tail(LINKED_LIST_T *list, void *data)
{
    NODE_T* new_tail = calloc(1, sizeof(NODE_T));
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
    new_tail->data = data;
    list->tail = new_tail;
    list->count += 1;
    return 1;
}

int list_add_at(LINKED_LIST_T *list, void *data, int idx)
{
    if(idx >= list->count || idx < 0)
    {
        return -1;
    }
    /* MAIN LOGIC */

    NODE_T *new_node = calloc(1, sizeof(NODE_T));
    if(new_node == NULL)
    {
        return 0;
    }
    
    if(idx == 0)
    {
        new_node->next = list->head;
        list->head = new_node;
    }
    else
    {
        NODE_T *prev = list->head;
        for(int i = 1; i < idx; i++)
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

int list_add_by_compare(
    LINKED_LIST_T *list, 
    void *data, 
    int (*comp_func)(const void*, const void*))
{
    NODE_T *new_node = calloc(1, sizeof(NODE_T));
    if(new_node == NULL)
    {
        return 0;
    }
    
    NODE_T* prev = NULL;
    NODE_T* curr = list->head;
    while(curr != NULL && comp_func(curr->data, data) < 0)
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

int list_edit_at(LINKED_LIST_T *list, void *data, int idx)
{    
    if(idx >= list->count || idx < 0)
    {
        return 0;
    }
    /* MAIN LOGIC */

    NODE_T *curr = list->head;
    for(int i = 0; i < idx; i++)
    {
        curr = curr->next;
    }
    curr->data = data;
    return 1;
}

void* list_data_at(LINKED_LIST_T *list, int idx)
{
    if(idx >= list->count || idx < 0)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    NODE_T *curr = list->head;
    for(int i = 0; i < idx; i++)
    {
        curr = curr->next;
    }
    return curr->data;
}

void* list_data(LINKED_LIST_T *list, const void *key, int (*comp_func)(const void*, const void*))
{
    NODE_T *curr = list->head;
    while(curr != NULL && comp_func(curr->data, key) != 0)
    {
        curr = curr->next;
    }
    return curr->data;
}

int list_all_data(LINKED_LIST_T *list, const void *key, void ***data_arr, int (*comp_func)(const void*, const void*))
{
    LINKED_LIST_T *data_list = list_create();
    if(data_list == NULL)
    {
        return -1;
    }
    NODE_T *curr = list->head;
    for(int i = 0; curr != NULL; i++)
    {
        if(comp_func(curr->data, key) != 0);
        else if(list_add_tail(data_list, curr->data) == 0)
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
    list_to_pointer_arr(data_list, *data_arr, count);
    list_clear(data_list, NULL);
    return count;
}

int list_find_idx(LINKED_LIST_T *list, const void *key, int (*comp_func)(const void*, const void*))
{
    int i = 0;
    NODE_T *curr = list->head;
    for(; curr != NULL && comp_func(curr->data, key) != 0; i++)
    {
        curr = curr->next;
    }
    if(curr == NULL)
    {
        i = -1;
    }
    return i;
}

int list_find_all_idx(LINKED_LIST_T *list, const void *key, int **idx_arr, int (*comp_func)(const void*, const void*))
{
    LINKED_LIST_T* idx_list = list_create();
    if(idx_list == NULL)
    {
        return -1;
    }
    NODE_T *curr = list->head;
    for(int i = 0; curr != NULL; i++)
    {
        if(comp_func(curr->data, key) == 0)
        {
            int *new_idx = malloc(sizeof(int));
            if(new_idx == NULL)
            {
                return -1;
            }
            *new_idx = i;
            if(list_add_tail(idx_list, new_idx) == 0)
            {
                return -1;
            }
        }
        curr = curr->next;
    }
    int count = idx_list->count;
    *idx_arr = malloc(count*sizeof(int));
    if(*idx_arr == NULL)
    {
        return -1;
    }
    list_to_arr(idx_list, (void*) *idx_arr, count, sizeof(int));
    list_clear(idx_list, free);
    return count;
}

void list_traverse(LINKED_LIST_T *list, void (*func)(void*))
{
    NODE_T* curr = list->head;
    while(curr != NULL)
    {
        func(curr->data);
        curr = curr->next;
    }
}

void list_to_pointer_arr(LINKED_LIST_T *list, void **arr, int len)
{
    int min_len = len;
    if(min_len > list->count)
    {
        min_len = list->count;
    }
    NODE_T *curr = list->head;
    for(int i = 0; i < min_len; i++)
    {
        arr[i] = curr->data;
        curr = curr->next;
    }
}

void list_to_arr(LINKED_LIST_T *list, void *arr, int len, size_t item_size)
{
    int min_len = len;
    if(min_len > list->count)
    {
        min_len = list->count;
    }
    NODE_T *curr = list->head;
    for(int i = 0; i < min_len; i++)
    {
        memcpy(arr + i*item_size, curr->data, item_size);
        curr = curr->next;
    }
}