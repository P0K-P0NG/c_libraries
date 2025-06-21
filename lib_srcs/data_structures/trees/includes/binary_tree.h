/**
 * @file binary_tree.h
 *
 * @brief
 *  Structs and functions for binary tree structures
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-04-23
 */
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stddef.h>

typedef struct BinTreeNode { // node of a binary tree structure
    void *data;      // pointer to data
    int count;
    struct BinTreeNode *left;  // left child, less "value",
    struct BinTreeNode *right; // right child, greater "value"
} BinTreeNode_t;

typedef struct BinTree {              // binary tree
    BinTreeNode_t *root; // root of the tree
} BinTree_t;

/**
 * @brief
 *  Creates a binary tree.
 *
 * @note
 *  When using this module for binary trees, it is highly advised to use
 *  this function to initailize a new binary tree. Doing otherwise may
 *  result in unexpected behavior.
 *
 * @return Pointer to the new binary tree, NULL if unable to allocate memory.
 */
extern BinTree_t *BinTreeCreate();

/**
 * @brief
 *  Deletes a binary tree.
 *
 * @param[in,out] p_tree        binary tree to delete
 * @param[in]     free_data     function to free the data, NULL if not needed
 */
extern void BinTreeClear(BinTree_t **p_tree, void (*free_data)(void *));

/**
 * @brief
 *  Executes a given function on all the data in in-order traversal.
 *
 * @param[in,out] tree  binary tree to execute on
 * @param[in]     func  function to execute on the data
 */
extern void BinTreeInOrder(BinTree_t *tree, void (*func)(void *));

/**
 * @brief
 *  Executes a given function on all the data in pre-order traversal.
 *
 * @param[in,out] tree  binary tree to execute on
 * @param[in]     func  function to execute on the data
 */
extern void BinTreePreOrder(BinTree_t *tree, void (*func)(void *));

/**
 * @brief
 *  Executes a given function on all the data in post-order traversal.
 *
 * @param[in,out] tree  binary tree to execute on
 * @param[in]     func  function to execute on the data
 */
extern void BinTreePostOrder(BinTree_t *tree, void (*func)(void *));

/**
 * @brief
 *  Adds a new node to a binary tree.
 *
 * @note
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if data_1 should come before data_2 @n
 *  2) Returns int >= 0 if data_1 should come after data_2 @n
 *
 * @param[in,out] tree          tree to add to
 * @param[in]     data          data of the now node
 * @param[in]     comp_func     function to compare the data
 *
 * @return
 *   2 : data has repeats @n
 *   1 : new unique node added @n
 *   0 : unable to allocate memory @n
 */
extern int BinTreeAdd(BinTree_t *tree, void *data,
                      int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Finds data in a binary tree using a key and a function to compare
 *  the key with data in the tree.
 *
 * @note
 *  Compare function input No. : @n
 *  1) data from the linked list @n
 *  2) key @n
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if data_1 should come before data_2 @n
 *  2) Returns int >= 0 if data_1 should come after data_2 @n
 *
 * @param[in] tree          binary tree to search
 * @param[in] key           key to indentify data with
 * @param[in] comp_func     function to compare key and data
 *
 * @return Pointer to the matching data, NULL if not found.
 */
extern void *BinTreeFind(BinTree_t *tree, void *key,
                         int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Finds the number of nodes in a binary tree
 *
 * @param[in] tree  binary tree to count
 *
 * @return The number of nodes in the tree.
 */
extern size_t BinTreeCount(BinTree_t *tree);
#endif