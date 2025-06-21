/**
 * @file tree_linked_list.c
 *
 * @brief
 *  structs and functions for building linked list tree structures
 *
 * @implements
 *  tree_linked_list.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-04-23
 */
#include "tree_linked_list.h"
#include "linked_list.h"
#include <stdlib.h>

static int _deepestNodesRec(LListTreeNode_t *node, int depth, int deepest,
                            LList_t *node_list);

LListTreeNode_t *LListTreeCreate(void *data)
{
    LListTreeNode_t *root = calloc(1, sizeof(LListTreeNode_t));
    if (root != NULL) {
        root->data = data;
    }
    return root;
}

void LListTreeClear(LListTreeNode_t **root, void (*free_data)(void *))
{
    if ((*root)->head_child != NULL) {
        LListTreeClear(&((*root)->head_child), free_data);
    } else if ((*root)->next != NULL) {
        LListTreeClear(&((*root)->next), free_data);
    }
    if (free_data != NULL) {
        free_data((*root)->data);
    }
    free(*root);
    *root = NULL;
}

int LListTreeAdd(LListTreeNode_t *parent, void *data)
{
    int is_made = 0;
    LListTreeNode_t *new_child = calloc(1, sizeof(LListTreeNode_t));
    if (new_child != NULL) {
        is_made = 1;
        new_child->parent = parent;
        new_child->data = data;
        new_child->next = parent->head_child;
        parent->head_child = new_child;
    }
    return is_made;
}

void LListTreeEdit(LListTreeNode_t *node, void *data)
{
    node->data = data;
}

LListTreeNode_t *LListTreeGetNode(LListTreeNode_t *root, void *data,
                                       int (*comp_func)(const void *,
                                                        const void *))
{
    LListTreeNode_t *target = NULL;
    if (comp_func(root->data, data) != 0) {
        if (root->head_child != NULL) {
            target = LListTreeGetNode(root->head_child, data, comp_func);
        }
        if (root->next != NULL && target == NULL) {
            target = LListTreeGetNode(root->next, data, comp_func);
        }
    } else {
        target = root;
    }
    return target;
}

int LListTreeCountChild(LListTreeNode_t *parent)
{
    int count = 0;
    LListTreeNode_t *curr = parent->head_child;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

void LListTreePreOrder(LListTreeNode_t *root, int depth,
                       void (*func)(void *, int))
{
    func(root->data, depth);
    if (root->head_child != NULL) {
        LListTreePreOrder(root->head_child, depth + 1, func);
    }
    if (root->next != NULL) {
        LListTreePreOrder(root->next, depth, func);
    }
}

void LListTreeInOrder(LListTreeNode_t *root, int depth,
                      void (*func)(void *, int))
{
    if (root->head_child != NULL) {
        LListTreeInOrder(root->head_child, depth + 1, func);
    }
    func(root->data, depth);
    if (root->next != NULL) {
        LListTreeInOrder(root->next, depth, func);
    }
}

void LListTreePostOrder(LListTreeNode_t *root, int depth,
                        void (*func)(void *, int))
{
    if (root->head_child != NULL) {
        LListTreePostOrder(root->head_child, depth + 1, func);
    }
    if (root->next != NULL) {
        LListTreePostOrder(root->next, depth, func);
    }
    func(root->data, depth);
}

int LListTreeDeepestNodes(LListTreeNode_t *root,
                          LListTreeNode_t **node_arr)
{
    LList_t *node_list = LListCreate();
    int deepest = _deepestNodesRec(root, 0, 0, node_list);
    if (deepest == -1) {
        LListClear(&node_list, NULL);
        return -1;
    }
    int count = node_list->count;
    *node_arr = malloc(count * sizeof(LListTreeNode_t));
    if (*node_arr == NULL) {
        LListClear(&node_list, NULL);
        return -1;
    }
    LListToArr(node_list, *node_arr, count, sizeof(LListTreeNode_t));
    LListClear(&node_list, NULL);
    return count;
}

static int _deepestNodesRec(LListTreeNode_t *node, int depth, int deepest,
                            LList_t *node_list)
{
    if (node->head_child != NULL) {
        deepest
            = _deepestNodesRec(node->head_child, depth + 1, deepest, node_list);
    }
    if (node->next != NULL) {
        deepest = _deepestNodesRec(node->next, depth, deepest, node_list);
    }
    if (deepest == -1)
        ;
    else if (depth > deepest) {
        deepest = depth;
        LListRemoveAll(node_list, NULL);
        if (LListAddHead(node_list, node) == false) {
            deepest = -1;
        }
    } else if (depth == deepest) {
        if (LListAddHead(node_list, node) == false) {
            deepest = -1;
        }
    }
    return deepest;
}