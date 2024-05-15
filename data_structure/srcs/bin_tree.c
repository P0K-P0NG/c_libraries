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
static void clearRec(BinTreeNode *node, void (*free_data)(void *));
static void inOrderRec(BinTreeNode *node, void (*func)(void *));
static void preOrderRec(BinTreeNode *node, void (*func)(void *));
static void postOrderRec(BinTreeNode *node, void (*func)(void *));
static int addRec(BinTreeNode **node, void *data,
                  int (*comp_func)(const void *, const void *));
static void findRec(BinTreeNode *node, void *key, void **data,
                    int (*comp_func)(const void *, const void *));
static int countRec(BinTreeNode *node);

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
BinTree *BinTreeCreate()
{
    return calloc(1, sizeof(BinTreeNode *));
}

/**
 * @brief
 *  Deletes a binary tree.
 *
 * @param tree  binary tree to delete
 */
void BinTreeClear(BinTree **tree, void (*free_data)(void *))
{
    clearRec((*tree)->root, free_data);
    free(*tree);
    *tree = NULL;
}

void clearRec(BinTreeNode *node, void (*free_data)(void *))
{
    if (node != NULL)
    {
        clearRec(node->left, free_data);
        clearRec(node->right, free_data);
        if (free_data != NULL)
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
void BinTreeInOrder(BinTree *tree, void (*func)(void *))
{
    inOrderRec(tree->root, func);
}

void inOrderRec(BinTreeNode *node, void (*func)(void *))
{
    if (node->left != NULL)
    {
        inOrderRec(node->left, func);
    }
    func(node->data);
    if (node->right != NULL)
    {
        inOrderRec(node->right, func);
    }
}

/**
 * @brief
 *  Executes a given function on all the nodes in pre-order traversal.
 *
 * @param tree  binary tree to execute on
 * @param func  function to execute the nodes with
 */
void BinTreePreOrder(BinTree *tree, void (*func)(void *))
{
    preOrderRec(tree->root, func);
}

static void preOrderRec(BinTreeNode *node, void (*func)(void *))
{
    func(node->data);
    if (node->left != NULL)
    {
        preOrderRec(node->left, func);
    }
    if (node->right != NULL)
    {
        preOrderRec(node->right, func);
    }
}

/**
 * @brief
 *  Executes a function on all the nodes in post-order traversal.
 *
 * @param tree  binary tree to execute on
 * @param func  function to execute the nodes with
 */
void BinTreePostOrder(BinTree *tree, void (*func)(void *))
{
    postOrderRec(tree->root, func);
}

static void postOrderRec(BinTreeNode *node, void (*func)(void *))
{
    if (node->left != NULL)
    {
        postOrderRec(node->left, func);
    }
    if (node->right != NULL)
    {
        postOrderRec(node->right, func);
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
int BinTreeAdd(
    BinTree *tree,
    void *data,
    int (*comp_func)(const void *, const void *))
{
    return addRec(&(tree->root), data, comp_func);
}

static int addRec(
    BinTreeNode **node,
    void *data,
    int (*comp_func)(const void *, const void *))
{
    int status = 0;
    if (*node != NULL)
    {
        int result = comp_func((*node)->data, data);
        if (result > 0)
        {
            status = addRec(&((*node)->left), data, comp_func);
        }
        else if (result < 0)
        {
            status = addRec(&((*node)->right), data, comp_func);
        }
        else
        {
            status = 2;
            (*node)->count += 1;
        }
    }
    else
    {
        if ((*node = calloc(1, sizeof(BinTreeNode))) != NULL)
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
void *BinTreeFind(
    BinTree *tree,
    void *key,
    int (*comp_func)(const void *, const void *))
{
    void *data = NULL;
    findRec(tree->root, key, &data, comp_func);
    return data;
}

static void findRec(
    BinTreeNode *node,
    void *key,
    void **data,
    int (*comp_func)(const void *, const void *))
{
    if (node != NULL)
    {
        int result = comp_func(node->data, key);
        if (result == 0)
        {
            *data = node->data;
        }
        else if (result > 0)
        {
            findRec(node->left, key, data, comp_func);
        }
        else if (result < 0)
        {
            findRec(node->right, key, data, comp_func);
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
int BinTreeCount(BinTree *tree)
{
    return countRec(tree->root);
}

static int countRec(BinTreeNode *node)
{
    int count = 0;
    if (node != NULL)
    {
        count++;
        count += countRec(node->left);
        count += countRec(node->right);
    }
    return 0;
}