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

typedef struct DLListNode {          // node in a doubly linked list
    void *data;              // pointer to data
    struct DLListNode *next; // next node in doubly linked list
    struct DLListNode *prev; // next node in doubly linked list
} DLListNode_t;

typedef struct DLList {
    struct DLListNode *head; // head node
    struct DLListNode *tail; // tail node
    size_t count;
} DLList_t;

/**
 * @brief
 *  Makes a new empty doubly linked list.
 *
 * @return Pointer to new doubly linked list, NULL if memory allocation is
 * unsuccessful.
 */
extern DLList_t *DLListCreate();

/**
 * @brief
 *  Deletes a doubly linked list and it's data if a function for freeing it is
 *  given.
 *
 * @param[in,out] p_list        doubly linked list to delete
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void DLListClear(DLList_t **p_list, void (*free_data)(void *));

/**
 * @brief
 *  Deletes a given node in a doubly linked list and it's data
 *  if a function for freeing it is given.
 *
 * @param[in,out] list          doubly linked list to remove from
 * @param[in]     node          pointer to the node to delete
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void DLListRemove(DLList_t *list, DLListNode_t *node,
                         void (*free_data)(void *));

/**
 * @brief
 *  Deletes all nodes of doubly linked list (but not the list itself) and it's
 *  data if a function for freeing it is given.
 *
 * @param[in,out] list          doubly linked list to remove from
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void DLListRemoveAll(DLList_t *list, void (*free_data)(void *));

/**
 * @brief
 *  Adds a node to start of a doubly linked list.
 *
 * @param[in,out] list  doubly linked list to add to
 * @param[in]     data  data of the new node
 *
 * @return Pointer to the new node, NULL if memory allocation failed.
 */
extern DLListNode_t *DLListAddHead(DLList_t *list, void *data);

/**
 * @brief
 *  Adds a node to end of a doubly linked list.
 *
 * @param[in,out] list  doubly linked list to add to
 * @param[in]     data  data of the new node
 *
 * @return Pointer to the new node, NULL if memory allocation failed.
 */
extern DLListNode_t *DLListAddTail(DLList_t *list, void *data);

/**
 * @brief
 *  Adds a node at the postion of an already existing node in a doubly linked
 *  list. And pushes the old node back.
 *
 * @param[in,out] list          doubly linked list to add to
 * @param[in,out] curr_node     current node at the postion to add to; NULL to
 *                              add as new tail
 * @param[in]     data          data of the new node
 *
 * @return Pointer to the new node, NULL if memory allocation failed.
 */
extern DLListNode_t *DLListAddAt(DLList_t *list,
                                      DLListNode_t *curr_node, void *data);

/**
 * @brief
 *  Adds a node to a doubly linked list at the position determined by the
 *  compare funtion.
 *
 * @note
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if data_1 should come before data_2 @n
 *  2) Returns int >= 0 if data_1 should come after data_2 @n
 *
 * @param[in,out] list          doubly linked list to add to
 * @param[in]     data          data of the new node
 * @param[in]     comp_func     function to compare data with
 *
 * @return Pointer to the new node, NULL if memory allocation failed.
 */
extern DLListNode_t *DLListAddByCompare(DLList_t *list, void *data,
                                             int (*comp_func)(const void *,
                                                              const void *));

/**
 * @brief
 *  Gets the node at the given index in a doubly linked list.
 *
 * @param[in] list  doubly linked list cointaing the node
 * @param[in] idx   index to get data from
 *
 * @return Pointer to the node, NULL if node is not found or the index is
 * invalid.
 */
extern DLListNode_t *DLListAt(DLList_t *list, size_t idx);

/**
 * @brief
 *  Gets the first node with matching data in a doubly linked list using a given
 *  key and compare function in a doubly linked list.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't. @n
 *  Compare function input No. : @n
 *  1) data from the doubly linked list @n
 *  2) key @n
 *
 * @param[in] list          doubly linked list to search
 * @param[in] key           key to compare the data with
 * @param[in] comp_func     function to compare data and key
 *
 * @return Pointer to the data, NULL if data is not found
 */
extern DLListNode_t *DLListFind(DLList_t *list, const void *key,
                                     int (*comp_func)(const void *,
                                                      const void *));

/**
 * @brief
 *  Traverses through a doubly linked list head to tail and preforms a given
 *  function on all its data.
 *
 * @param[in,out] list  doubly linked list to traverse
 * @param[in]     func  function to preform on data
 */
extern void DLListTraverse(DLList_t *list, void (*func)(void *));
#endif