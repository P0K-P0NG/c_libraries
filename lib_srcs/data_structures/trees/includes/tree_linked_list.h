/**
 * @file tree_linked_list.h
 *
 * @brief
 *  structs and functions for building linked list tree structures
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-04-23
 */
#ifndef TREE_LINKED_LIST_H
#define TREE_LINKED_LIST_H

typedef struct LListTreeNode {            // struct of a tree node of a tree structure
    void *data;                   // pointer to data
    struct LListTreeNode *parent; // parent node of this node
    struct LListTreeNode *next;   // the next sibling node in reverse of the
                                  // order added
    struct LListTreeNode *head_child; // the most recent child
                                      // added of this node
} LListTreeNode_t;

/**
 * @brief
 *  Creates the root node of a linked list tree structure.
 *
 * @param[in] data  data for the root node
 *
 * @return Pointer to the new root node, NULL is unable to allocate memory.
 */
extern LListTreeNode_t *LListTreeCreate(void *data);

/**
 * @brief
 *  Deletes a linked list tree structure.
 *
 * @param[in,out] p_root        root node of the tree to delete
 * @param[in]     free_data     function to free the data, NULL if not needed
 */
extern void LListTreeClear(LListTreeNode_t **p_root,
                           void (*free_data)(void *));

/**
 * @brief
 *  Adds a new linked list tree node as the child of the inputted node.
 *
 * @param[in,out] parent    parent node of the new node
 * @param[in]     data      data of the new node
 *
 * @return
 *   1 : added successfully @n
 *   0 : unable to allocate memory @n
 */
extern int LListTreeAdd(LListTreeNode_t *parent, void *data);

/**
 * @brief
 *  Edits the data of a given linked list tree node.
 *
 * @param[in,out] node  node to edit
 * @param[in]     data  data of the new node
 */
extern void LListTreeEdit(LListTreeNode_t *node, void *data);

/**
 * @brief
 *  Finds and returns the pointer to the first tree node (in a depth first
 *  traversal) with data matching the input, if there is any.
 *
 * @note
 *  The function used to compare must behave in the follows
 *  ways in order for the function to perform properly. @n
 *  1) WHEN input_1 > input_2,  RETURNS a postive integer @n
 *  2) WHEN input_1 < input_2,  RETURNS a negative integer @n
 *  3) WHEN input_1 == input_2, RETURNS zero @n
 *  Compare function input No. : @n
 *  1) data from the linked list @n
 *  2) key @n
 *
 * @param[in] root          root node of the tree to search
 * @param[in] data          data of the node to find
 * @param[in] comp_func     function to compare the data
 *
 * @return Pointer to the node with matching data, NULL if not found.
 */
extern LListTreeNode_t *
LListTreeGetNode(LListTreeNode_t *root, void *data,
                 int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Finds the number of child nodes belong to the inputted node/
 *
 * @param[in] parent    node to count the children of
 *
 * @return Number of child nodes.
 */
extern int LListTreeCountChild(LListTreeNode_t *parent);

/**
 * @brief
 *  Executes a function on all the nodes in the linked list tree, with a depth
 *  first traversal pioritizing the last child node, then the silibing nodes in
 *  the reverse order of recency, then the parent node. Immediately executes the
 *  nodes when it is first called.
 *
 * @param[in,out] root      root node of the tree
 * @param[in]     depth     starting depth level (larger values are deeper)
 * @param[in]     func      function to execute
 */
extern void LListTreePreOrder(LListTreeNode_t *root, int depth,
                              void (*func)(void *, int));

/**
 * @brief
 *  Executes a function on all the nodes in the linked list tree, with a depth
 *  first traversal pioritizing the last child node, then the silibing nodes in
 *  the reverse order of recency, then the parent node. Starts executing a node
 *  once it cannot go a layer deeper or already has gone deeper.
 *
 * @param[in,out] root      root node of the tree
 * @param[in]     depth     starting depth level (larger values are deeper)
 * @param[in]     func      function to execute
 */
extern void LListTreeInOrder(LListTreeNode_t *root, int depth,
                             void (*func)(void *, int));

/**
 * @brief
 *  Executes a function on all the nodes in the linked list tree, with a depth
 *  first traversal pioritizing the last child node, then the silibing nodes in
 *  the reverse order of recency, then the parent node. Starts executing a node
 *  once it cannot go a layer deeper and is has no older sibling node (in terms
 *  of time added) or the layer below and it's older silibing Node(s) has
 *  already been executed.
 *
 * @param[in,out] root      root node of the tree
 * @param[in]     depth     starting depth level (larger values are deeper)
 * @param[in]     func      function to execute
 */
extern void LListTreePostOrder(LListTreeNode_t *root, int depth,
                               void (*func)(void *, int));

/**
 * @brief
 *  Finds the deepest nodes in a linked list tree and stores it in an array.
 *
 * @param[in]  root         root of the tree to search
 * @param[out] node_arr     array to store in
 *
 * @return 1 if executed successfully, 0 if unable to allocate memory.
 */
extern int LListTreeDeepestNodes(LListTreeNode_t *root,
                                 LListTreeNode_t **node_arr);
#endif