/**
 * @file pointer_array.c
 * 
 * @brief 
 *  Struct and functions for flexible pointer array.
 * 
 * @implements 
 *  pointer_array.h
 * 
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2025-06-17
 */
#include "pointer_array.h"
#include <assert.h>
#include <stdlib.h>

struct PointerArray *PointerArrayCreate(size_t len)
{
    struct PointerArray *new_arr = calloc(1, sizeof(struct PointerArray));
    if (new_arr == NULL)
        return NULL;
    new_arr->len = len;
    new_arr->ptrs = calloc(len, sizeof(void *));
    if (new_arr->ptrs == NULL) {
        free(new_arr);
        return NULL;
    }
    return new_arr;
}
void PointerArrayClear(struct PointerArray **p_arr,
                       void (*free_data)(void *data))
{
    assert(p_arr != NULL);
    assert(*p_arr != NULL);

    if (free_data != NULL) {
        for (size_t i = 0; i < (*p_arr)->len; i++) {
            free_data((*p_arr)->ptrs[i]);
        }
    }
    free((*p_arr)->ptrs);
    free(*p_arr);
    *p_arr = NULL;
}
void *PointerArrayGet(struct PointerArray *arr, size_t idx)
{
    return (idx < arr->len) ? arr->ptrs[idx] : NULL;
}
bool PointerArraySet(struct PointerArray *arr, size_t idx, void *data,
                     void (*free_data)(void *data))
{
    if (idx < arr->len) {
        if (free_data != NULL && arr->ptrs[idx] != NULL)
            free_data(arr->ptrs[idx]);
        arr->ptrs[idx] = data;
        return true;
    } else {
        return false;
    }
}