/**
 * @file linked_list_graph.h
 * 
 * @brief 
 *  Structs and functions for linked list graphs.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-21
 */
#ifndef LINKED_LIST_GRAPH_H
#define LINKED_LIST_GRAPH_H

#include "doubly_linked_list.h"
#include "graph.h"

// redefining for more clarity
typedef DLListNode LListGraphNode;    
typedef DLList LListGraph;

/**
 * @brief 
 *  Creates a new linked list graph.
 * 
 * @return Pointer to the new linked list graph. NULL if memory allocation failed.
 */
extern LListGraph *LListGraphCreate();

/**
 * @brief 
 *  Deletes a linked list node and frees it's data if given a function to do so.
 * 
 * @param graph         linked list graph to delete
 * @param free_data     function to free data, NULL if not needed
 */
extern void LListGraphClear(LListGraph **graph, void (*free_data)(void*));

/**
 * @brief 
 *  Adds a new vertex to a linked list graph.
 * 
 * @param graph     linked list graph to add to 
 * @param data      data of the new vertex
 * 
 * @return Pointer to the list node with the vertex. NULL if memory allocation failed.
 */
extern LListGraphNode *LListGraphAdd(LListGraph *graph, void *data);

/**
 * @brief 
 *  Removes a vertex from a linked list graph.
 * 
 * @param graph         linked list graph to remove from
 * @param vertex_node   node containg the vertex to remove
 * @param free_data     function to free data, NULL if not needed
 * 
 * @return 
 *  1 : removal successful @n
 *  0 : node pointer is NULL @n
 */
extern int LListGraphRemove(LListGraph *graph, LListGraphNode *vertex_node, void (*free_data)(void*));

/**
 * @brief 
 *  Creates an directional edge from the first vertex to the second.
 * 
 * @param start     vertex the edge starts at
 * @param end       vertex the edge ends at
 * 
 * @return 
 *  1 : connected successful @n
 *  0 : memory allocation failed @n
 */
extern int LListGraphConnect(GraphVert *start, GraphVert *end);

/**
 * @brief 
 *  Removes a directional edge from the first vertex to the second.
 * 
 * @param start     vertex the edge starts at
 * @param end       vertex the edge ends at
 * 
 * @return 
 *  1 : removal successful @n
 *  0 : no edge found @n
 */
extern int LListGraphDisconnect(GraphVert *start, GraphVert *end);

/**
 * @brief 
 *  Finds the node of the vertex that matches the given key.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't. @n
 *  Compare function input No. : @n 
 *  1) data from the doubly linked list @n 
 *  2) key @n 
 * 
 * @param graph         linked list graph to search
 * @param key           key to compare the vertex's data with
 * @param comp_func     function to compare vertex's data and key
 * 
 * @return Pointer to the node with the vertex search for. NULL if not found.
 */
extern LListGraphNode *LListGraphFindNode(LListGraph *graph, const void *key, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Checks if an edge from the first vertex to the second exists or not.
 * 
 * @param start     vertex the edge starts at
 * @param end       vertex the edge ends at
 * 
 * @return 
 *  1 : an edge exist @n
 *  0 : an edge doesn't exit @n
 */
extern int LListGraphIsConnected(GraphVert *start, GraphVert *end);

/**
 * @brief 
 *  Traverses the entire list of vertices in a linked list graph 
 *  and preforms a function on the vertices' data
 * 
 * @param graph     linked list graoh to traverse
 * @param func      function to execute
 */
extern void LListGraphTraverseAll(LListGraph *graph, void (*func)(void*));

/**
 * @brief 
 *  Performs a given function on the data of all the vertices adjacent to the one passed. 
 * 
 * @param vertex    vertex with the adjacency list
 * @param func      function to execute 
 */
extern void LListGraphTraverseAdj(GraphVert *vertex, void (*func)(void*));

/**
 * @brief 
 *  Sets the state of all the vertices adjacent to the one passed.
 * 
 * @param vertex    vertex with the adjacency list
 * @param state     state to set to
 */
extern void LListGraphSetAdjState(GraphVert *vertex, unsigned char state);

/**
 * @brief 
 *  Traverses breath first from the given vertex a specified amount of levels and performs a 
 *  function on the data of the every vertex encountered.
 * 
 * @param vertex    vertex to start at
 * @param max_lvl   further level to traverse; -1 for unbound traversal
 * @param func      function to execute 
 * 
 * @return
 *  1 : traversed successful @n
 *  0 : memory allocation failed @n
 */
extern int LListGraphBreathTraverse(GraphVert *vertex, int max_lvl, void (*func)(void*));
#endif