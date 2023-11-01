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
} QUEUE_NODE_T;

typedef struct linked_list_queue    // linked list queue
{
    QUEUE_NODE_T *head;     // head node
    QUEUE_NODE_T *tail;     // tail node
} LINKED_QUEUE_T;

/**
 * @brief 
 *  Creates a new linked list queue
 * 
 * @return Pointer to the linked list queue. NULL if memory allocation failed.
 */
LINKED_QUEUE_T* linked_queue_create();

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
int linked_queue_enqueue(LINKED_QUEUE_T *queue, void *data);

/**
 * @brief 
 *  Dequeues data from a linked list queue
 * 
 * @param queue     linked list queue to dequeue
 * 
 * @return Pointer to the dequeued data, NULL if the queue is empty.
 */
void* linked_queue_dequeue(LINKED_QUEUE_T *queue);

/**
 * @brief 
 *  Deletes a linked list queue and frees its data if given a function to do so.
 * 
 * @param queue         linked list queue to delete
 * @param free_data     function to free data, NULL if not needed
 */
void linked_queue_clear(LINKED_QUEUE_T *queue, void (*free_data)(void*));
#endif