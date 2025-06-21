/**
 * @file linked_list_stack.c
 *
 * @brief
 *  Structs and functions for linked list stacks.
 *
 * @implements
 *  linked_list_stack.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-22
 */
#include "linked_list_stack.h"
#include <assert.h>
#include <stdlib.h>

LListStack_t *LListStackCreate()
{
    return calloc(1, sizeof(LListStack_t));
}

bool LListStackPush(LListStack_t *stack, void *data)
{
    assert(stack != NULL);

    LListStackNode_t *new_head = calloc(1, sizeof(LListStackNode_t));
    if (new_head == NULL) {
        return false;
    }

    if (stack->tail == NULL) {
        stack->tail = new_head;
    }
    new_head->next = stack->head;
    new_head->data = data;
    stack->head = new_head;
    return true;
}

void *LListStackPop(LListStack_t *stack)
{
    assert(stack != NULL);

    void *data;
    LListStackNode_t *prev_head = stack->head;
    if (prev_head == NULL) {
        return NULL;
    }
    if (prev_head == stack->tail) {
        stack->tail = NULL;
    }
    data = prev_head->data;
    stack->head = stack->head->next;
    free(prev_head);
    return data;
}

void LListStackClear(LListStack_t **p_stack, void (*free_data)(void *))
{
    assert(p_stack != NULL);
    assert(*p_stack != NULL);

    LListStackNode_t *curr = (*p_stack)->head;
    while (curr != NULL) {
        LListStackNode_t *prev = curr;
        curr = curr->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*p_stack);
    *p_stack = NULL;
}