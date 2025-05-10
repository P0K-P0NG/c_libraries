#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swap_funcs.h"
#include "universal_array.h"

void ArraySetItem(Array arr, unsigned int idx, void *item)
{
    memcpy(arr.items + idx*arr.item_size, item, arr.item_size); 
}

void* ArrayGetItem(Array arr, unsigned int idx)
{
    return arr.items + idx*arr.item_size;
}

int ArrayGetIdx(Array arr, const void *item, int (*comp_func)(const void*, const void*))
{
    if(item == NULL)
    {
        return -2;
    }
    /* MAIN LOGIC */

    int index = -1;
    const void *item_i = arr.items;
    for (int i = 0; i < arr.len; i++)
    {
        if(comp_func(item, item_i) == 0)
        {
            index = i;
            break;
        }
        item_i += arr.item_size;
    }
    return index;
}

void ArrayInsertSort(Array *arr, int (*comp_func)(const void*, const void*))
{
    for(int i = 1; i < arr->len; i++)
    {
        for(int j = i; j >= 1; j--)
        {
            void* prev_item = ArrayGetItem(*arr, j - 1);
            void* next_item = ArrayGetItem(*arr, j);
            
            if(comp_func(prev_item, next_item) >= 0)
            {
                swap(prev_item, next_item, arr->item_size);
            }
            else
            {
                break;
            }
        }
    }
}

int array_to_int(Array arr)
{
    int result = 0;
    for(int i = 0; i < arr.len; i++)
    {
        result *= 10;
        result += *(int*)ArrayGetItem(arr, i);
    }
    return result;
}