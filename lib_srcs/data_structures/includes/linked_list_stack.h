/**
 * @file linked_list_stack.h
 *
 * @brief
 *  Structs and functions for linked list stacks.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-22
 */
#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H

#include <stdbool.h>

struct LListStackNode {          // linked list stack node
    void *data;                  // Pointer to data
    struct LListStackNode *next; // next node in the stack
};

struct LListStack {              // linked list stack
    struct LListStackNode *head; // head node
    struct LListStackNode *tail; // tail node
};

/**
 * @brief
 *  Creates a new linked list stack
 *
 * @return Pointer to the linked list stack. NULL if memory allocation failed.
 */
extern struct LListStack *LListStackCreate();

/**
 * @brief
 *  Pushes new data to a linked list stack
 *
 * @param[in,out] stack     linked list stack to push to
 * @param[in]     data      new data
 *
 * @return
 *   true  : pushed successfully @n
 *   false : unable to allocate memory @n
 */
extern bool LListStackPush(struct LListStack *stack, void *data);

/**
 * @brief
 *  Pops data from a linked list stack
 *
 * @param[in,out] stack     linked list stack to pop
 *
 * @return Pointer to the popped data, NULL if the stack is empty.
 */
extern void *LListStackPop(struct LListStack *stack);

/**
 * @brief
 *  Deletes a linked list stack and frees its data if given a function to do so.
 *
 * @param[in,out] p_stack       linked list stack to delete
 * @param[in]     free_data     function to free data, NULL if not needed
 */
extern void LListStackClear(struct LListStack **p_stack,
                            void (*free_data)(void *));
#endif