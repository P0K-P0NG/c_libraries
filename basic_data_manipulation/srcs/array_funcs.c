/**
 * @file array_funcs.c
 * 
 * @brief 
 *  Functions for arrays.
 * 
 * @implements
 *  array_funcs.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include <swap_funcs.h>
#include "array_funcs.h"

int getArrIdx(
    const void *value, 
    const void *arr, 
    size_t item_size, 
    int count, 
    int (*comp_func)(const void*, const void*))
{
    if(value == NULL || arr == NULL)
    {
        return -2;
    }
    /* MAIN LOGIC */

    int index = -1;
    const void *item_i = arr;
    for (int i = 0; i < count; i++)
    {
        if(comp_func(value, item_i) == 0)
        {
            index = i;
            break;
        }
        item_i += item_size;
    }
    return index;
}

void insertSortArr(
    void *arr, size_t item_size, 
    int count, int (*comp_func)(const void*, const void*))
{
    for(int i = 1; i < count; i++)
    {
        for(int j = i; j >= 1; j--)
        {
            if(comp_func(arr + (j - 1)*item_size, arr + j*item_size) >= 0)
            {
                swap(arr + (j - 1)*item_size, arr + j*item_size, item_size);
            }
            else
            {
                break;
            }
        }
    }
}