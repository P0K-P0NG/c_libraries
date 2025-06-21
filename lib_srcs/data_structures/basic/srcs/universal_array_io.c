/**
 * @file universal_array_io.c
 *
 * @brief
 *  Streaming function for the struct Array type.
 *
 * @implements
 *  universal_array_io.h
 *
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2025-06-17
 */
#include "universal_array_io.h"
#include "swap_funcs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ArrayReadBinary(Array_t **p_arr, FILE *file_src)
{
    assert(p_arr != NULL);
    assert(file_src != NULL);

    Array_t arr_info;
    if ((fread(&arr_info, sizeof(Array_t), 1, file_src)) != 1) {
        return false;
    }
    *p_arr = ArrayCreate(arr_info.item_size, arr_info.len);
    if (fread((*p_arr)->items, (*p_arr)->item_size, (*p_arr)->len, file_src)
        != (size_t)(*p_arr)->len) {
        ArrayClear(p_arr);
        return false;
    }
    return true;
}

bool ArrayWriteBinary(Array_t *arr, FILE *file_dest)
{
    assert(arr != NULL);
    assert(file_dest != NULL);

    Array_t temp
        = {.items = NULL, .item_size = arr->item_size, .len = arr->len};
    if (fwrite(&temp, sizeof(Array_t), 1, file_dest) != 1
        || fwrite(arr->items, arr->item_size, arr->len, file_dest)
               != (size_t)arr->len) {
        return false;
    }
    return true;
}

bool ArrayWrite(Array_t *arr, const char *type_format, const char *delim,
                FILE *file_dest)
{
    assert(arr != NULL);
    assert(file_dest != NULL);

    if (fprintf(file_dest, type_format, ArrayGet(arr, 0)) < 0) {
        return false;
    }
    for (int i = 1; i < arr->len; i++) {
        if (fprintf(file_dest, "%s", delim) < 0
            || fprintf(file_dest, type_format, ArrayGet(arr, i)) < 0) {
            return false;
        }
    }
    return true;
}