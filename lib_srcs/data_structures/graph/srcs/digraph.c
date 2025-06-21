/**
 * @file digraph.c
 *
 * @brief
 *  Structs and functions for linked list digraphs.
 *
 * @implements
 *  digraph.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-21
 */
#include "digraph.h"
#include "comp_funcs.h"
#include "doubly_linked_list.h"
#include "linked_list_queue.h"
#include <assert.h>
#include <stdlib.h>

/**
 * LOCAL FUNTION DECLARATIONS
 *
 * These function aren't defined outside of this source file and are not
 * intended to be acessed directly.
 */
static void _freeVert(void *vert);
static void _resetVert(DigraphVert_t *vert);
static bool _enqueueVert(DigraphVert_t *vert, int lvl,
                         LListQueue_t *queue,
                         LListQueue_t *verts_passed);

DigraphVert_t *DigraphInitVert(void *data)
{
    DigraphVert_t *new_vert = calloc(1, sizeof(DigraphVert_t));
    if (new_vert == NULL) {
        return NULL;
    }
    new_vert->data = data;
    return new_vert;
}

bool DigraphRemoveVert(DigraphVert_t **p_vert, void (*free_data)(void *))
{
    assert(p_vert != NULL);
    assert(*p_vert != NULL);

    if (free_data != NULL) {
        free_data((*p_vert)->data);
    }

    // remove references
    DLListNode_t *ref_node = (*p_vert)->ref_list.head;
    while (ref_node != NULL) {
        DLListNode_t *vert_ref
            = DLListFind(&((DigraphVert_t *)ref_node->data)->adj_list,
                         *p_vert, compPtr);
        DLListRemove(&((DigraphVert_t *)ref_node->data)->adj_list,
                     vert_ref, NULL);
        ref_node = ref_node->next;
    }
    _freeVert(*p_vert);
    *p_vert = NULL;
    return true;
}

bool DigraphConnect(DigraphVert_t *start, DigraphVert_t *end)
{
    assert(start != NULL);
    assert(end != NULL);

    DLListNode_t *end_ref = DLListAddHead(&start->adj_list, end);
    if (end_ref == NULL) {
        return false;
    }
    DLListNode_t *start_ref = DLListAddHead(&end->ref_list, start);
    if (start_ref == NULL) {
        DLListRemove(&start->adj_list, end_ref, NULL);
        return false;
    }
    return true;
}

bool DigraphDisconnect(DigraphVert_t *start, DigraphVert_t *end)
{
    assert(start != NULL);
    assert(end != NULL);

    DLListNode_t *connection = DLListFind(&start->adj_list, end, compPtr);
    DLListNode_t *reference = DLListFind(&end->ref_list, start, compPtr);
    if (connection == NULL || reference == NULL) {
        return false;
    }
    DLListRemove(&start->adj_list, connection, NULL);
    DLListRemove(&end->ref_list, reference, NULL);
    return true;
}

bool DigraphIsConnected(DigraphVert_t *start, DigraphVert_t *end)
{
    assert(start != NULL);
    assert(end != NULL);

    DLListNode_t *connection = DLListFind(&start->adj_list, end, compPtr);
    if (connection == NULL) {
        return false;
    }
    return true;
}

void DigraphTraverseAdj(DigraphVert_t *vert, void (*func)(void *))
{
    assert(vert != NULL);
    assert(func != NULL);

    DLListNode_t *curr_node = vert->adj_list.head;
    while (curr_node != NULL) {
        func(((DigraphVert_t *)curr_node->data)->data);
        curr_node = curr_node->next;
    }
}

bool DigraphBreathTraverse(DigraphVert_t *start, int max_lvl,
                           void (*func)(void *))
{
    assert(start != NULL);
    assert(func != NULL);

    int curr_lvl = 0;
    if (max_lvl < 0) {
        curr_lvl = max_lvl;
    }
    LListQueue_t *queue = LListQueueCreate();
    if (queue == NULL) {
        return false;
    }
    LListQueue_t *verts_passed = LListQueueCreate();
    if (verts_passed == NULL) {
        LListQueueClear(&queue, NULL);
        return false;
    }

    if (LListQueueEnqueue(queue, start) == 0) {
        LListQueueClear(&queue, NULL);
        LListQueueClear(&verts_passed, NULL);
        return false;
    }
    start->lvl = curr_lvl;
    DigraphVert_t *curr_vert;
    while ((curr_vert = LListQueueDequeue(queue)) != NULL) {
        if (curr_vert->state == 0) {
            func(curr_vert->data);
        }

        if (max_lvl >= 0) {
            curr_lvl = curr_vert->lvl + 1;
        }
        if (curr_vert->state != 1 && curr_lvl <= max_lvl) {
            if (!_enqueueVert(curr_vert, curr_lvl, queue, verts_passed)) {
                LListQueueClear(&queue, NULL);
                LListQueueClear(&verts_passed, NULL);
                return false;
            }
        }
        curr_vert->state = 1;
    }

    DigraphVert_t *passed_vert;
    while ((passed_vert = LListQueueDequeue(verts_passed)) != NULL) {
        _resetVert(passed_vert);
    }
    return true;
}

static bool _enqueueVert(DigraphVert_t *vert, int lvl,
                         LListQueue_t *queue,
                         LListQueue_t *verts_passed)
{
    DLListNode_t *curr_node = vert->adj_list.head;
    while (curr_node != NULL) {
        ((DigraphVert_t *)curr_node->data)->lvl = lvl;
        if (LListQueueEnqueue(queue, curr_node->data) == 0
            || LListQueueEnqueue(verts_passed, curr_node->data) == 0) {
            return false;
        }
        curr_node = curr_node->next;
    }
    return true;
}

void DigraphSetAdjState(DigraphVert_t *vert, unsigned char state)
{
    DLListNode_t *curr_node = vert->adj_list.head;
    while (curr_node != NULL) {
        ((DigraphVert_t *)curr_node->data)->state = state;
        curr_node = curr_node->next;
    }
}

static void _resetVert(DigraphVert_t *vert)
{
    vert->state = 0;
    vert->lvl = 0;
}

static void _freeVert(void *vert)
{
    DLListRemoveAll(&((DigraphVert_t *)vert)->adj_list, NULL);
    DLListRemoveAll(&((DigraphVert_t *)vert)->ref_list, NULL);
    free(vert);
    vert = NULL;
}