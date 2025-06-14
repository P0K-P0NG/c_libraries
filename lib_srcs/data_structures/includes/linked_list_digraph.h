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
typedef struct DLListNode LListDigraphNode;
typedef struct DLList LListDigraph;

/**
 * @brief
 *  Creates a new linked list digraph.
 *
 * @return Pointer to the new linked list digraph. NULL if memory allocation
 * failed.
 */
extern LListDigraph *LListDigraphCreate();

/**
 * @brief
 *  Deletes a linked list node and frees it's data if given a function to do so.
 *
 * @param graph         linked list digraph to delete
 * @param free_data     function to free data, NULL if not needed
 */
extern void LListDigraphClear(LListDigraph **graph, void (*free_data)(void *));

/**
 * @brief
 *  Adds a new vertex to a linked list digraph.
 *
 * @param graph     linked list digraph to add to
 * @param data      data of the new vertex
 *
 * @return Pointer to the list node with the vertex. NULL if memory allocation
 * failed.
 */
extern LListDigraphNode *LListDigraphAdd(LListDigraph *graph, void *data);

/**
 * @brief
 *  Removes a vertex from a linked list digraph.
 *
 * @param graph         linked list digraph to remove from
 * @param vertex_node   node containg the vertex to remove
 * @param free_data     function to free data, NULL if not needed
 *
 * @return
 *  true  : removal successful @n
 *  false : node pointer is NULL @n
 */
extern bool LListDigraphRemove(LListDigraph *graph,
                               LListDigraphNode *vertex_node,
                               void (*free_data)(void *));

/**
 * @brief
 *  Creates an directional edge from the first vertex to the second.
 *
 * @param start     vertex the edge starts at
 * @param end       vertex the edge ends at
 *
 * @return
 *  true  : connected successful @n
 *  false : memory allocation failed @n
 */
extern bool LListDigraphConnect(struct DigraphVert *start,
                                struct DigraphVert *end);

/**
 * @brief
 *  Removes a directional edge from the first vertex to the second.
 *
 * @param start     vertex the edge starts at
 * @param end       vertex the edge ends at
 *
 * @return
 *  true  : removal successful @n
 *  false : no edge found @n
 */
extern bool LListDigraphDisconnect(struct DigraphVert *start,
                                   struct DigraphVert *end);

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
 * @param graph         linked list digraph to search
 * @param key           key to compare the vertex's data with
 * @param comp_func     function to compare vertex's data and key
 *
 * @return Pointer to the node with the vertex search for. NULL if not found.
 */
extern LListDigraphNode *
LListDigraphFindNode(LListDigraph *graph, const void *key,
                     int (*comp_func)(const void *, const void *));

/**
 * @brief
 *  Checks if an edge from the first vertex to the second exists or not.
 *
 * @param start     vertex the edge starts at
 * @param end       vertex the edge ends at
 *
 * @return
 *  true  : an edge exist @n
 *  false : an edge doesn't exit @n
 */
extern bool LListDigraphIsConnected(struct DigraphVert *start,
                                    struct DigraphVert *end);

/**
 * @brief
 *  Traverses the entire list of vertices in a linked list digraph
 *  and preforms a function on the vertices' data
 *
 * @param graph     linked list digraph to traverse
 * @param func      function to execute
 */
extern void LListDigraphTraverseAll(LListDigraph *graph, void (*func)(void *));

/**
 * @brief
 *  Performs a given function on the data of all the vertices adjacent to the
 *  one passed.
 *
 * @param vertex    vertex with the adjacency list
 * @param func      function to execute
 */
extern void LListDigraphTraverseAdj(struct DigraphVert *vertex,
                                    void (*func)(void *));

/**
 * @brief
 *  Sets the state of all the vertices adjacent to the one passed.
 *
 * @param vertex    vertex with the adjacency list
 * @param state     state to set to
 */
extern void LListDigraphSetAdjState(struct DigraphVert *vertex,
                                    unsigned char state);

/**
 * @brief
 *  Traverses breath first from the given vertex a specified amount of levels
 *  and performs a function on the data of the every vertex encountered.
 *
 * @param vertex    vertex to start at
 * @param max_lvl   further level to traverse; -1 for unbound traversal
 * @param func      function to execute
 *
 * @return
 *  true  : traversed successful @n
 *  false : memory allocation failed @n
 */
extern bool LListDigraphBreathTraverse(struct DigraphVert *vertex, int max_lvl,
                                       void (*func)(void *));
#endif