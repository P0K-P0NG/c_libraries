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
#include "swap_funcs.h"
#include <stdlib.h>
#include <string.h>

bool swap(void *ptr1, void *ptr2, size_t size)
{
    byte_t *temp = malloc(size);
    if (temp == NULL)
        return false;
    memcpy(temp, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, temp, size);
    free(temp);
    return true;
}

bool swapBuf(void *ptr1, void *ptr2, void *buf, size_t size)
{
    memcpy(buf, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, buf, size);
}