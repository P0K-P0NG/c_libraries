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

struct LListStack *LListStackCreate()
{
    return calloc(1, sizeof(struct LListStack));
}

bool LListStackPush(struct LListStack *stack, void *data)
{
    assert(stack != NULL);

    struct LListStackNode *new_head = calloc(1, sizeof(struct LListStackNode));
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

void *LListStackPop(struct LListStack *stack)
{
    assert(stack != NULL);

    void *data;
    struct LListStackNode *prev_head = stack->head;
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

void LListStackClear(struct LListStack **p_stack, void (*free_data)(void *))
{
    assert(p_stack != NULL);
    assert(*p_stack != NULL);

    struct LListStackNode *curr = (*p_stack)->head;
    while (curr != NULL) {
        struct LListStackNode *prev = curr;
        curr = curr->next;
        if (free_data != NULL) {
            free_data(prev->data);
        }
        free(prev);
    }
    free(*p_stack);
    *p_stack = NULL;
}