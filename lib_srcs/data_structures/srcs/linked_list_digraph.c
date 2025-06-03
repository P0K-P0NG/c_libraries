/**
 * @file linked_list_digraph.c
 *
 * @brief
 *  Structs and functions for linked list graphs.
 *
 * @implements
 *  linked_list_digraph.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-21
 */
#include "linked_list_digraph.h"
#include "comp_funcs.h"
#include "doubly_linked_list.h"
#include "linked_list_queue.h"
#include <stdlib.h>

/**
 * LOCAL FUNTION DECLARATIONS
 */
static void _freeVert(void *vert);

LListDigraph *LListDigraphCreate() { return DLListCreate(); }

void LListDigraphClear(LListDigraph **graph, void (*free_data)(void *))
{
    struct DLListNode *curr_node = (*graph)->head;
    while (curr_node != NULL) {
        struct DLListNode *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL) {
            free_data(((struct DigraphVert *)prev->data)->data);
        }
        _freeVert(prev->data);
        free(prev);
    }
    free(*graph);
    *graph = NULL;
}

LListDigraphNode *LListDigraphAdd(LListDigraph *graph, void *data)
{
    struct DigraphVert *new_vert = DigraphInitVert(data);
    struct DLListNode *new_node = DLListAddHead(graph, new_vert);
    if (new_node == NULL) {
        free(new_vert);
        return NULL;
    }
    return new_node;
}

bool LListDigraphRemove(LListDigraph *graph, struct DLListNode *vert_node,
                        void (*free_data)(void *))
{
    if (vert_node == NULL) {
        return false;
    }
    if (!DigraphRemoveVert(vert_node->data, free_data)) {
        return false;
    }
    DLListRemove(graph, vert_node, NULL);
    return true;
}

bool LListDigraphConnect(struct DigraphVert *start, struct DigraphVert *end)
{
    return DigraphConnect(start, end);
}

bool LListDigraphDisconnect(struct DigraphVert *start, struct DigraphVert *end)
{
    return DigraphDisconnect(start, end);
}

LListDigraphNode *LListDigraphFindNode(LListDigraph *graph, const void *key,
                                       int (*comp_func)(const void *,
                                                        const void *))
{
    struct DLListNode *curr_node = graph->head;
    while (curr_node != NULL
           && comp_func(((struct DigraphVert *)curr_node->data)->data, key)
                  != 0) {
        curr_node = curr_node->next;
    }
    return curr_node;
}

bool LListDigraphIsConnected(struct DigraphVert *start, struct DigraphVert *end)
{
    return DigraphIsConnected(start, end);
}

void LListDigraphTraverseAll(LListDigraph *graph, void (*func)(void *))
{
    struct DLListNode *curr_node = graph->head;
    while (curr_node != NULL) {
        func(((struct DigraphVert *)curr_node->data)->data);
        curr_node = curr_node->next;
    }
}

void LListDigraphTraverseAdj(struct DigraphVert *vert, void (*func)(void *))
{
    DigraphTraverseAdj(vert, func);
}

bool LListDigraphBreathTraverse(struct DigraphVert *start, int max_lvl,
                                void (*func)(void *))
{
    return DigraphBreathTraverse(start, max_lvl, func);
}

void LListDigraphSetAdjState(struct DigraphVert *vert, unsigned char state)
{
    DigraphSetAdjState(vert, state);
}

static void _freeVert(void *vert)
{
    DLListRemoveAll(&((struct DigraphVert *)vert)->adj_list, NULL);
    DLListRemoveAll(&((struct DigraphVert *)vert)->ref_list, NULL);
    free(vert);
    vert = NULL;
}