/**
 * @file linked_list_queue.c
 * 
 * @brief 
 *  Structs and functions for linked list queues.
 * 
 * @implements
 *  linked_list_queue.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-22
 */
#include <stdlib.h>
#include "linked_list_queue.h"

LINKED_QUEUE_T* linked_queue_create()
{
    return calloc(1, sizeof(LINKED_QUEUE_T));
}

int linked_queue_enqueue(LINKED_QUEUE_T *queue, void *data)
{
    QUEUE_NODE_T* new_tail = calloc(1, sizeof(QUEUE_NODE_T));
    if(new_tail == NULL)
    {
        return 0;
    }

    if(queue->head == NULL)
    {
        queue->head = new_tail;
    }
    else
    {
        queue->tail->next = new_tail;
    }
    new_tail->data = data;
    queue->tail = new_tail;
    return 1;
}

void* linked_queue_dequeue(LINKED_QUEUE_T *queue)
{
    void *data;
    QUEUE_NODE_T* prev_head = queue->head;
    if(prev_head == NULL)
    {
        return NULL;
    }
    if(prev_head == queue->tail)
    {
        queue->tail = NULL;
    }
    data = prev_head->data;
    queue->head = queue->head->next;
    free(prev_head);
    return data;
}

void linked_queue_clear(LINKED_QUEUE_T *queue, void (*free_data)(void*))
{
    QUEUE_NODE_T* curr = queue->head;
    while(curr != NULL)
    {
        QUEUE_NODE_T* prev = curr;
        curr = curr->next;
        if(free_data != NULL)
        {
            free_data(prev->data);
        }
        free(prev);
    }
    free(queue);
    queue = NULL;
}