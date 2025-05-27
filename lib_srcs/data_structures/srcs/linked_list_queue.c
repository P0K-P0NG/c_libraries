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
#include "linked_list_queue.h"
#include <stdlib.h>

struct LListQueue *LListQueueCreate()
{
    return calloc(1, sizeof(struct LListQueue));
}

int LListQueueEnqueue(struct LListQueue *queue, void *data)
{
    struct LListQueueNode *new_tail = calloc(1, sizeof(struct LListQueueNode));
    if (new_tail == NULL) {
        return 0;
    }

    if (queue->head == NULL) {
        queue->head = new_tail;
    } else {
        queue->tail->next = new_tail;
    }
    new_tail->data = data;
    queue->tail = new_tail;
    return 1;
}

void *LListQueueDequeue(struct LListQueue *queue)
{
    void *data;
    struct LListQueueNode *prev_head = queue->head;
    if (prev_head == NULL) {
        return NULL;
    }
    if (prev_head == queue->tail) {
        queue->tail = NULL;
    }
    data = prev_head->data;
    queue->head = queue->head->next;
    free(prev_head);
    return data;
}

void LListQueueClear(struct LListQueue **queue, void (*free_data)(void *))
{
    struct LListQueueNode *curr = (*queue)->head;
    while (curr != NULL) {
        struct LListQueueNode *prev = curr;
        curr = curr->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*queue);
    *queue = NULL;
}