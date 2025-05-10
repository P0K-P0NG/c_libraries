#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swap_funcs.h"
#include "universal_array_io.h"

int ArrayReadBinary(Array *arr, FILE *file_src)
{
    if(file_src == NULL)
    {
        return -2;
    }
    /* MAIN LOGIC */
    
    if((fread(arr, sizeof(Array), 1, file_src)) != 1)
    {
        return 0;
    }
    char *items = calloc(arr->len, arr->item_size);
    if(items == NULL)
    {
        return -1;
    }
    if(fread(items, arr->item_size, arr->len, file_src) != (size_t) arr->len)
    {
        free(items);
        return 0;
    }
    arr->items = items;
    return 1;
}

int ArrayWriteBinary(Array arr, FILE *file_dest)
{
    if(file_dest == NULL)
    {
        return -1;
    }
    Array temp = {
        .items = NULL,
        .item_size = arr.item_size,
        .len = arr.len
    };
    if( fwrite(&temp, sizeof(Array), 1, file_dest) != 1 ||
        fwrite(arr.items, arr.item_size, arr.len, file_dest) != (size_t) arr.len)
    {
        return 0;
    }
    return 1;
}

int ArrayWrite(
    Array arr,     char type[TYPE_LEN], 
    char *delim,    FILE *file_dest)
{
    if(file_dest == NULL)
    {
        return -1;
    }
    if(fprintf(file_dest, type, ArrayGetItem(arr, 0)) < 0)
    {
        return 0;
    }
    for(int i = 1; i < arr.len; i++)
    {
        if( fprintf(file_dest, "%s", delim) < 0 ||
            fprintf(file_dest, type, ArrayGetItem(arr, i)) < 0)
        {
            return 0;
        }
    }
    return 1;
}