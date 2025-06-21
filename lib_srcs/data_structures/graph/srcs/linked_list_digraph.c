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
#include "_extend_doubly_linked_list.h"
#include "comp_funcs.h"
#include "doubly_linked_list.h"
#include "linked_list_queue.h"
#include <stdlib.h>

// No need for asserts since the modules it calls include asserts already

/**
 * LOCAL FUNTION DECLARATIONS
 */
static void _freeVert(void *vert);
static void *_extractVertData(void *vert_node);

DLList_t *LListDigraphCreate() { return DLListCreate(); }

void LListDigraphClear(DLList_t **graph, void (*free_data)(void *))
{
    DLListNode_t *curr_node = (*graph)->head;
    while (curr_node != NULL) {
        DLListNode_t *prev = curr_node;
        curr_node = curr_node->next;
        if (free_data != NULL) {
            free_data(((DigraphVert_t *)prev->data)->data);
        }
        _freeVert(prev->data);
        free(prev);
    }
    free(*graph);
    *graph = NULL;
}

DLListNode_t *LListDigraphAdd(DLList_t *graph, void *data)
{
    DigraphVert_t *new_vert = DigraphInitVert(data);
    DLListNode_t *new_node = DLListAddHead(graph, new_vert);
    if (new_node == NULL) {
        free(new_vert);
        return NULL;
    }
    return new_node;
}

bool LListDigraphRemove(DLList_t *graph, DLListNode_t *vert_node,
                        void (*free_data)(void *))
{
    if (!DigraphRemoveVert((DigraphVert_t **)&vert_node->data,
                           free_data)) {
        return false;
    }
    DLListRemove(graph, vert_node, NULL);
    return true;
}

bool LListDigraphConnect(DLListNode_t *start, DLListNode_t *end)
{
    return DigraphConnect((DigraphVert_t *)start->data,
                          (DigraphVert_t *)end->data);
}

bool LListDigraphDisconnect(DLListNode_t *start, DLListNode_t *end)
{
    return DigraphConnect((DigraphVert_t *)start->data,
                          (DigraphVert_t *)end->data);
}

bool LListDigraphIsConnected(DLListNode_t *start, DLListNode_t *end)
{
    return DigraphConnect((DigraphVert_t *)start->data,
                          (DigraphVert_t *)end->data);
}

DLListNode_t *LListDigraphFind(DLList_t *graph, const void *key,
                                    int (*comp_func)(const void *,
                                                     const void *))
{
    DLListNode_t *curr_node = graph->head;
    while (curr_node != NULL
           && comp_func(((DigraphVert_t *)curr_node->data)->data, key)
                  != 0) {
        curr_node = curr_node->next;
    }
    return curr_node;
}

void LListDigraphTraverseAll(DLList_t *graph, void (*func)(void *))
{
    _extend_DLListTraverse(graph, _extractVertData, func);
}

static void *_extractVertData(void *vert)
{
    return ((DigraphVert_t *)vert)->data;
}

void LListDigraphTraverseAdj(DLListNode_t *vert_node, void (*func)(void *))
{
    DigraphTraverseAdj((DigraphVert_t *)vert_node->data, func);
}

bool LListDigraphBreathTraverse(DLListNode_t *start, int max_lvl,
                                void (*func)(void *))
{
    return DigraphBreathTraverse((DigraphVert_t *)start->data, max_lvl,
                                 func);
}

void LListDigraphSetAdjState(DLListNode_t *vert_node, unsigned char state)
{
    DigraphSetAdjState((DigraphVert_t *)vert_node->data, state);
}

static void _freeVert(void *vert)
{
    DLListRemoveAll(&((DigraphVert_t *)vert)->adj_list, NULL);
    DLListRemoveAll(&((DigraphVert_t *)vert)->ref_list, NULL);
    free(vert);
    vert = NULL;
}