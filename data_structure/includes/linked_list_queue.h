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

typedef struct queue_node   // linked list queue node
{
    void *data;                 // Pointer to data
    struct queue_node *next;    // next node in the queue
} LListQueueNode;

typedef struct linked_list_queue    // linked list queue
{
    LListQueueNode *head;     // head node
    LListQueueNode *tail;     // tail node
} LListQueue;

/**
 * @brief 
 *  Creates a new linked list queue
 * 
 * @return Pointer to the linked list queue. NULL if memory allocation failed.
 */
extern LListQueue *LListQueueCreate();

/**
 * @brief 
 *  Enqueues new data to a linked list queue
 * 
 * @param queue     linked list queue to enqueue to
 * @param data      new data
 * 
 * @return
 *   1 : enqueued successfully @n 
 *   0 : unable to allocate memory @n
 */
extern int LListQueueEnqueue(LListQueue *queue, void *data);

/**
 * @brief 
 *  Dequeues data from a linked list queue
 * 
 * @param queue     linked list queue to dequeue
 * 
 * @return Pointer to the dequeued data, NULL if the queue is empty.
 */
extern void *LListQueueDequeue(LListQueue *queue);

/**
 * @brief 
 *  Deletes a linked list queue and frees its data if given a function to do so.
 * 
 * @param queue         linked list queue to delete
 * @param free_data     function to free data, NULL if not needed
 */
extern void LListQueueClear(LListQueue **queue, void (*free_data)(void*));
#endif