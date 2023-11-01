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

int get_input(
    const char prompt[],    size_t max_len, 
    const char type[],      void* ptr)
{
    char str[max_len];
    printf(prompt);
    fgets(str, max_len, stdin);
    fflush(stdin);
    return sscanf(str, type, ptr);
}

char* get_full_str(const char prompt[], size_t max_len, char str[])
{
    printf(prompt);
    char *ptr = fgets(str, max_len, stdin);
    fflush(stdin);
    return ptr;
}

char* get_str(const char prompt[], size_t max_len, char str[])
{
    printf(prompt);
    char *ptr = fgets(str, max_len, stdin);
    if(ptr != NULL && str[0] != '\0' && str[strlen(str) - 1] == '\n')
    {
        str[strlen(str) - 1] = '\0';
    }
    fflush(stdin);
    return ptr;
}