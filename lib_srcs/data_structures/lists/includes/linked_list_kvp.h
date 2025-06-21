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
#ifndef LINKED_LIST_KVP_H
#define LINKED_LIST_KVP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct LListKVPNode {          // node in a key-value pair linked list
    void *key;                 // key to identify the node with
    void *data;                // pointer to data
    struct LListKVPNode *next; // next node in key-value pair linked list
} LListKVPNode_t;

typedef struct LListKVP {
    LListKVPNode_t *head; // head node
    LListKVPNode_t *tail; // tail node
    size_t count;
    /**
     *  The compare function must operate as follows: @n
     *  1) Returns int < 0 if key_1 should come before key_2 @n
     *  2) Returns int >= 0 if key_1 should come after key_2 @n
     */
    int (*comp_key)(const void *, const void *);
} LListKVP_t;

/**
 * @brief
 *  Makes a new empty key-value pair linked list.
 *
 * @note
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if key_1 should come before key_2 @n
 *  2) Returns int >= 0 if key_1 should come after key_2 @n
 *
 * @param[in] comp_key  function to compare the keys
 *
 * @return Pointer to new key-value pair linked list, NULL if memory allocation
 * is unsuccessful.
 */
extern LListKVP_t *LListKVPCreate(int (*comp_key)(const void *,
                                                       const void *));

/**
 * @brief
 *  Deletes a key-value pair linked list and it's data if a function for
 * freeing it is given.
 *
 * @param[in,out] p_list        key-value pair linked list to delete
 * @param[in]     free_key      function to free keys, NULL if not needed
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void LListKVPClear(LListKVP_t **p_list, void (*free_key)(void *),
                          void (*free_data)(void *));

/**
 * @brief
 *  Deletes the first node in a key-value pair linked list and it's data if
 * a function for freeing it is given.
 *
 * @param[in,out] list          key-value pair linked list to remove from
 * @param[in]     free_key      function to free keys, NULL if not needed
 * @param[in]     free_data     function to free data, NULL if not needed
 *
 * @return true  : removal successful 
 * @return false : list is empty
 */
extern bool LListKVPRemoveHead(LListKVP_t *list, void (*free_key)(void *),
                               void (*free_data)(void *));

/**
 * @brief
 *  Deletes a node in a key-value pair linked list with the matching key.
 *
 * @param[in,out] list          key-value pair linked list to remove from
 * @param[in]     key           key of the node to delete
 * @param[in]     free_key      function to free keys, NULL if not needed
 * @param[in]     free_data     function to free data, NULL if not needed
 *
 * @return Pointer the data of the removed node, NULL if not found.
 */
extern void *LListKVPRemove(LListKVP_t *list, void *key,
                            void (*free_key)(void *));

/**
 * @brief
 *  Deletes all nodes of key-value pair linked list (but not the list
 *  itself) and it's keys and data if a function for freeing it is given.
 *
 * @param[in,out] list          key-value pair linked list to remove from
 * @param[in]     free_key      function to free keys, NULL if not needed
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void LListKVPRemoveAll(LListKVP_t *list, void (*free_key)(void *),
                              void (*free_data)(void *));

/**
 * @brief
 *  Adds a node to start of a key-value pair linked list.
 *
 * @param[in,out] list  key-value pair linked list add to
 * @param[in]     key   key of the new node
 * @param[in]     data  data of the new node
 *
 * @return true  : node added successfully 
 * @return false : memory allocation falied
 */
extern bool LListKVPAddHead(LListKVP_t *list, void *key, void *data);

/**
 * @brief
 *  Adds a node to end of a key-value pair linked list.
 *
 * @param[in,out] list  key-value pair linked list add to
 * @param[in]     key   key of the new node
 * @param[in]     data  data of the new node
 *
 * @return true  : node added successfully 
 * @return false : memory allocation falied
 */
extern bool LListKVPAddTail(LListKVP_t *list, void *key, void *data);

/**
 * @brief
 *  Adds a node to a key-value pair linked list at the position determined
 *  by the compare funtion.
 *
 * @param[in,out] list  key-value pair linked list to add to
 * @param[in]     key   key of the new node
 * @param[in]     data  data of the new node
 *
 * @return true  : added successfully 
 * @return false : memory allocation falied
 */
extern bool LListKVPAdd(LListKVP_t *list, void *key, void *data);

/**
 * @brief
 *  Gets the data of first instance of a matching key in a key-value pair
 *  linked list.
 *
 * @param[in] list  key-value pair linked list to search
 * @param[in] key   key of the data to find
 *
 * @return Pointer to the data, NULL if data is not found
 */
extern void *LListKVPFind(LListKVP_t *list, const void *key);

/**
 * @brief
 *  Gets all the data with the matching key in a key-value pair linked list,
 *  and stores it in a dynamic array.
 *
 * @param[in]  list         key-value pair linked list to search
 * @param[in]  key          key of the data to find
 * @param[out] ptr_arr      dynamic array to store the data
 * @param[out] count        variable to store the number of pairs found
 *
 * @return true  : execution successful 
 * @return false : memory allocation failed
 */
extern bool LListKVPFindAll(LListKVP_t *list, const void *key,
                            void ***ptr_arr, size_t *count);

/**
 * @brief
 *  Counts the number of times a given key is matched in a key-value pair
 * linked list.
 *
 * @param[in] list  key-value pair linked list to search
 * @param[in] key   key to match
 *
 * @return The numebr of times the provided key is matched.
 */
extern size_t LListKVPCountRepeats(LListKVP_t *list, const void *key);

/**
 * @brief
 *  Traverses through a key-value pair linked list head to tail and preforms
 * a given function on all its data.
 *
 * @param[in,out] list  key-value pair linked list to traverse
 * @param[in]     func  function to preform on key and data, in this order
 */
extern void LListKVPTraverse(LListKVP_t *list,
                             void (*func)(void *, void *));

/**
 * @brief
 *  Copies data from a key-value pair linked list to an array.
 *
 * @note
 *  Only works if all data (not the data pointers) in the key-value pair
 * linked list have uniform size.
 *
 * @param[in]  list         key-value pair linked list to copy from
 * @param[out] arr          array to store copied data
 * @param[in]  len          array length
 * @param[in]  item_size    array element size
 */
extern void LListKVPToArr(LListKVP_t *list, void *arr, size_t len,
                          size_t item_size);

/**
 * @brief
 *  Copies the pointers to data from a key-value pair linked list to an
 * array.
 *
 * @param[in]  list     key-value pair linked list to copy from
 * @param[out] arr      array to store copied pointers
 * @param[in]  len      array length
 */
extern void LListKVPToPointerArr(LListKVP_t *list, void **arr, size_t len);
#endif