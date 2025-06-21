/**
 * @file linked_list_queue.h
 *
 * @brief
 *  Structs and functions for linked list queues.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-22
 */
#ifndef LINKED_LIST_QUEUE_H
#define LINKED_LIST_QUEUE_H

#include <stdbool.h>

typedef struct LListQueueNode {          // linked list queue node
    void *data;                  // Pointer to data
    struct LListQueueNode *next; // next node in the queue
} LListQueueNode_t;

typedef struct LListQueue {              // linked list queue
    LListQueueNode_t *head; // head node
    LListQueueNode_t *tail; // tail node
} LListQueue_t;

/**
 * @brief
 *  Creates a new linked list queue
 *
 * @return Pointer to the linked list queue. NULL if memory allocation failed.
 */
extern LListQueue_t *LListQueueCreate();

/**
 * @brief
 *  Enqueues new data to a linked list queue
 *
 * @param[in,out] queue     linked list queue to enqueue to
 * @param[in]     data      new data
 *
 * @return
 *   true  : enqueued successfully @n
 *   false : unable to allocate memory @n
 */
extern bool LListQueueEnqueue(LListQueue_t *queue, void *data);

/**
 * @brief
 *  Dequeues data from a linked list queue
 *
 * @param[in,out] queue     linked list queue to dequeue
 *
 * @return Pointer to the dequeued data, NULL if the queue is empty.
 */
extern void *LListQueueDequeue(LListQueue_t *queue);

/**
 * @brief
 *  Deletes a linked list queue and frees its data if given a function to do so.
 *
 * @param[in,out] p_queue       linked list queue to delete
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void LListQueueClear(LListQueue_t **p_queue,
                            void (*free_data)(void *));
#endif