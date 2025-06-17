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

/**
 * @brief
 *  Creates a digraph vertex;
 *
 * @param[in] data  data to store
 *
 * @return Pointer to new digraph vertex
 */
extern struct DigraphVert *DigraphInitVert(void *data);

/**
 * @brief
 *  Deletes a digraph vertex.
 *
 * @param[in,out] p_vert        vertex to delete
 * @param[in]     free_data     function to free the data, NULL if not needed
 *
 * @return true  : removal successful 
 * @return false : memory allocation failed
 */
extern bool DigraphRemoveVert(struct DigraphVert **p_vert,
                              void (*free_data)(void *));

/**
 * @brief
 *  Creates a directional edge from the first vertex to the second.
 *
 * @param[in,out] start     vertex the edge starts at
 * @param[in,out] end       vertex the edge ends at
 *
 * @return true  : connection successful 
 * @return false : memory allocation failed
 */
extern bool DigraphConnect(struct DigraphVert *start, struct DigraphVert *end);

/**
 * @brief
 *  Removes a directional edge from the first vertex to the second.
 *
 * @param[in,out] start     vertex the edge starts at
 * @param[in,out] end       vertex the edge ends at
 *
 * @return true  : disconnection successful 
 * @return false : no edge found
 */
extern bool DigraphDisconnect(struct DigraphVert *start,
                              struct DigraphVert *end);

/**
 * @brief
 *  Checks if an edge from the first vertex to the second exists or not.
 *
 * @param[in,out] start     vertex the edge starts at
 * @param[in,out] end       vertex the edge ends at
 *
 * @return true  : an edge exist 
 * @return false : an edge doesn't exit
 */
extern bool DigraphIsConnected(struct DigraphVert *start,
                               struct DigraphVert *end);

/**
 * @brief
 *  Performs a given function on the data of all the vertices adjacent to the
 *  one passed.
 *
 * @param[in,out] vert      vertex with the adjacency list
 * @param[in]     func      function to execute
 */
extern void DigraphTraverseAdj(struct DigraphVert *vert, void (*func)(void *));

/**
 * @brief
 *  Sets the state of all the vertices adjacent to the one passed.
 *
 * @param[in,out] vert      vertex with the adjacency list
 * @param[in]     state     state to set to
 */
extern void DigraphSetAdjState(struct DigraphVert *vert, unsigned char state);

/**
 * @brief
 *  Traverses breath first from the given vertex a specified amount of levels
 *  and performs a function on the data of the every vertex encountered.
 *
 * @param[in,out] vert      vertex to start at
 * @param[in]     max_lvl   further level to traverse; -1 for unbound traversal
 * @param[in]     func      function to execute
 *
 * @return true  : traversal successful 
 * @return false : memory allocation failed
 */
extern bool DigraphBreathTraverse(struct DigraphVert *vert, int max_lvl,
                                  void (*func)(void *));
#endif