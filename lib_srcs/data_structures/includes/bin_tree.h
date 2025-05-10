/**
 * @file bin_tree.h
 * 
 * @brief 
 *  Structs and functions for binary tree structures
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-04-23
 */
#ifndef BIN_TREE_H
#define BIN_TREE_H

typedef struct bin_tree_node // node of a binary tree structure
{
    void *data; // pointer to data
    int count;
    struct bin_tree_node *left;     // left child, less "value", 
    struct bin_tree_node *right;    // right child, greater "value"
} BinTreeNode;

typedef struct  // binary tree
{
    BinTreeNode *root;  // root of the tree
} BinTree;

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
extern BinTree *BinTreeCreate();

/**
 * @brief 
 *  Deletes a binary tree.
 * 
 * @param[in, out] tree          binary tree to delete
 * @param[in]      free_data     function to free the data, NULL if not needed
 */
extern void BinTreeClear(BinTree **tree, void (*free_data)(void*));

/**
 * @brief 
 *  Executes a given function on all the data in in-order traversal.
 * 
 * @param[in, out] tree  binary tree to execute on
 * @param[in]      func  function to execute on the data
 */
extern void BinTreeInOrder(BinTree *tree, void (*func)(void*));

/**
 * @brief 
 *  Executes a given function on all the data in pre-order traversal.
 * 
 * @param[in, out] tree  binary tree to execute on
 * @param[in]      func  function to execute on the data
 */
extern void BinTreePreOrder(BinTree *tree, void (*func)(void*));

/**
 * @brief 
 *  Executes a given function on all the data in post-order traversal.
 * 
 * @param[in, out] tree  binary tree to execute on
 * @param[in]      func  function to execute on the data
 */
extern void BinTreePostOrder(BinTree *tree, void (*func)(void*));

/**
 * @brief 
 *  Adds a new node to a binary tree.
 * 
 * @note 
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if data_1 should come before data_2 @n
 *  2) Returns int >= 0 if data_1 should come after data_2 @n 
 * 
 * @param[in, out] tree          tree to add to
 * @param[in]      data          data of the now node
 * @param[in]      comp_func     function to compare the data
 * 
 * @return 
 *   2 : data has repeats @n
 *   1 : new unique node added @n
 *   0 : unable to allocate memory @n
 */
extern int BinTreeAdd(BinTree *tree, void *data, int (*comp_func)(const void*, const void*));

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
 * @param[in, out] tree          binary tree to search
 * @param[in]      key           key to indentify data with
 * @param[in]      comp_func     function to compare key and data
 * 
 * @return Pointer to the matching data, NULL if not found.
 */
extern void *BinTreeFind(BinTree *tree, void *key, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Finds the number of nodes in a binary tree
 * 
 * @param[in, out] tree  binary tree to count
 * 
 * @return The number of nodes in the tree.
 */
extern int BinTreeCount(BinTree *tree);
#endif