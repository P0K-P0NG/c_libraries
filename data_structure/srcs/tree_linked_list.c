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
#include <stdlib.h>
#include "linked_list.h"
#include "tree_linked_list.h"

int LListTreeDeepestNodesRec(
    LListTreeNode *node, int depth, int deepest, LList *node_list);

/**
 * @brief
 *  Creates the root node of a linked list tree structure.
 *
 * @param data  data for the root node
 *
 * @return Pointer to the new root node, NULL is unable to allocate memory.
 */
LListTreeNode *LListTreeCreate(void *data)
{
    LListTreeNode *root = calloc(1, sizeof(LListTreeNode));
    if (root != NULL)
    {
        root->data = data;
    }
    return root;
}

/**
 * @brief
 *  Deletes a linked list tree structure.
 *
 * @param root          root node of the tree to delete
 * @param free_data     function to free the data, NULL if not needed
 */
void LListTreeClear(LListTreeNode **root, void (*free_data)(void *))
{
    if ((*root)->head_child != NULL)
    {
        LListTreeClear(&((*root)->head_child), free_data);
    }
    else if ((*root)->next != NULL)
    {
        LListTreeClear(&((*root)->next), free_data);
    }
    if (free_data != NULL)
    {
        free_data((*root)->data);
    }
    free(*root);
    *root = NULL;
}

/**
 * @brief
 *  Adds a new linked list tree node as the child of the inputted node.
 *
 * @param parent    parent node of the new node
 * @param data      data of the new node
 *
 * @return
 *   1 : added successfully @n
 *   0 : unable to allocate memory @n
 *  -1 : NULL pointer was passed in @n
 */
int LListTreeAdd(LListTreeNode *parent, void *data)
{
    int is_made = 0;
    LListTreeNode *new_child = calloc(1, sizeof(LListTreeNode));
    if (new_child != NULL)
    {
        is_made = 1;
        new_child->parent = parent;
        new_child->data = data;
        new_child->next = parent->head_child;
        parent->head_child = new_child;
    }
    return is_made;
}

/**
 * @brief
 *  Edits the data of a given linked list tree node.
 *
 * @param node  node to edit
 * @param data  data of the new node
 */
void LListTreeEdit(LListTreeNode *node, void *data)
{
    node->data = data;
}

/**
 * @brief
 *  Finds and returns the pointer to the first tree node (in a depth first traversal)
 *  with data matching the input, if there is any.
 *
 * @note
 *  The function used to compare must behave in the follows
 *  ways in order for the function to perform properly. @n
 *  1) WHEN input_1 > input_2,  RETURNS a postive integer @n
 *  2) WHEN input_1 < input_2,  RETURNS a negative integer @n
 *  3) WHEN input_1 == input_2, RETURNS zero @n
 *
 * @param root          root node of the tree to search
 * @param data          data of the node to find
 * @param comp_func     function to compare the data
 *
 * @return Pointer to the node with matching data, NULL if not found.
 */
LListTreeNode *LListTreeGetNode(
    LListTreeNode *root,
    void *data,
    int (*comp_func)(const void *, const void *))
{
    LListTreeNode *target = NULL;
    if (comp_func(root->data, data) != 0)
    {
        if (root->head_child != NULL)
        {
            target = LListTreeGetNode(root->head_child, data, comp_func);
        }
        if (root->next != NULL && target == NULL)
        {
            target = LListTreeGetNode(root->next, data, comp_func);
        }
    }
    else
    {
        target = root;
    }
    return target;
}

/**
 * @brief
 *  Finds the number of child nodes belong to the inputted node/
 *
 * @param parent    node to count the children of
 *
 * @return number of child nodes.
 */
int LListTreeCountChild(LListTreeNode *parent)
{
    int count = 0;
    LListTreeNode *curr = parent->head_child;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

/**
 * @brief
 *  Executes a function on all the nodes in the linked list tree, with a depth first traversal
 *  pioritizing the last child node, then the silibing nodes in the reverse order of recency,
 *  then the parent node. Immediately executes the nodes when it is first called.
 *
 * @param root      root node of the tree
 * @param depth     starting depth level (larger values are deeper)
 * @param func      function to execute
 */
void LListTreePreOrder(
    LListTreeNode *root,
    int depth,
    void (*func)(void *, int))
{
    func(root->data, depth);
    if (root->head_child != NULL)
    {
        LListTreePreOrder(root->head_child, depth + 1, func);
    }
    if (root->next != NULL)
    {
        LListTreePreOrder(root->next, depth, func);
    }
}

/**
 * @brief
 *  Executes a function on all the nodes in the linked list tree, with a depth first traversal
 *  pioritizing the last child node, then the silibing nodes in the reverse order of recency,
 *  then the parent node. Starts executing a node once it cannot go a layer deeper or already
 *  has gone deeper.
 *
 * @param root      root node of the tree
 * @param depth     starting depth level (larger values are deeper)
 * @param func      function to execute
 */
void LListTreeInOrder(
    LListTreeNode *root,
    int depth,
    void (*func)(void *, int))
{
    if (root->head_child != NULL)
    {
        LListTreeInOrder(root->head_child, depth + 1, func);
    }
    func(root->data, depth);
    if (root->next != NULL)
    {
        LListTreeInOrder(root->next, depth, func);
    }
}

/**
 * @brief
 *  Executes a function on all the nodes in the linked list tree, with a depth first traversal
 *  pioritizing the last child node, then the silibing nodes in the reverse order of recency,
 *  then the parent node. Starts executing a node once it cannot go a layer deeper and is has no
 *  older sibling node (in terms of time added) or the layer below and it's older silibing Node(s)
 *  has already been executed.
 *
 * @param root      root node of the tree
 * @param depth     starting depth level (larger values are deeper)
 * @param func      function to execute
 */
void LListTreePostOrder(
    LListTreeNode *root,
    int depth,
    void (*func)(void *, int))
{
    if (root->head_child != NULL)
    {
        LListTreePostOrder(root->head_child, depth + 1, func);
    }
    if (root->next != NULL)
    {
        LListTreePostOrder(root->next, depth, func);
    }
    func(root->data, depth);
}

int LListTreeDeepestNodes(LListTreeNode *root, LListTreeNode **node_arr)
{
    LList *node_list = LListCreate();
    int deepest = LListTreeDeepestNodesRec(root, 0, 0, node_list);
    if (deepest == -1)
    {
        LListClear(&node_list, NULL);
        return -1;
    }
    int count = node_list->count;
    *node_arr = malloc(count * sizeof(LListTreeNode));
    if (*node_arr == NULL)
    {
        LListClear(&node_list, NULL);
        return -1;
    }
    LListToArr(node_list, *node_arr, count, sizeof(LListTreeNode));
    LListClear(&node_list, NULL);
    return count;
}

int LListTreeDeepestNodesRec(
    LListTreeNode *node, int depth,
    int deepest, LList *node_list)
{
    if (node->head_child != NULL)
    {
        deepest = LListTreeDeepestNodesRec(
            node->head_child, depth + 1, deepest, node_list);
    }
    if (node->next != NULL)
    {
        deepest = LListTreeDeepestNodesRec(
            node->next, depth, deepest, node_list);
    }
    if (deepest == -1)
        ;
    else if (depth > deepest)
    {
        deepest = depth;
        LListRemoveAll(node_list, NULL);
        if (LListPush(node_list, node) == 0)
        {
            deepest = -1;
        }
    }
    else if (depth == deepest)
    {
        if (LListPush(node_list, node) == 0)
        {
            deepest = -1;
        }
    }
    return deepest;
}