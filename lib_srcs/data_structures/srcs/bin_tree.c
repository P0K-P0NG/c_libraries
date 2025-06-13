/**
 * @file bin_tree.c
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
#include "bin_tree.h"
#include <assert.h>
#include <stdlib.h>

/**
 * LOCAL FUNTION DECLARATIONS
 *
 * These function aren't defined outside of this source file and are not
 * intended to be acessed directly.
 */
static void _clearRec(struct BinTreeNode *node, void (*free_data)(void *));
static void _inOrderRec(struct BinTreeNode *node, void (*func)(void *));
static void _preOrderRec(struct BinTreeNode *node, void (*func)(void *));
static void _postOrderRec(struct BinTreeNode *node, void (*func)(void *));
static int _addRec(struct BinTreeNode **p_node, void *data,
                   int (*comp_func)(const void *, const void *));
static void _findRec(struct BinTreeNode *node, void *key, void **data,
                     int (*comp_func)(const void *, const void *));
static size_t _countRec(struct BinTreeNode *node);

struct BinTree *BinTreeCreate() { return calloc(1, sizeof(struct BinTree *)); }

void BinTreeClear(struct BinTree **p_tree, void (*free_data)(void *))
{
    assert(p_tree != NULL);
    assert(*p_tree != NULL);

    _clearRec((*p_tree)->root, free_data);
    free(*p_tree);
    *p_tree = NULL;
}

void _clearRec(struct BinTreeNode *node, void (*free_data)(void *))
{
    if (node != NULL) {
        _clearRec(node->left, free_data);
        _clearRec(node->right, free_data);
        if (free_data != NULL) {
            free_data(node->data);
        }
        free(node);
    }
}

void BinTreeInOrder(struct BinTree *tree, void (*func)(void *))
{
    assert(tree != NULL);
    assert(func != NULL);

    if (tree->root != NULL) {
        _inOrderRec(tree->root, func);
    }
}

void _inOrderRec(struct BinTreeNode *node, void (*func)(void *))
{
    if (node->left != NULL) {
        _inOrderRec(node->left, func);
    }
    func(node->data);
    if (node->right != NULL) {
        _inOrderRec(node->right, func);
    }
}

void BinTreePreOrder(struct BinTree *tree, void (*func)(void *))
{
    assert(tree != NULL);
    assert(func != NULL);

    if (tree->root != NULL) {
        _preOrderRec(tree->root, func);
    }
}

static void _preOrderRec(struct BinTreeNode *node, void (*func)(void *))
{
    func(node->data);
    if (node->left != NULL) {
        _preOrderRec(node->left, func);
    }
    if (node->right != NULL) {
        _preOrderRec(node->right, func);
    }
}

void BinTreePostOrder(struct BinTree *tree, void (*func)(void *))
{
    assert(tree != NULL);
    assert(func != NULL);

    if (tree->root != NULL) {
        _postOrderRec(tree->root, func);
    }
}

static void _postOrderRec(struct BinTreeNode *node, void (*func)(void *))
{
    if (node->left != NULL) {
        _postOrderRec(node->left, func);
    }
    if (node->right != NULL) {
        _postOrderRec(node->right, func);
    }
    func(node->data);
}

int BinTreeAdd(struct BinTree *tree, void *data,
               int (*comp_func)(const void *, const void *))
{
    assert(tree != NULL);
    assert(comp_func != NULL);

    return _addRec(&(tree->root), data, comp_func);
}

static int _addRec(struct BinTreeNode **p_node, void *data,
                   int (*comp_func)(const void *, const void *))
{
    int status = 0;
    if (*p_node != NULL) {
        int result = comp_func((*p_node)->data, data);
        if (result > 0) {
            status = _addRec(&((*p_node)->left), data, comp_func);
        } else if (result < 0) {
            status = _addRec(&((*p_node)->right), data, comp_func);
        } else {
            status = 2;
            (*p_node)->count += 1;
        }
    } else {
        if ((*p_node = calloc(1, sizeof(struct BinTreeNode))) != NULL) {
            status = 1;
            (*p_node)->data = data;
        }
    }
    return status;
}

void *BinTreeFind(struct BinTree *tree, void *key,
                  int (*comp_func)(const void *, const void *))
{
    assert(tree != NULL);
    assert(comp_func != NULL);

    void *data = NULL;
    _findRec(tree->root, key, &data, comp_func);
    return data;
}

static void _findRec(struct BinTreeNode *node, void *key, void **data,
                     int (*comp_func)(const void *, const void *))
{
    if (node != NULL) {
        int result = comp_func(node->data, key);
        if (result == 0) {
            *data = node->data;
        } else if (result > 0) {
            _findRec(node->left, key, data, comp_func);
        } else if (result < 0) {
            _findRec(node->right, key, data, comp_func);
        }
    }
}

size_t BinTreeCount(struct BinTree *tree)
{
    assert(tree != NULL);

    return _countRec(tree->root);
}

static size_t _countRec(struct BinTreeNode *node)
{
    size_t count = 0;
    if (node != NULL) {
        count++;
        count += _countRec(node->left);
        count += _countRec(node->right);
    }
    return count;
}