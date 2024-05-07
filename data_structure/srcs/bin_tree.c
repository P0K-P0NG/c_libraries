/**
 * @file bin_tree.h
 * 
 * @brief 
 *  Structs and functions for binary tree structures
 * 
 * @implements
 *  bin_tree.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-04-23
 */
#include <stdlib.h>
#include "bin_tree.h"

/**
 * LOCAL FUNTION DECLARATIONS
 *
 * These function aren't defined outside of this source file and are not intended to be acessed directly.
*/
static void clear_rec(BIN_TREE_NODE_T *node, void (*free_data)(void*));
static void in_order_rec(BIN_TREE_NODE_T *node, void (*func)(void*));
static void pre_order_rec(BIN_TREE_NODE_T *node, void (*func)(void*));
static void post_order_rec(BIN_TREE_NODE_T *node, void (*func)(void*));
static int add_rec(BIN_TREE_NODE_T **node, void *data, 
    int (*comp_func)(const void*, const void*));
static void find_rec(BIN_TREE_NODE_T *node, void *key, void **data, 
    int (*comp_func)(const void*, const void*));
static int count_rec(BIN_TREE_NODE_T *node);

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
BIN_TREE_T *bin_tree_create()
{
    return calloc(1, sizeof(BIN_TREE_NODE_T*));
}

/**
 * @brief 
 *  Deletes a binary tree.
 * 
 * @param tree  binary tree to delete
 */
void bin_tree_clear(BIN_TREE_T **tree, void (*free_data)(void*))
{
    clear_rec((*tree)->root, free_data);
    free(*tree);
    *tree = NULL;
}

void clear_rec(BIN_TREE_NODE_T *node, void (*free_data)(void*))
{
    if(node != NULL)
    {
        clear_rec(node->left, free_data);
        clear_rec(node->right, free_data);
        if(free_data != NULL)
        {
            free_data(node->data);
        }
        free(node);
    }
}

/**
 * @brief 
 *  Executes a given function on all the nodes in in-order traversal.
 * 
 * @param tree  binary tree to execute on
 * @param func  function to execute the nodes with
 */
void bin_tree_in_order(BIN_TREE_T *tree, void (*func)(void*))
{
    in_order_rec(tree->root, func);
}

void in_order_rec(BIN_TREE_NODE_T *node, void (*func)(void*))
{
    if(node->left != NULL)
    {
        in_order_rec(node->left, func);
    }
    func(node->data);
    if(node->right != NULL)
    {
        in_order_rec(node->right, func);
    }
}

/**
 * @brief 
 *  Executes a given function on all the nodes in pre-order traversal.
 * 
 * @param tree  binary tree to execute on
 * @param func  function to execute the nodes with
 */
void bin_tree_pre_order(BIN_TREE_T *tree, void (*func)(void*))
{
    pre_order_rec(tree->root, func);
}

static void pre_order_rec(BIN_TREE_NODE_T *node, void (*func)(void*))
{
    func(node->data);
    if(node->left != NULL)
    {
        pre_order_rec(node->left, func);
    }
    if(node->right != NULL)
    {
        pre_order_rec(node->right, func);
    }
}

/**
 * @brief 
 *  Executes a function on all the nodes in post-order traversal.
 * 
 * @param tree  binary tree to execute on
 * @param func  function to execute the nodes with
 */
void bin_tree_post_order(BIN_TREE_T *tree, void (*func)(void*))
{
    post_order_rec(tree->root, func);
}

static void post_order_rec(BIN_TREE_NODE_T *node, void (*func)(void*))
{
    if(node->left != NULL)
    {
        post_order_rec(node->left, func);
    }
    if(node->right != NULL)
    {
        post_order_rec(node->right, func);
    }
    func(node->data);
}

/**
 * @brief 
 *  Adds a new node to a binary tree.
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
int bin_tree_add(
    BIN_TREE_T *tree, 
    void *data, 
    int (*comp_func)(const void*, const void*))
{
    return add_rec(&(tree->root), data, comp_func);
}

static int add_rec(
    BIN_TREE_NODE_T **node, 
    void *data, 
    int (*comp_func)(const void*, const void*))
{
    int status = 0;
    if(*node != NULL)
    {
        int result = comp_func((*node)->data, data);
        if(result > 0)
        {
            status = add_rec(&((*node)->left), data, comp_func);
        }
        else if(result < 0)
        {
            status = add_rec(&((*node)->right), data, comp_func);
        }
        else
        {
            status = 2;
            (*node)->count += 1;
        }
    }
    else
    {
        if((*node = calloc(1, sizeof(BIN_TREE_NODE_T))) != NULL)
        {
            status = 1;
            (*node)->data = data;
        }
    }
    return status;
}


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
void *bin_tree_find(
    BIN_TREE_T *tree, 
    void *key, 
    int (*comp_func)(const void*, const void*))
{
    void *data = NULL;
    find_rec(tree->root, key, &data, comp_func);
    return data;
}

static void find_rec(
    BIN_TREE_NODE_T *node, 
    void *key, 
    void **data, 
    int (*comp_func)(const void*, const void*))
{
    if(node != NULL)
    {
        int result = comp_func(node->data, key);
        if(result == 0)
        {
            *data = node->data;
        }
        else if(result > 0)
        {
            find_rec(node->left, key, data, comp_func);
        }
        else if(result < 0)
        {
            find_rec(node->right, key, data, comp_func);
        }
    }
}

/**
 * @brief 
 *  Finds the number of nodes in a binary tree.
 * 
 * @param tree  binary tree to count
 * 
 * @return The number of nodes in the tree.
 */
int bin_tree_count(BIN_TREE_T *tree)
{
    return count_rec(tree->root);
}

static int count_rec(BIN_TREE_NODE_T *node)
{
    int count = 0;
    if(node != NULL)
    {
        count++;    
        count += count_rec(node->left);
        count += count_rec(node->right);
    }
    return 0;
}