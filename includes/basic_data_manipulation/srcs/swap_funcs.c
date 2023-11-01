/**
 * @file swap_funcs.c
 * 
 * @brief 
 *  Functions for swaping data.
 * 
 * @implements
 *  swap_funcs.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include <string.h>
#include "swap_funcs.h"

void swap(void *ptr1, void *ptr2, size_t size)
{
    byte_t temp[size];
    memcpy(temp, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, temp, size);
}