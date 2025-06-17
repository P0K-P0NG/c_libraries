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

#include <stdbool.h>
#include <stddef.h>

typedef unsigned char byte_t;

/**
 * @brief
 *  Swaps the contents in two pointers
 *
 * @param[in,out] ptr1  pointer 1
 * @param[in,out] ptr2  pointer 2
 * @param[in]     size  size of the content in bytes
 *
 * @return
 *  true  : success
 *  false : memory allocation failed
 */
extern bool swap(void *ptr1, void *ptr2, size_t size);

/**
 * @brief
 *  Swaps the contents in two pointers using the given buffer
 *
 * @param[in,out] ptr1  pointer 1
 * @param[in,out] ptr2  pointer 2
 * @param[in]     buf   buffer used to hold data temporarily
 * @param[in]     size  size of the content in bytes
 *
 * @return
 *  true  : success
 *  false : memory allocation failed
 */
extern bool swapBuf(void *ptr1, void *ptr2, void *buf, size_t size);
#endif