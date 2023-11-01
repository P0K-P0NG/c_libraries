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
    struct bin_tree_node* left;     // left child, less "value", 
    struct bin_tree_node* right;    // right child, greater "value"
} BIN_TREE_NODE_T;

typedef struct  // binary tree
{
    BIN_TREE_NODE_T* root;  // root of the tree
} BIN_TREE_T;

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
BIN_TREE_T* bin_tree_create();

/**
 * @brief 
 *  Deletes a binary tree.
 * 
 * @param tree          binary tree to delete
 * @param free_data     function to free the data, NULL if not needed
 */
void bin_tree_clear(BIN_TREE_T* tree, void (*free_data)(void*));

/**
 * @brief 
 *  Executes a given function on all the data in in-order traversal.
 * 
 * @param tree  binary tree to execute on
 * @param func  function to execute on the data
 */
void bin_tree_in_order(BIN_TREE_T* tree, void (*func)(void*));

/**
 * @brief 
 *  Executes a given function on all the data in pre-order traversal.
 * 
 * @param tree  binary tree to execute on
 * @param func  function to execute on the data
 */
void bin_tree_pre_order(BIN_TREE_T* tree, void (*func)(void*));

/**
 * @brief 
 *  Executes a given function on all the data in post-order traversal.
 * 
 * @param tree  binary tree to execute on
 * @param func  function to execute on the data
 */
void bin_tree_post_order(BIN_TREE_T* tree, void (*func)(void*));

/**
 * @brief 
 *  Adds a new node to a binary tree.
 * 
 * @note 
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if data_1 should come before data_2 @n
 *  2) Returns int >= 0 if data_1 should come after data_2 @n 
 * 
 * @param tree          tree to add to
 * @param data          data of the now node
 * @param comp_func     function to compare the data
 * 
 * @return 
 *   2 : data has repeats @n
 *   1 : new unique node added @n
 *   0 : unable to allocate memory @n
 */
int bin_tree_add(BIN_TREE_T* tree, void *data, int (*comp_func)(const void*, const void*));

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
 * @param tree          binary tree to search
 * @param key           key to indentify data with
 * @param comp_func     function to compare key and data
 * 
 * @return Pointer to the matching data, NULL if not found.
 */
void* bin_tree_find(BIN_TREE_T* tree, void *key, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Finds the number of nodes in a binary tree
 * 
 * @param tree  binary tree to count
 * 
 * @return The number of nodes in the tree.
 */
int bin_tree_count(BIN_TREE_T* tree);
#endif