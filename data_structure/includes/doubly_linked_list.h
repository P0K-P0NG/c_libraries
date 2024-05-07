/**
 * @file doubly_linked_list.h
 * 
 * @brief 
 *  Structs and functions for doubly linked lists.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef struct doubly_node  // node in a doubly linked list
{
    void *data;                 // pointer to data
    struct doubly_node *next;   // next node in doubly linked list
    struct doubly_node *prev;   // next node in doubly linked list
} DOUBLY_NODE_T;

typedef struct doubly_linked_list
{
    DOUBLY_NODE_T *head;    // head node
    DOUBLY_NODE_T *tail;    // tail node
    int count;
} DOUBLY_LIST_T;

/**
 * @brief 
 *  Makes a new empty doubly linked list.
 * 
 * @return Pointer to new doubly linked list, NULL if memory allocation is unsuccessful.
 */
DOUBLY_LIST_T *doubly_list_create();

/**
 * @brief 
 *  Deletes a doubly linked list and it's data if a function for freeing it is given.
 * 
 * @param list          doubly linked list to delete
 * @param free_data     function to free data, NULL if not needed
 */
void doubly_list_clear(DOUBLY_LIST_T **list, void (*free_data)(void*));

/**
 * @brief 
 *  Deletes a given node in a doubly linked list and it's data 
 *  if a function for freeing it is given.
 * 
 * @param list          doubly linked list to remove from
 * @param node          pointer to the node to delete
 * @param free_data     function to free data, NULL if not needed
 * 
 * @return 
 *  1 : removal successful @n
 *  0 : node pointer is NULL @n
 */
int doubly_list_remove(DOUBLY_LIST_T *list, DOUBLY_NODE_T *node, void (*free_data)(void*));

/**
 * @brief 
 *  Deletes all nodes of doubly linked list (but not the list itself) and it's data 
 *  if a function for freeing it is given.
 * 
 * @param list          doubly linked list to remove from
 * @param free_data     function to free data, NULL if not needed
 */
void doubly_list_remove_all(DOUBLY_LIST_T *list, void (*free_data)(void*));

/**
 * @brief 
 *  Adds a node to start of a doubly linked list.
 * 
 * @param list  doubly linked list to add to
 * @param data  data of the new node
 * 
 * @return Pointer to the new node, NULL if memory allocation failed.
 */
DOUBLY_NODE_T *doubly_list_add_head(DOUBLY_LIST_T *list, void *data);

/**
 * @brief 
 *  Adds a node to end of a doubly linked list.
 * 
 * @param list  doubly linked list add to
 * @param data  data of the new node
 * 
 * @return Pointer to the new node, NULL if memory allocation failed.
 */
DOUBLY_NODE_T *doubly_list_add_tail(DOUBLY_LIST_T *list, void *data);

/**
 * @brief 
 *  Adds a node at the postion of an already existing node in a doubly linked list. 
 *  And pushes the old node back.
 * 
 * @param list          doubly linked list to add to
 * @param curr_node     current node at the postion to add to; NULL to add as new tail
 * @param data          data of the new node
 * 
 * @return Pointer to the new node, NULL if memory allocation failed.
 */
DOUBLY_NODE_T *doubly_list_add_at(DOUBLY_LIST_T *list, DOUBLY_NODE_T *curr_node, void *data);

/**
 * @brief 
 *  Adds a node to a doubly linked list at the position determined by the compare funtion.
 * 
 * @note 
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if data_1 should come before data_2 @n
 *  2) Returns int >= 0 if data_1 should come after data_2 @n
 * 
 * @param list          doubly linked list to add to
 * @param data          data of the new node
 * @param comp_func     function to compare data with
 * 
 * @return Pointer to the new node, NULL if memory allocation failed.
 */
DOUBLY_NODE_T *doubly_list_add_by_compare(DOUBLY_LIST_T *list, void *data, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Gets the node at the given index in a doubly linked list.
 * 
 * @param list  doubly linked list cointaing the node
 * @param idx   index to get data from
 * 
 * @return Pointer to the node, NULL if node is not found or the index is invalid.
 */
DOUBLY_NODE_T *doubly_list_at(DOUBLY_LIST_T *list, int idx);

/**
 * @brief 
 *  Gets the first node with matching data in a doubly linked list using a given key 
 *  and compare function in a doubly linked list.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't. @n
 *  Compare function input No. : @n 
 *  1) data from the doubly linked list @n 
 *  2) key @n 
 * 
 * @param list          doubly linked list to search
 * @param key           key to compare the data with
 * @param comp_func     function to compare data and key
 * 
 * @return Pointer to the data, NULL if data is not found
 */
DOUBLY_NODE_T *doubly_list_find(DOUBLY_LIST_T *list, const void *key, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Traverses through a doubly linked list head to tail and preforms a given function on all its data.
 * 
 * @param list  doubly linked list to traverse
 * @param func  function to preform on data
 */
void doubly_list_traverse(DOUBLY_LIST_T *list, void (*func)(void*));
#endif