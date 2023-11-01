/**
 * @file key-value_linked_list.h
 * 
 * @brief 
 *  Structs and functions for key-value pair linked lists.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#ifndef KEY_VALUE_LINKED_LIST_H
#define KEY_VALUE_LINKED_LIST_H

#include <stddef.h>

typedef struct key_value_pair_node // node in a key-value pair linked list
{
    void *key;                          // key to identify the node with
    void *data;                         // pointer to data
    struct key_value_pair_node *next;   // next node in key-value pair linked list
} KVP_NODE_T;

typedef struct key_value_pair_linked_list
{
    KVP_NODE_T *head;   // head node
    KVP_NODE_T *tail;   // tail node
    int count;
} KVP_LIST_T;

/**
 * @brief 
 *  Makes a new empty key-value pair linked list.
 * 
 * @return Pointer to new key-value pair linked list, NULL if memory allocation is unsuccessful.
 */
KVP_LIST_T* kvp_list_create();

/**
 * @brief 
 *  Deletes a key-value pair linked list and it's data if a function for freeing it is given.
 * 
 * @param list          key-value pair linked list to delete
 * @param free_key      function to free keys, NULL if not needed
 * @param free_data     function to free data, NULL if not needed
 */
void kvp_list_clear(KVP_LIST_T *list, void (*free_key)(void*), void (*free_data)(void*));

/**
 * @brief 
 *  Deletes the first node in a key-value pair linked list and it's data if a function for freeing it is given.
 * 
 * @param list          key-value pair linked list to remove from
 * @param free_key      function to free keys, NULL if not needed
 * @param free_data     function to free data, NULL if not needed
 * 
 * @return 
 *  1 : removal successful @n
 *  0 : key-value pair linked list is empty @n
 */
int kvp_list_remove_head(KVP_LIST_T *list, void (*free_key)(void*), void (*free_data)(void*));

/**
 * @brief 
 *  Deletes a node in a key-value pair linked list with the matching key.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't.
 * 
 * @param list          key-value pair linked list to remove from
 * @param key           key of the node to delete
 * @param comp_key      function to compare keys with
 * @param free_key      function to free keys, NULL if not needed
 * @param free_data     function to free data, NULL if not needed
 * 
 * @return Pointer the data of the removed node, NULL if not found.
 */
void* kvp_list_remove(KVP_LIST_T *list, void *key,  int (*comp_key)(const void*, const void*), void (*free_key)(void*));

/**
 * @brief 
 *  Deletes all nodes of key-value pair linked list (but not the list itself) 
 *  and it's keys and data if a function for freeing it is given.
 * 
 * @param list          key-value pair linked list to remove from
 * @param free_key      function to free keys, NULL if not needed
 * @param free_data     function to free data, NULL if not needed
 */
void kvp_list_remove_all(KVP_LIST_T *list, void (*free_key)(void*), void (*free_data)(void*));

/**
 * @brief 
 *  Adds a node to start of a key-value pair linked list.
 * 
 * @param list  key-value pair linked list add to
 * @param key   key of the new node
 * @param data  data of the new node
 * 
 * @return 
 *  1 : node added successfully @n
 *  0 : memory allocation falied @n
 */
int kvp_list_add_head(KVP_LIST_T *list, void *key, void *data);

/**
 * @brief 
 *  Adds a node to end of a key-value pair linked list.
 * 
 * @param list  key-value pair linked list add to
 * @param key   key of the new node
 * @param data  data of the new node
 * 
 * @return 
 *  1 : node added successfully @n
 *  0 : memory allocation falied @n
 */
int kvp_list_add_tail(KVP_LIST_T *list, void *key, void *data);

/**
 * @brief 
 *  Adds a node to a key-value pair linked list at the position determined by the compare funtion.
 * 
 * @note 
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if key_1 should come before key_2 @n
 *  2) Returns int >= 0 if key_1 should come after key_2 @n
 * 
 * @param list      key-value pair linked list to add to
 * @param key       key of the new node
 * @param data      data of the new node
 * @param comp_key  function to compare keys with
 * 
 * @return 
 *  1 : added successfully @n
 *  0 : memory allocation falied @n
 */
int kvp_list_add(KVP_LIST_T *list, void *key, void *data, int (*comp_key)(const void*, const void*));

/**
 * @brief 
 *  Gets the data of first instance of a matching key in a key-value pair linked listt.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't.
 * 
 * @param list          key-value pair linked list to search
 * @param key           key of the data to find
 * @param comp_key      function to compare the keys
 * 
 * @return Pointer to the data, NULL if data is not found
 */
void* kvp_list_find(KVP_LIST_T *list, const void *key, int (*comp_key)(const void*, const void*));

/**
 * @brief 
 *  Gets all the data with the matching key in a key-value pair linked list, 
 *  and stores it in a dynamic array.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't.
 * 
 * @param list          key-value pair linked list to search
 * @param key           key of the data to find
 * @param data_arr      dynamic array to store the data
 * @param comp_key      function to compare the keys
 * 
 * @return Number of data chunks, -1 if memory allocation failed.
 */
int kvp_list_find_all(KVP_LIST_T *list, const void *key, void ***data_arr, int (*comp_key)(const void*, const void*));

/**
 * @brief 
 *  Counts the number of times a given key is matched in a key-value pair linked list.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't.
 * 
 * @param list          key-value pair linked list to search
 * @param key           key to match
 * @param comp_key      function to compare the keys
 * 
 * @return The numebr of times the provided key is matched.
 */
int kvp_list_count_repeats(KVP_LIST_T *list, const void *key, int (*comp_key)(const void*, const void*));

/**
 * @brief 
 *  Traverses through a key-value pair linked list head to tail and preforms a given function on all its data.
 * 
 * @param list  key-value pair linked list to traverse
 * @param func  function to preform on key and data, in this order
 */
void kvp_list_traverse(KVP_LIST_T *list, void (*func)(void*, void*));

/**
 * @brief 
 *  Copies data from a key-value pair linked list to an array.
 * 
 * @note
 *  Only works if all data (not the data pointers) in the key-value pair linked list have uniform size.
 * 
 * @param list          key-value pair linked list to copy from
 * @param arr           array to store copied data
 * @param len           array length
 * @param item_size     array element size
 */
void kvp_list_to_arr(KVP_LIST_T *list, void *arr, int len, size_t item_size);

/**
 * @brief 
 *  Copies the pointers to data from a key-value pair linked list to an array.
 * 
 * @param list  key-value pair linked list to copy from
 * @param arr   array to store copied pointers
 * @param len   array length
 */
void kvp_list_to_pointer_arr(KVP_LIST_T *list, void **arr, int len);
#endif