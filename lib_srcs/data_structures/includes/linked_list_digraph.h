/**
 * @file linked_list_digraph.h
 *
 * @brief
 *  Structs and functions for linked list digraphs.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-21
 */
#ifndef LINKED_LIST_DIGRAPH_H
#define LINKED_LIST_DIGRAPH_H

#include "digraph.h"
#include "doubly_linked_list.h"
#include <stdbool.h>

// redefining for more clarity
typedef struct DLListNode LListDigraphNode_t;
typedef struct DLList LListDigraph_t;

/**
 * @brief
 *  Creates a new linked list digraph.
 *
 * @return Pointer to the new linked list digraph. NULL if memory allocation
 * failed.
 */
extern LListDigraph_t *LListDigraphCreate();

/**
 * @brief
 *  Deletes a linked list digraph and frees it's data if given a function to do
 *  so.
 *
 * @param[in,out] p_graph       linked list digraph to delete
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void LListDigraphClear(LListDigraph_t **p_graph,
                              void (*free_data)(void *));

/**
 * @brief
 *  Adds a new vertex to a linked list digraph.
 *
 * @param[in,out] graph     linked list digraph to add to
 * @param[in]     data      data of the new vertex
 *
 * @return Pointer to the list node with the vertex. NULL if memory allocation
 * failed.
 */
extern LListDigraphNode_t *LListDigraphAdd(LListDigraph_t *graph, void *data);

/**
 * @brief
 *  Removes a vertex from a linked list digraph.
 *
 * @param[in,out] graph         linked list digraph to remove from
 * @param[in]     vert_node     node containg the vertex to remove
 * @param[in]     free_data     function to free data, NULL if not needed
 *
 * @return
 *  true  : removal successful @n
 *  false : node pointer is NULL @n
 */
extern bool LListDigraphRemove(LListDigraph_t *graph,
                               LListDigraphNode_t *vert_node,
                               void (*free_data)(void *));

/**
 * @brief
 *  Creates an directional edge from the first vertex to the second.
 *
 * @param[in,out] start     node of vertex the edge starts at
 * @param[in,out] end       node of vertex the edge ends at
 *
 * @return
 *  true  : connection successful @n
 *  false : memory allocation failed @n
 */
extern bool LListDigraphConnect(LListDigraphNode_t *start,
                                LListDigraphNode_t *end);

/**
 * @brief
 *  Removes a directional edge from the first vertex to the second.
 *
 * @param[in,out] start     node of vertex the edge starts at
 * @param[in,out] end       node of vertex the edge ends at
 *
 * @return
 *  true  : disconnection successful @n
 *  false : no edge found @n
 */
extern bool LListDigraphDisconnect(LListDigraphNode_t *start,
                                   LListDigraphNode_t *end);

/**
 * @brief
 *  Checks if an edge from the first vertex to the second exists or not.
 *
 * @param[in,out] start     node of vertex the edge starts at
 * @param[in,out] end       node of vertex the edge ends at
 *
 * @return
 *  true  : an edge exist @n
 *  false : an edge doesn't exit @n
 */
extern bool LListDigraphIsConnected(LListDigraphNode_t *start,
                                    LListDigraphNode_t *end);

/**
 * @brief
 *  Finds the node of the vertex that matches the given key.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 *  doesn't. @n
 *  Compare function input No. : @n
 *  1) data from the doubly linked list @n
 *  2) key @n
 *
 * @param[in,out] graph         linked list digraph to search
 * @param[in]     key           key to compare the vertex's data with
 * @param[in]     comp_func     function to compare vertex's data and key
 *
 * @return Pointer to the node with the vertex search for. NULL if not found.
 */
extern LListDigraphNode_t *
LListDigraphFind(LListDigraph_t *graph, const void *key,
                 int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Traverses the entire list of vertices in a linked list digraph
 *  and preforms a function on the vertices' data
 *
 * @param[in,out] graph     linked list digraph to traverse
 * @param[in]     func      function to execute
 */
extern void LListDigraphTraverseAll(LListDigraph_t *graph,
                                    void (*func)(void *));

/**
 * @brief
 *  Performs a given function on the data of all the vertices adjacent to the
 *  one passed.
 *
 * @param[in,out] vert_node     node of vertex with the adjacency list
 * @param[in]     func          function to execute
 */
extern void LListDigraphTraverseAdj(LListDigraphNode_t *vert_node,
                                    void (*func)(void *));

/**
 * @brief
 *  Sets the state of all the vertices adjacent to the one passed.
 *
 * @param[in,out] vert_node    node of vertex with the adjacency list
 * @param[in]     state     state to set to
 */
extern void LListDigraphSetAdjState(LListDigraphNode_t *vert_node,
                                    unsigned char state);

/**
 * @brief
 *  Traverses breath first from the given vertex a specified amount of levels
 *  and performs a function on the data of the every vertex encountered.
 *
 * @param[in,out] vert_node     node of vertex to start at
 * @param[in]     max_lvl       further level to traverse; -1 for unbound
 * traversal
 * @param[in]     func          function to execute
 *
 * @return
 *  true  : traversal successful @n
 *  false : memory allocation failed @n
 */
extern bool LListDigraphBreathTraverse(LListDigraphNode_t *vert_node,
                                       int max_lvl, void (*func)(void *));
#endif