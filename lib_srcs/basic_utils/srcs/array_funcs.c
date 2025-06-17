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
#include "array_funcs.h"
#include "swap_funcs.h"
#include <assert.h>
#include <stdlib.h>

bool getArrIdx(size_t *idx, const void *value, const void *arr,
               size_t item_size, int count,
               int (*comp_func)(const void *, const void *))
{
    assert(value != NULL);
    assert(arr != NULL);
    assert(comp_func != NULL);

    bool is_found = false;
    const void *item_i = arr;
    for (size_t i = 0; i < count; i++) {
        if (comp_func(value, item_i) == 0) {
            *idx = i;
            is_found = true;
            break;
        }
        item_i += item_size;
    }
    return is_found;
}

bool insertSortArr(void *arr, size_t item_size, int count,
                   int (*comp_func)(const void *, const void *))
{
    assert(arr != NULL);
    assert(comp_func != NULL);

    byte_t *swap_buf = malloc(item_size);
    if (swap_buf == NULL)
        return false;

    for (int i = 1; i < count; i++) {
        for (int j = i; j >= 1; j--) {
            void *item1 = arr + (j - 1) * item_size;
            void *item2 = arr + j * item_size;
            if (comp_func(item1, item2) > 0) {
                swapBuf(item1, item2, swap_buf, item_size);
            } else {
                break;
            }
        }
    }
    free(swap_buf);
    return true;
}