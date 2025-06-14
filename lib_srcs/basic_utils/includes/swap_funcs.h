/**
 * @file swap_funcs.h
 *
 * @brief
 *  Functions for swaping data.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#ifndef SWAP_FUNCS_H
#define SWAP_FUNCS_H

#include <stddef.h>

typedef unsigned char byte_t;

/**
 * @brief
 *  Swaps the contents in two pointers
 *
 * @param[in] ptr1  pointer 1
 * @param[in] ptr2  pointer 2
 * @param[in] size  size of the content in bytes
 */
extern void swap(void *ptr1, void *ptr2, size_t size);
#endif