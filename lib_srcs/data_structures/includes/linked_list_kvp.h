/**
 * @file linked_list_kvp.h
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

struct LListKVPNode {          // node in a key-value pair linked list
    void *key;                 // key to identify the node with
    void *data;                // pointer to data
    struct LListKVPNode *next; // next node in key-value pair linked list
};

struct LListKVP {
    struct LListKVPNode *head; // head node
    struct LListKVPNode *tail; // tail node
    int count;
};

/**
 * @brief
 *  Makes a new empty key-value pair linked list.
 *
 * @return Pointer to new key-value pair linked list, NULL if memory allocation
 * is unsuccessful.
 */
extern struct LListKVP *LListKVPCreate();

/**
 * @brief
 *  Deletes a key-value pair linked list and it's data if a function for freeing
 *  it is given.
 *
 * @param list          key-value pair linked list to delete
 * @param free_key      function to free keys, NULL if not needed
 * @param free_data     function to free data, NULL if not needed
 */
extern void LListKVPClear(struct LListKVP **list, void (*free_key)(void *),
                          void (*free_data)(void *));

/**
 * @brief
 *  Deletes the first node in a key-value pair linked list and it's data if a
 *  function for freeing it is given.
 *
 * @param list          key-value pair linked list to remove from
 * @param free_key      function to free keys, NULL if not needed
 * @param free_data     function to free data, NULL if not needed
 *
 * @return
 *  1 : removal successful @n
 *  0 : key-value pair linked list is empty @n
 */
extern int LListKVPRemoveHead(struct LListKVP *list, void (*free_key)(void *),
                              void (*free_data)(void *));

/**
 * @brief
 *  Deletes a node in a key-value pair linked list with the matching key.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't.
 *
 * @param list          key-value pair linked list to remove from
 * @param key           key of the node to delete
 * @param comp_key      function to compare keys with
 * @param free_key      function to free keys, NULL if not needed
 * @param free_data     function to free data, NULL if not needed
 *
 * @return Pointer the data of the removed node, NULL if not found.
 */
extern void *LListKVPRemove(struct LListKVP *list, void *key,
                            int (*comp_key)(const void *, const void *),
                            void (*free_key)(void *));

/**
 * @brief
 *  Deletes all nodes of key-value pair linked list (but not the list itself)
 *  and it's keys and data if a function for freeing it is given.
 *
 * @param list          key-value pair linked list to remove from
 * @param free_key      function to free keys, NULL if not needed
 * @param free_data     function to free data, NULL if not needed
 */
extern void LListKVPRemoveAll(struct LListKVP *list, void (*free_key)(void *),
                              void (*free_data)(void *));

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
extern int LListKVPAddHead(struct LListKVP *list, void *key, void *data);

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
extern int LListKVPAddTail(struct LListKVP *list, void *key, void *data);

/**
 * @brief
 *  Adds a node to a key-value pair linked list at the position determined by
 *  the compare funtion.
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
extern int LListKVPAdd(struct LListKVP *list, void *key, void *data,
                       int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Gets the data of first instance of a matching key in a key-value pair linked
 *  list.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't.
 *
 * @param list          key-value pair linked list to search
 * @param key           key of the data to find
 * @param comp_key      function to compare the keys
 *
 * @return Pointer to the data, NULL if data is not found
 */
extern void *LListKVPFind(struct LListKVP *list, const void *key,
                          int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Gets all the data with the matching key in a key-value pair linked list,
 *  and stores it in a dynamic array.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't.
 *
 * @param list          key-value pair linked list to search
 * @param key           key of the data to find
 * @param data_arr      dynamic array to store the data
 * @param comp_key      function to compare the keys
 *
 * @return Number of data chunks, -1 if memory allocation failed.
 */
extern int LListKVPFindAll(struct LListKVP *list, const void *key,
                           void ***data_arr,
                           int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Counts the number of times a given key is matched in a key-value pair linked
 *  list.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't.
 *
 * @param list          key-value pair linked list to search
 * @param key           key to match
 * @param comp_key      function to compare the keys
 *
 * @return The numebr of times the provided key is matched.
 */
extern int LListKVPCountRepeats(struct LListKVP *list, const void *key,
                                int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Traverses through a key-value pair linked list head to tail and preforms a
 *  given function on all its data.
 *
 * @param list  key-value pair linked list to traverse
 * @param func  function to preform on key and data, in this order
 */
extern void LListKVPTraverse(struct LListKVP *list,
                             void (*func)(void *, void *));

/**
 * @brief
 *  Copies data from a key-value pair linked list to an array.
 *
 * @note
 *  Only works if all data (not the data pointers) in the key-value pair linked
 *  list have uniform size.
 *
 * @param list          key-value pair linked list to copy from
 * @param arr           array to store copied data
 * @param len           array length
 * @param item_size     array element size
 */
extern void LListKVPToArr(struct LListKVP *list, void *arr, int len,
                          size_t item_size);

/**
 * @brief
 *  Copies the pointers to data from a key-value pair linked list to an array.
 *
 * @param list  key-value pair linked list to copy from
 * @param arr   array to store copied pointers
 * @param len   array length
 */
extern void LListKVPToPointerArr(struct LListKVP *list, void **arr, int len);
#endif