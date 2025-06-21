/**
 * @file doubly_linked_list.h
 *
 * @brief
 *  functions for extending the doubly linked list implementation.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-03-20
 */
#ifndef _EXTEND_DOUBLY_LINKED_LIST_H
#define _EXTEND_DOUBLY_LINKED_LIST_H

#include "doubly_linked_list.h"

/**
 * @brief
 *  Traverses through a doubly linked list head to tail and preforms a given
 *  function on all its an extract section of data.
 *
 * @param[in,out] list          doubly linked list to traverse
 * @param[in]     extract_func  funcdtion to extract the appropriate data
 * @param[in]     func          function to preform on data
 */
extern void _extend_DLListTraverse(struct DLList *list,
                                   void *(*extract_func)(void *),
                                   void (*func)(void *));
#endif