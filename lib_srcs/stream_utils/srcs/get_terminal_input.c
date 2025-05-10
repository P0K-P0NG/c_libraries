/**
 * @file get_terminal_input.c
 * 
 * @brief 
 *  Functions for getting various types of inputs from terminal.
 * 
 * @implements
 *  get_terminal_input.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include <stdio.h>
#include <string.h>
#include "get_terminal_input.h"

int getInput(const size_t max_len, Pointer ptr, const char prompt[])
{
    char str[max_len];
    printf("%s", prompt);
    fgets(str, max_len, stdin);
    return sscanf(str, ptr.type, ptr.ptr);
}

char *getFullStr(String str, const char prompt[])
{
    printf("%s", prompt);
    char *ptr = fgets(str.items, str.len, stdin);
    return ptr;
}

char *getStr(String str_block, const char prompt[])
{
    char *str = str_block.items;
    char max_len = str_block.len;
    
    printf("%s", prompt);
    char *ptr = fgets(str, max_len, stdin);
    if(ptr != NULL && str[0] != '\0' && str[strlen(str) - 1] == '\n')
    {
        str[strlen(str) - 1] = '\0';
    }
    return ptr;
}