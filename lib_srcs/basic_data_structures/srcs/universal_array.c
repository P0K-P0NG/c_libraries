/**
 * @file universal_array.c
 * 
 * @brief 
 *  Struct and functions of an universal array type.
 * 
 * @implements
 *  universal_array.h
 * 
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2025-06-17
 */
#include "universal_array.h"
#include "swap_funcs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Array *ArrayCreate(size_t item_size, size_t len)
{
    struct Array *new_arr = calloc(1, sizeof(struct Array));
    if (new_arr == NULL)
        return NULL;
    new_arr->items = calloc(len, item_size);
    if (new_arr->items == NULL) {
        free(new_arr);
        return NULL;
    }
    new_arr->item_size = item_size;
    new_arr->len = len;
    return new_arr;
}

void ArrayClear(struct Array **p_arr)
{
    assert(p_arr != NULL);
    assert(*p_arr != NULL);

    free((*p_arr)->items);
    free(*p_arr);
    *p_arr = NULL;
}

void ArraySet(struct Array *arr, size_t idx, void *item)
{
    memcpy(arr->items + idx * arr->item_size, item, arr->item_size);
}

void *ArrayGet(struct Array *arr, size_t idx)
{
    return arr->items + idx * arr->item_size;
}

bool ArrayFind(struct Array *arr, size_t *idx, const void *item,
               int (*comp_func)(const void *, const void *))
{
    assert(arr != NULL);
    assert(comp_func != NULL);

    bool is_found = false;
    const void *item_i = arr->items;
    for (int i = 0; i < arr->len; i++) {
        if (comp_func(item, item_i) == 0) {
            *idx = i;
            is_found = true;
            break;
        }
        item_i += arr->item_size;
    }
    return is_found;
}

bool ArrayInsertSort(struct Array *arr,
                     int (*comp_func)(const void *, const void *))
{
    assert(arr != NULL);
    assert(comp_func != NULL);

    byte_t *swap_buf = malloc(arr->item_size);
    if (swap_buf == NULL)
        return false;

    for (int i = 1; i < arr->len; i++) {
        for (int j = i; j >= 1; j--) {
            void *prev_item = ArrayGet(arr, j - 1);
            void *next_item = ArrayGet(arr, j);

            if (comp_func(prev_item, next_item) > 0) {
                swapBuf(prev_item, next_item, swap_buf, arr->item_size);
            } else {
                break;
            }
        }
    }
    free(swap_buf);
    return true;
}

int ArrayToInt(struct Array *arr)
{
    int result = 0;
    for (int i = 0; i < arr->len; i++) {
        result *= 10;
        result += *(int *)ArrayGet(arr, i);
    }
    return result;
}