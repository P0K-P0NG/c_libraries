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
#include <stdlib.h>
#include "comp_funcs.h"
#include "linked_list_queue.h"
#include "doubly_linked_list.h"
#include "linked_list_graph.h"

/**
 * LOCAL FUNTION DECLARATIONS
 *
 * These function aren't defined outside of this source file and are not intended to be acessed directly.
 */
static void freeVert(void *vert);
static void resetVert(GraphVert *vert);
static int enqueueVert(
    GraphVert *vert, int lvl, LListQueue *queue, LListQueue *verts_passed);

GraphVert *GraphInitVert(void *data)
{
    GraphVert *new_vert = calloc(1, sizeof(GraphVert));
    if (new_vert == NULL)
    {
        return NULL;
    }
    new_vert->data = data;
    return new_vert;
}

int GraphRemoveVert(GraphVert **p_vert, void (*free_data)(void *))
{
    if (p_vert == NULL)
    {
        return 0;
    }
    if (free_data != NULL)
    {
        free_data((*p_vert)->data);
    }
    
    // remove references
    DLListNode *ref_node = (*p_vert)->ref_list.head;
    while (ref_node != NULL)
    {
        DLListNode *vert_ref = DLListFind(
            &((GraphVert *)ref_node->data)->adj_list, *p_vert, compPtr);
        DLListRemove(
            &((GraphVert *)ref_node->data)->adj_list, vert_ref, NULL);
        ref_node = ref_node->next;
    }
    freeVert(*p_vert);
    *p_vert = NULL;
    return 1;
}

int GraphConnect(GraphVert *start, GraphVert *end)
{
    DLListNode *end_ref = DLListAddHead(&start->adj_list, end);
    if (end_ref == NULL)
    {
        return 0;
    }
    DLListNode *start_ref = DLListAddHead(&end->ref_list, start);
    if (start_ref == NULL)
    {
        DLListRemove(&start->adj_list, end_ref, NULL);
        return 0;
    }
    return 1;
}

int GraphDisconnect(GraphVert *start, GraphVert *end)
{
    DLListNode *connection = DLListFind(
        &start->adj_list, end, compPtr);
    DLListNode *reference = DLListFind(
        &end->ref_list, start, compPtr);
    if (connection == NULL || reference == NULL)
    {
        return 0;
    }
    DLListRemove(&start->adj_list, connection, NULL);
    DLListRemove(&end->ref_list, reference, NULL);
    return 1;
}

int GraphIsConnected(GraphVert *start, GraphVert *end)
{
    DLListNode *connection = DLListFind(
        &start->adj_list, end, compPtr);
    if (connection == NULL)
    {
        return 0;
    }
    return 1;
}

void GraphTraverseAdj(GraphVert *vert, void (*func)(void *))
{
    DLListNode *curr_node = vert->adj_list.head;
    while (curr_node != NULL)
    {
        func(((GraphVert *)curr_node->data)->data);
        curr_node = curr_node->next;
    }
}

int GraphBreathTraverse(
    GraphVert *start, int max_lvl, void (*func)(void *))
{
    int curr_lvl = 0;
    if (max_lvl < 0)
    {
        curr_lvl = max_lvl;
    }
    LListQueue *queue = LListQueueCreate();
    if (queue == NULL)
    {
        return 0;
    }
    LListQueue *verts_passed = LListQueueCreate();
    if (verts_passed == NULL)
    {
        LListQueueClear(&queue, NULL);
        return 0;
    }

    if (LListQueueEnqueue(queue, start) == 0)
    {
        LListQueueClear(&queue, NULL);
        LListQueueClear(&verts_passed, NULL);
        return 0;
    }
    start->lvl = curr_lvl;
    GraphVert *curr_vert;
    while ((curr_vert = LListQueueDequeue(queue)) != NULL)
    {
        if (curr_vert->state == 0)
        {
            func(curr_vert->data);
        }

        if (max_lvl >= 0)
        {
            curr_lvl = curr_vert->lvl + 1;
        }
        if (curr_vert->state != 1 && curr_lvl <= max_lvl)
        {
            if(!enqueueVert(curr_vert, curr_lvl, queue, verts_passed))
            {
                LListQueueClear(&queue, NULL);
                LListQueueClear(&verts_passed, NULL);
                return 0;
            }
        }
        curr_vert->state = 1;
    }

    GraphVert *passed_vert;
    while ((passed_vert = LListQueueDequeue(verts_passed)) != NULL)
    {
        resetVert(passed_vert);
    }
    return 1;
}

static int enqueueVert(
    GraphVert *vert, int lvl, LListQueue *queue, LListQueue *verts_passed)
{
    DLListNode *curr_node = vert->adj_list.head;
    while (curr_node != NULL)
    {
        ((GraphVert *)curr_node->data)->lvl = lvl;
        if (LListQueueEnqueue(queue, curr_node->data) == 0 ||
            LListQueueEnqueue(verts_passed, curr_node->data) == 0)
        {
            return 0;
        }
        curr_node = curr_node->next;
    }
    return 1;
}

void GraphSetAdjState(GraphVert *vert, unsigned char state)
{
    DLListNode *curr_node = vert->adj_list.head;
    while (curr_node != NULL)
    {
        ((GraphVert *)curr_node->data)->state = state;
        curr_node = curr_node->next;
    }
}

static void resetVert(GraphVert *vert)
{
    vert->state = 0;
    vert->lvl = 0;
}

static void freeVert(void *vert)
{
    DLListRemoveAll(&((GraphVert *)vert)->adj_list, NULL);
    DLListRemoveAll(&((GraphVert *)vert)->ref_list, NULL);
    free(vert);
    vert = NULL;
}