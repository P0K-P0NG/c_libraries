/**
 * @file linked_list.h
 * 
 * @brief 
 *  Structs and functions for linked lists.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct node // node in a linked list
{
    void *data;         // pointer to data
    struct node *next;  // next node in linked list
} NODE_T;

typedef struct linked_list
{
    NODE_T *head;   // head node
    NODE_T *tail;   // tail node
    int count;
} LINKED_LIST_T;

/**
 * @brief 
 *  Makes a new empty linked list.
 * 
 * @return Pointer to new linked list, NULL if memory allocation is unsuccessful.
 */
LINKED_LIST_T* list_create();

/**
 * @brief 
 *  Deletes a linked list and it's data if a function for freeing it is given.
 * 
 * @param list          linked list to delete
 * @param free_data     function to free data, NULL if not needed
 */
void list_clear(LINKED_LIST_T *list, void (*free_data)(void*));

/**
 * @brief 
 *  Deletes the first node in a linked list and it's data if a function for freeing it is given.
 * 
 * @param list          linked list to remove from
 * @param free_data     function to free data, NULL if not needed
 * 
 * @return 
 *  1 : removal successful @n
 *  0 : linked list is empty @n
 */
int list_pop(LINKED_LIST_T *list, void (*free_data)(void*));

/**
 * @brief 
 *  Deletes a node at the given index of a linked list and it's data 
 *  if a function for freeing it is given.
 * 
 * @param list          linked list to remove from
 * @param idx           index of the node to delete
 * @param free_data     function to free data, NULL if not needed
 * 
 * @return 
 *  1 : removal successful @n
 *  0 : invalid index @n
 */
int list_remove_at(LINKED_LIST_T *list, int idx, void (*free_data)(void*));

/**
 * @brief 
 *  Deletes all nodes of linked list (but not the list itself) and it's data 
 *  if a function for freeing it is given.
 * 
 * @param list          linked list to remove from
 * @param free_data     function to free data, NULL if not needed
 */
void list_remove_all(LINKED_LIST_T *list, void (*free_data)(void*));

/**
 * @brief 
 *  Adds a node to start of a linked list.
 * 
 * @param list  linked list add to
 * @param data  data of the new node
 * 
 * @return 
 *  1 : node added successfully @n
 *  0 : memory allocation falied @n
 */
int list_push(LINKED_LIST_T *list, void *data);

/**
 * @brief 
 *  Adds a node to end of a linked list.
 * 
 * @param list  linked list add to
 * @param data  data of the new node
 * 
 * @return 
 *  1 : node added successfully @n
 *  0 : memory allocation falied @n
 */
int list_add_tail(LINKED_LIST_T *list, void *data);

/**
 * @brief 
 *  Adds a node at the given index of a linked list.
 * 
 * @param list  linked list to add to
 * @param data  data of the new node
 * @param idx   index of the new node
 * 
 * @return 
 *   1 : node added successfully @n
 *   0 : memory allocation falied @n
 *  -1 : invalid index @n
 */
int list_add_at(LINKED_LIST_T *list, void *data, int idx);

/**
 * @brief 
 *  Adds a node to a linked list at the position determined by the compare funtion.
 * 
 * @note 
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if data_1 should come before data_2 @n
 *  2) Returns int >= 0 if data_1 should come after data_2 @n
 * 
 * @param list          linked list to add to
 * @param data          data of the new node
 * @param comp_func     function to compare data with
 * 
 * @return 
 *  1 : added successfully @n
 *  0 : memory allocation falied @n
 */
int list_add_by_compare(LINKED_LIST_T *list, void *data, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Edits data from a node at the given index of a linked list.
 * 
 * @param list  linked list to edit
 * @param data  new data
 * @param idx   index of the node to edit
 * 
 * @return 
 *  1 : edit successful @n
 *  0 : invalid index @n
 */
int list_edit_at(LINKED_LIST_T *list, void *data, int idx);

/**
 * @brief 
 *  Gets the pointer to data stored in the linked list by the given index.
 * 
 * @param list  linked list cointaing the data
 * @param idx   index to get data from
 * 
 * @return Pointer to the data, NULL if data is not found or the index is invalid.
 */
void* list_data_at(LINKED_LIST_T *list, int idx);

/**
 * @brief 
 *  Gets the first instance of matching data in a linked list using a given key 
 *  and compare function in a linked list.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't. @n
 *  Compare function input No. : @n 
 *  1) data from the linked list @n 
 *  2) key @n 
 * 
 * @param list          linked list to search
 * @param key           key to compare the data with
 * @param comp_func     function to compare data and key
 * 
 * @return Pointer to the data, NULL if data is not found
 */
void* list_data(LINKED_LIST_T *list, const void *key, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Gets all the data using a given key and compare function in a linked list, 
 *  and stores it in a dynamic array.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't. @n
 *  Compare function input No. : @n 
 *  1) data from the linked list @n 
 *  2) key @n 
 *  Highly advised to free the dynamic array after use. @n
 * 
 * @param list          linked list to search
 * @param key           key to compare the data with
 * @param data_arr      dynamic array to store the data
 * @param comp_func     function to compare data and key
 * 
 * @return Number of data chunks, -1 if memory allocation failed.
 */
int list_all_data(LINKED_LIST_T *list, const void *key, void ***data_arr, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Gets the index of the first node in a linked list containing data matching a given key. 
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't. @n
 *  Compare function input No. : @n 
 *  1) data from the linked list @n 
 *  2) key @n 
 * 
 * @param list          linked list to search
 * @param key           key to compare the data with
 * @param comp_func     function to compare data and key
 * 
 * @return Index of node conatining the data, -1 if node with the given data doesn't exist.
 */
int list_find_idx(LINKED_LIST_T *list, const void *key, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Gets all the indices of nodes in a linked list with data matching a given key, 
 *  and stores it in a dynamic array.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't. @n
 *  Compare function input No. : @n 
 *  1) data from the linked list @n 
 *  2) key @n 
 *  Highly advised to free the dynamic array after use.
 * 
 * @param list          linked list to search
 * @param key           key to compare the data with
 * @param idx_arr       dynamic array to store the indicies
 * @param comp_func     function to compare data and key
 * 
 * @return Number of indices, -1 if memory allocation failed.
 */
int list_find_all_idx(LINKED_LIST_T *list, const void *key, int **idx_arr, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Traverses through a linked list head to tail and preforms a given function on all its data.
 * 
 * @param list  linked list to traverse
 * @param func  function to preform on data
 */
void list_traverse(LINKED_LIST_T *list, void (*func)(void*));

/**
 * @brief 
 *  Copies data from a linked list to an array.
 * 
 * @note
 *  Only works if all data (not the data pointers) in the linked list have uniform size.
 * 
 * @param list          linked list to copy from
 * @param arr           array to store copied data
 * @param len           array length
 * @param item_size     array element size
 */
void list_to_arr(LINKED_LIST_T *list, void *arr, int len, size_t item_size);

/**
 * @brief 
 *  Copies the pointers to data from a linked list to an array.
 * 
 * @param list  linked list to copy from
 * @param arr   array to store copied pointers
 * @param len   array length
 */
void list_to_pointer_arr(LINKED_LIST_T *list, void **arr, int len);
#endif