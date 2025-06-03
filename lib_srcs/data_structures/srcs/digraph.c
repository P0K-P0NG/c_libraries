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
#include <stdlib.h>

/**
 * LOCAL FUNTION DECLARATIONS
 *
 * These function aren't defined outside of this source file and are not
 * intended to be acessed directly.
 */
static void _freeVert(void *vert);
static void _resetVert(struct DigraphVert *vert);
static bool _enqueueVert(struct DigraphVert *vert, int lvl,
                         struct LListQueue *queue,
                         struct LListQueue *verts_passed);

struct DigraphVert *DigraphInitVert(void *data)
{
    struct DigraphVert *new_vert = calloc(1, sizeof(struct DigraphVert));
    if (new_vert == NULL) {
        return NULL;
    }
    new_vert->data = data;
    return new_vert;
}

bool DigraphRemoveVert(struct DigraphVert **p_vert, void (*free_data)(void *))
{
    if (p_vert == NULL) {
        return false;
    }
    if (free_data != NULL) {
        free_data((*p_vert)->data);
    }

    // remove references
    struct DLListNode *ref_node = (*p_vert)->ref_list.head;
    while (ref_node != NULL) {
        struct DLListNode *vert_ref
            = DLListFind(&((struct DigraphVert *)ref_node->data)->adj_list,
                         *p_vert, compPtr);
        DLListRemove(&((struct DigraphVert *)ref_node->data)->adj_list,
                     vert_ref, NULL);
        ref_node = ref_node->next;
    }
    _freeVert(*p_vert);
    *p_vert = NULL;
    return true;
}

bool DigraphConnect(struct DigraphVert *start, struct DigraphVert *end)
{
    struct DLListNode *end_ref = DLListAddHead(&start->adj_list, end);
    if (end_ref == NULL) {
        return false;
    }
    struct DLListNode *start_ref = DLListAddHead(&end->ref_list, start);
    if (start_ref == NULL) {
        DLListRemove(&start->adj_list, end_ref, NULL);
        return false;
    }
    return true;
}

bool DigraphDisconnect(struct DigraphVert *start, struct DigraphVert *end)
{
    struct DLListNode *connection = DLListFind(&start->adj_list, end, compPtr);
    struct DLListNode *reference = DLListFind(&end->ref_list, start, compPtr);
    if (connection == NULL || reference == NULL) {
        return false;
    }
    DLListRemove(&start->adj_list, connection, NULL);
    DLListRemove(&end->ref_list, reference, NULL);
    return true;
}

bool DigraphIsConnected(struct DigraphVert *start, struct DigraphVert *end)
{
    struct DLListNode *connection = DLListFind(&start->adj_list, end, compPtr);
    if (connection == NULL) {
        return false;
    }
    return true;
}

void DigraphTraverseAdj(struct DigraphVert *vert, void (*func)(void *))
{
    struct DLListNode *curr_node = vert->adj_list.head;
    while (curr_node != NULL) {
        func(((struct DigraphVert *)curr_node->data)->data);
        curr_node = curr_node->next;
    }
}

bool DigraphBreathTraverse(struct DigraphVert *start, int max_lvl,
                           void (*func)(void *))
{
    int curr_lvl = 0;
    if (max_lvl < 0) {
        curr_lvl = max_lvl;
    }
    struct LListQueue *queue = LListQueueCreate();
    if (queue == NULL) {
        return false;
    }
    struct LListQueue *verts_passed = LListQueueCreate();
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
    struct DigraphVert *curr_vert;
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

    struct DigraphVert *passed_vert;
    while ((passed_vert = LListQueueDequeue(verts_passed)) != NULL) {
        _resetVert(passed_vert);
    }
    return true;
}

static bool _enqueueVert(struct DigraphVert *vert, int lvl,
                         struct LListQueue *queue,
                         struct LListQueue *verts_passed)
{
    struct DLListNode *curr_node = vert->adj_list.head;
    while (curr_node != NULL) {
        ((struct DigraphVert *)curr_node->data)->lvl = lvl;
        if (LListQueueEnqueue(queue, curr_node->data) == 0
            || LListQueueEnqueue(verts_passed, curr_node->data) == 0) {
            return false;
        }
        curr_node = curr_node->next;
    }
    return true;
}

void DigraphSetAdjState(struct DigraphVert *vert, unsigned char state)
{
    struct DLListNode *curr_node = vert->adj_list.head;
    while (curr_node != NULL) {
        ((struct DigraphVert *)curr_node->data)->state = state;
        curr_node = curr_node->next;
    }
}

static void _resetVert(struct DigraphVert *vert)
{
    vert->state = 0;
    vert->lvl = 0;
}

static void _freeVert(void *vert)
{
    DLListRemoveAll(&((struct DigraphVert *)vert)->adj_list, NULL);
    DLListRemoveAll(&((struct DigraphVert *)vert)->ref_list, NULL);
    free(vert);
    vert = NULL;
}