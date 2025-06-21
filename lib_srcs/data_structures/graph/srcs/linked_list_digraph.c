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

struct DLList *LListDigraphCreate() { return DLListCreate(); }

void LListDigraphClear(struct DLList **graph, void (*free_data)(void *))
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

struct DLListNode *LListDigraphAdd(struct DLList *graph, void *data)
{
    struct DigraphVert *new_vert = DigraphInitVert(data);
    struct DLListNode *new_node = DLListAddHead(graph, new_vert);
    if (new_node == NULL) {
        free(new_vert);
        return NULL;
    }
    return new_node;
}

bool LListDigraphRemove(struct DLList *graph, struct DLListNode *vert_node,
                        void (*free_data)(void *))
{
    if (!DigraphRemoveVert((struct DigraphVert **)&vert_node->data,
                           free_data)) {
        return false;
    }
    DLListRemove(graph, vert_node, NULL);
    return true;
}

bool LListDigraphConnect(struct DLListNode *start, struct DLListNode *end)
{
    return DigraphConnect((struct DigraphVert *)start->data,
                          (struct DigraphVert *)end->data);
}

bool LListDigraphDisconnect(struct DLListNode *start, struct DLListNode *end)
{
    return DigraphConnect((struct DigraphVert *)start->data,
                          (struct DigraphVert *)end->data);
}

bool LListDigraphIsConnected(struct DLListNode *start, struct DLListNode *end)
{
    return DigraphConnect((struct DigraphVert *)start->data,
                          (struct DigraphVert *)end->data);
}

struct DLListNode *LListDigraphFind(struct DLList *graph, const void *key,
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

void LListDigraphTraverseAll(struct DLList *graph, void (*func)(void *))
{
    _extend_DLListTraverse(graph, _extractVertData, func);
}

static void *_extractVertData(void *vert)
{
    return ((struct DigraphVert *)vert)->data;
}

void LListDigraphTraverseAdj(struct DLListNode *vert_node, void (*func)(void *))
{
    DigraphTraverseAdj((struct DigraphVert *)vert_node->data, func);
}

bool LListDigraphBreathTraverse(struct DLListNode *start, int max_lvl,
                                void (*func)(void *))
{
    return DigraphBreathTraverse((struct DigraphVert *)start->data, max_lvl,
                                 func);
}

void LListDigraphSetAdjState(struct DLListNode *vert_node, unsigned char state)
{
    DigraphSetAdjState((struct DigraphVert *)vert_node->data, state);
}

static void _freeVert(void *vert)
{
    DLListRemoveAll(&((struct DigraphVert *)vert)->adj_list, NULL);
    DLListRemoveAll(&((struct DigraphVert *)vert)->ref_list, NULL);
    free(vert);
    vert = NULL;
}