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

#include <stdbool.h>
#include <stddef.h>

struct LListNode {          // node in a linked list
    void *data;             // pointer to data
    struct LListNode *next; // next node in linked list
};

struct LList {
    struct LListNode *head; // head node
    struct LListNode *tail; // tail node
    int count;
};

/**
 * @brief
 *  Makes a new empty linked list.
 *
 * @return Pointer to new linked list, NULL if memory allocation is
 * unsuccessful.
 */
extern struct LList *LListCreate();

/**
 * @brief
 *  Deletes a linked list and it's data if a function for freeing it is given.
 *
 * @param[in,out] p_list        inked list to delete
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void LListClear(struct LList **p_list, void (*free_data)(void *));

/**
 * @brief
 *  Deletes the first node in a linked list and it's data if a function for
 *  freeing it is given.
 *
 * @param[in,out] list          linked list to remove from
 * @param[in]     free_data     function to free data, NULL if not needed
 *
 * @return
 *  true  : removal successful @n
 *  false : linked list is empty @n
 */
extern bool LListRemoveHead(struct LList *list, void (*free_data)(void *));

/**
 * @brief
 *  Deletes a node at the given index of a linked list and it's data
 *  if a function for freeing it is given.
 *
 * @param[in,out] list          linked list to remove from
 * @param[in]     idx           index of the node to delete
 * @param[in]     free_data     function to free data, NULL if not needed
 *
 * @return
 *  true  : removal successful @n
 *  false : invalid index @n
 */
extern bool LListRemoveAt(struct LList *list, size_t idx,
                          void (*free_data)(void *));

/**
 * @brief
 *  Deletes all nodes of linked list (but not the list itself) and it's data
 *  if a function for freeing it is given.
 *
 * @param[in,out] list          linked list to remove from
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void LListRemoveAll(struct LList *list, void (*free_data)(void *));

/**
 * @brief
 *  Adds a node to start of a linked list.
 *
 * @param[in,out] list  linked list add to
 * @param[in]     data  data of the new node
 *
 * @return
 *  true  : node added successfully @n
 *  false : memory allocation falied @n
 */
extern bool LListAddHead(struct LList *list, void *data);

/**
 * @brief
 *  Adds a node to end of a linked list.
 *
 * @param[in,out] list  linked list add to
 * @param[in]     data  data of the new node
 *
 * @return
 *  true  : node added successfully @n
 *  false : memory allocation falied @n
 */
extern bool LListAddTail(struct LList *list, void *data);

/**
 * @brief
 *  Adds a node at the given index of a linked list.
 *
 * @param[in,out] list  linked list to add to
 * @param[in]     data  data of the new node
 * @param[in]     idx   index of the new node
 *
 * @return
 *   1 : node added successfully @n
 *   0 : memory allocation falied @n
 *  -1 : invalid index @n
 */
extern int LListAddAt(struct LList *list, void *data, size_t idx);

/**
 * @brief
 *  Adds a node to a linked list at the position determined by the compare
 * funtion.
 *
 * @note
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if data_1 should come before data_2 @n
 *  2) Returns int >= 0 if data_1 should come after data_2 @n
 *
 * @param[in,out] list          linked list to add to
 * @param[in]     data          data of the new node
 * @param[in]     comp_func     function to compare data with
 *
 * @return
 *  true  : added successfully @n
 *  false : memory allocation falied @n
 */
extern bool LListAddByCompare(struct LList *list, void *data,
                              int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Edits data from a node at the given index of a linked list.
 *
 * @param[in,out] list  linked list to edit
 * @param[in]     data  new data
 * @param[in]     idx   index of the node to edit
 *
 * @return
 *  true  : edit successful @n
 *  false : invalid index @n
 */
extern bool LListEditAt(struct LList *list, void *data, size_t idx);

/**
 * @brief
 *  Gets the pointer to data stored in the linked list by the given index.
 *
 * @param[in] list  linked list cointaing the data
 * @param[in] idx   index to get data from
 *
 * @return Pointer to the data, NULL if data is not found or the index is
 * invalid.
 */
extern void *LListDataAt(struct LList *list, size_t idx);

/**
 * @brief
 *  Gets the first instance of matching data in a linked list using a given key
 *  and compare function in a linked list.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't. @n
 *  Compare function input No. : @n
 *  1) data from the linked list @n
 *  2) key @n
 *
 * @param[in] list          linked list to search
 * @param[in] key           key to compare the data with
 * @param[in] comp_func     function to compare data and key
 *
 * @return Pointer to the data, NULL if data is not found
 */
extern void *LListData(struct LList *list, const void *key,
                       int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Gets all the data using a given key and compare function in a linked list,
 *  and stores it in a dynamic array.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't. @n
 *  Compare function input No. : @n
 *  1) data from the linked list @n
 *  2) key @n
 *  Highly advised to free the dynamic array after use. @n
 *
 * @param[in]  list         linked list to search
 * @param[in]  key          key to compare the data with
 * @param[out] ptr_arr      dynamic array to store the data
 * @param[out] count        number of found data
 * @param[in]  comp_func    function to compare data and key
 *
 * @return
 *  true  : execution successful @n
 *  false : memory allocation failed @n
 */
extern bool LListAllData(struct LList *list, const void *key, void ***ptr_arr,
                         size_t *count,
                         int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Gets the index of the first node in a linked list containing data matching a
 * given key.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't. @n
 *  Compare function input No. : @n
 *  1) data from the linked list @n
 *  2) key @n
 *
 * @param[in]  list         linked list to search
 * @param[in]  key          key to compare the data with
 * @param[out] idx          variable to store index found
 * @param[in]  comp_func    function to compare data and key
 *
 * @return Index of node conatining the data, -1 if node with the given data
 * doesn't exist.
 */
extern bool LListFindIdx(struct LList *list, const void *key, size_t *idx,
                         int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Gets all the indices of nodes in a linked list with data matching a given
 * key, and stores it in a dynamic array.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't. @n
 *  Compare function input No. : @n
 *  1) data from the linked list @n
 *  2) key @n
 *  Highly advised to free the dynamic array after use.
 *
 * @param[in]  list         linked list to search
 * @param[in]  key          key to compare the data with
 * @param[out] idx_arr      dynamic array to store the indicies
 * @param[out] count        number of found indices
 * @param[in]  comp_func    function to compare data and key
 *
 * @return Number of indices, -1 if memory allocation failed.
 */
extern bool LListFindAllIdx(struct LList *list, const void *key, int **idx_arr,
                            size_t *count,
                            int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Traverses through a linked list head to tail and preforms a given function
 * on all its data.
 *
 * @param[in,out] list  linked list to traverse
 * @param[in]     func  function to preform on data
 */
extern void LListTraverse(struct LList *list, void (*func)(void *));

/**
 * @brief
 *  Copies data from a linked list to an array.
 *
 * @note
 *  Only works if all data (not the data pointers) in the linked list have
 * uniform size.
 *
 * @param[in]  list         linked list to copy from
 * @param[out] arr          array to store copied data
 * @param[in]  len          array length
 * @param[in]  item_size    array element size
 */
extern void LListToArr(struct LList *list, void *arr, size_t len,
                       size_t item_size);

/**
 * @brief
 *  Copies the pointers to data from a linked list to an array.
 *
 * @param[in]  list     linked list to copy from
 * @param[out] arr      array to store copied pointers
 * @param[in]  len      array length
 */
extern void LListToPointerArr(struct LList *list, void **arr, size_t len);
#endif