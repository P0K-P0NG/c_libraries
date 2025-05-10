/**
 * @file list_graph.h
 * 
 * @brief 
 *  Structs and functions for linked list graphs.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-21
 */
#ifndef GRAPH_H
#define GRAPH_H

#include "doubly_linked_list.h"

typedef struct graph_vertex     // linked list graph vertex
{
    void *data;                 // pointer to data
    int lvl;                    // tracks the level/depth of the vertex in a traversal
    unsigned char state;        // indicates the vertex state in a traversal; 
                                // 0 = have not passed, 1 = have passed, 2 = skip 
    DLList adj_list;     // list of adjacent vertices
    DLList ref_list;     // list of vertices this vertex is adjacent to
} GraphVert;


GraphVert *GraphInitVert(void *data);

int GraphRemoveVert(GraphVert **vert, void (*free_data)(void *));

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
int GraphConnect(GraphVert *start, GraphVert *end);

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
int GraphDisconnect(GraphVert *start, GraphVert *end);

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
int GraphIsConnected(GraphVert *start, GraphVert *end);

/**
 * @brief 
 *  Performs a given function on the data of all the vertices adjacent to the one passed. 
 * 
 * @param vertex    vertex with the adjacency list
 * @param func      function to execute 
 */
void GraphTraverseAdj(GraphVert *vertex, void (*func)(void*));

/**
 * @brief 
 *  Sets the state of all the vertices adjacent to the one passed.
 * 
 * @param vertex    vertex with the adjacency list
 * @param state     state to set to
 */
void GraphSetAdjState(GraphVert *vertex, unsigned char state);

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
int GraphBreathTraverse(GraphVert *vertex, int max_lvl, void (*func)(void*));
#endif