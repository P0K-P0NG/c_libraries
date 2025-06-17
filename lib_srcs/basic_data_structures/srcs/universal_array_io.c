#include "universal_array_io.h"
#include "swap_funcs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ArrayReadBinary(struct Array **p_arr, FILE *file_src)
{
    assert(p_arr != NULL);
    assert(file_src != NULL);

    struct Array arr_info;
    if ((fread(&arr_info, sizeof(struct Array), 1, file_src)) != 1) {
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

bool ArrayWriteBinary(struct Array *arr, FILE *file_dest)
{
    assert(arr != NULL);
    assert(file_dest != NULL);

    struct Array temp
        = {.items = NULL, .item_size = arr->item_size, .len = arr->len};
    if (fwrite(&temp, sizeof(struct Array), 1, file_dest) != 1
        || fwrite(arr->items, arr->item_size, arr->len, file_dest)
               != (size_t)arr->len) {
        return false;
    }
    return true;
}

bool ArrayWrite(struct Array *arr, char type[TYPE_LEN], char *delim,
                FILE *file_dest)
{
    assert(arr != NULL);
    assert(file_dest != NULL);

    if (fprintf(file_dest, type, ArrayGet(arr, 0)) < 0) {
        return false;
    }
    for (int i = 1; i < arr->len; i++) {
        if (fprintf(file_dest, "%s", delim) < 0
            || fprintf(file_dest, type, ArrayGet(arr, i)) < 0) {
            return false;
        }
    }
    return true;
}