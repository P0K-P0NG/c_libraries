/**
 * @file comp_func.c
 * 
 * @brief 
 *  Functions for comparing data passed in as void pointers.
 * 
 * @implements
 *  comp_func.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include <string.h>
#include <strings.h>
#include "comp_funcs.h"

inline int compInt(const void *int1, const void *int2)
{
    return (*(int*) int1 - *(int*) int2);
}

inline int compStr(const void *str1, const void *str2)
{
    return strcmp((char*) str1, (char*) str2);
}

inline int compStrIgnoreCase(const void *str1, const void *str2)
{
    return strcasecmp((char*) str1, (char*) str2);
}

inline int compPtr(const void *ptr1, const void *ptr2)
{
    return ptr1 - ptr2;
}