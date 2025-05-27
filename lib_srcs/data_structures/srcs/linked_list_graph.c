/**
 * @file linked_list_graph.c
 *
 * @brief
 *  Structs and functions for linked list graphs.
 *
 * @implements
 *  linked_list_graph.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-21
 */
#include "linked_list_graph.h"
#include "comp_funcs.h"
#include "doubly_linked_list.h"
#include "linked_list_queue.h"
#include <stdlib.h>

/**
 * LOCAL FUNTION DECLARATIONS
 */
static void _freeVert(void *vert);

LListGraph *LListGraphCreate() { return DLListCreate(); }

void LListGraphClear(LListGraph **graph, void (*free_data)(void *))
{
    struct DLListNode *curr_node = (*graph)->head;
    while (curr_node != NULL) {
        struct DLListNode *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL) {
            free_data(((struct GraphVert *)prev->data)->data);
        }
        _freeVert(prev->data);
        free(prev);
    }
    free(*graph);
    *graph = NULL;
}

LListGraphNode *LListGraphAdd(LListGraph *graph, void *data)
{
    struct GraphVert *new_vert = GraphInitVert(data);
    struct DLListNode *new_node = DLListAddHead(graph, new_vert);
    if (new_node == NULL) {
        free(new_vert);
        return NULL;
    }
    return new_node;
}

int LListGraphRemove(LListGraph *graph, struct DLListNode *vert_node,
                     void (*free_data)(void *))
{
    if (vert_node == NULL) {
        return 0;
    }
    if (!GraphRemoveVert(vert_node->data, free_data)) {
        return 0;
    }
    DLListRemove(graph, vert_node, NULL);
    return 1;
}

int LListGraphConnect(struct GraphVert *start, struct GraphVert *end)
{
    return GraphConnect(start, end);
}

int LListGraphDisconnect(struct GraphVert *start, struct GraphVert *end)
{
    return GraphDisconnect(start, end);
}

LListGraphNode *LListGraphFindNode(LListGraph *graph, const void *key,
                                   int (*comp_func)(const void *, const void *))
{
    struct DLListNode *curr_node = graph->head;
    while (curr_node != NULL
           && comp_func(((struct GraphVert *)curr_node->data)->data, key)
                  != 0) {
        curr_node = curr_node->next;
    }
    return curr_node;
}

int LListGraphIsConnected(struct GraphVert *start, struct GraphVert *end)
{
    return GraphIsConnected(start, end);
}

void LListGraphTraverseAll(LListGraph *graph, void (*func)(void *))
{
    struct DLListNode *curr_node = graph->head;
    while (curr_node != NULL) {
        func(((struct GraphVert *)curr_node->data)->data);
        curr_node = curr_node->next;
    }
}

void LListGraphTraverseAdj(struct GraphVert *vert, void (*func)(void *))
{
    GraphTraverseAdj(vert, func);
}

int LListGraphBreathTraverse(struct GraphVert *start, int max_lvl,
                             void (*func)(void *))
{
    return GraphBreathTraverse(start, max_lvl, func);
}

void LListGraphSetAdjState(struct GraphVert *vert, unsigned char state)
{
    GraphSetAdjState(vert, state);
}

static void _freeVert(void *vert)
{
    DLListRemoveAll(&((struct GraphVert *)vert)->adj_list, NULL);
    DLListRemoveAll(&((struct GraphVert *)vert)->ref_list, NULL);
    free(vert);
    vert = NULL;
}