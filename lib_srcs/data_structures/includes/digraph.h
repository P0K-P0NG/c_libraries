/**
 * @file digraph.h
 *
 * @brief
 *  Structs and functions for digraphs (directed digraphs).
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-21
 */
#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "doubly_linked_list.h"
#include <stdbool.h>

struct DigraphVert {     // linked list digraph vertex
    void *data;          // pointer to data
    int lvl;             // tracks the level/depth of the vertex in a traversal
    unsigned char state; // indicates the vertex state in a traversal;
                         // 0 = have not passed, 1 = have passed, 2 = skip
    struct DLList adj_list; // list of adjacent vertices
    struct DLList ref_list; // list of vertices this vertex is adjacent to
};

struct DigraphVert *DigraphInitVert(void *data);

/**
 * @brief
 *  Remove an vertex from the digraph.
 *
 * @param start     vertex the edge starts at
 * @param end       vertex the edge ends at
 *
 * @return
 *  true  : connected successful @n
 *  false : memory allocation failed @n
 */
bool DigraphRemoveVert(struct DigraphVert **vert, void (*free_data)(void *));

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
bool DigraphConnect(struct DigraphVert *start, struct DigraphVert *end);

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
bool DigraphDisconnect(struct DigraphVert *start, struct DigraphVert *end);

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
bool DigraphIsConnected(struct DigraphVert *start, struct DigraphVert *end);

/**
 * @brief
 *  Performs a given function on the data of all the vertices adjacent to the
 * one passed.
 *
 * @param vertex    vertex with the adjacency list
 * @param func      function to execute
 */
void DigraphTraverseAdj(struct DigraphVert *vertex, void (*func)(void *));

/**
 * @brief
 *  Sets the state of all the vertices adjacent to the one passed.
 *
 * @param vertex    vertex with the adjacency list
 * @param state     state to set to
 */
void DigraphSetAdjState(struct DigraphVert *vertex, unsigned char state);

/**
 * @brief
 *  Traverses breath first from the given vertex a specified amount of levels
 * and performs a function on the data of the every vertex encountered.
 *
 * @param vertex    vertex to start at
 * @param max_lvl   further level to traverse; -1 for unbound traversal
 * @param func      function to execute
 *
 * @return
 *  true  : traversed successful @n
 *  false : memory allocation failed @n
 */
bool DigraphBreathTraverse(struct DigraphVert *vertex, int max_lvl,
                           void (*func)(void *));
#endif