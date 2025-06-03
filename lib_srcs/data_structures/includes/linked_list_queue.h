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

struct LListQueueNode {          // linked list queue node
    void *data;                  // Pointer to data
    struct LListQueueNode *next; // next node in the queue
};

struct LListQueue {              // linked list queue
    struct LListQueueNode *head; // head node
    struct LListQueueNode *tail; // tail node
};

/**
 * @brief
 *  Creates a new linked list queue
 *
 * @return Pointer to the linked list queue. NULL if memory allocation failed.
 */
extern struct LListQueue *LListQueueCreate();

/**
 * @brief
 *  Enqueues new data to a linked list queue
 *
 * @param queue     linked list queue to enqueue to
 * @param data      new data
 *
 * @return
 *   true  : enqueued successfully @n
 *   false : unable to allocate memory @n
 */
extern bool LListQueueEnqueue(struct LListQueue *queue, void *data);

/**
 * @brief
 *  Dequeues data from a linked list queue
 *
 * @param queue     linked list queue to dequeue
 *
 * @return Pointer to the dequeued data, NULL if the queue is empty.
 */
extern void *LListQueueDequeue(struct LListQueue *queue);

/**
 * @brief
 *  Deletes a linked list queue and frees its data if given a function to do so.
 *
 * @param queue         linked list queue to delete
 * @param free_data     function to free data, NULL if not needed
 */
extern void LListQueueClear(struct LListQueue **queue,
                            void (*free_data)(void *));
#endif