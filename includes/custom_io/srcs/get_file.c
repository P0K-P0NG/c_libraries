/**
 * @file get_file.c
 * 
 * @brief 
 *  Functions for getting a file pointer from terminal.
 * 
 * @implements
 *  get_file.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-12
 */
#include <stdio.h>
#include <unistd.h>
#include "check_input.h"
#include "get_terminal_input.h"
#include "get_file.h"

int get_file_p(
    FILE **file_p,      const char prompt[], size_t max_len, 
    const char mode[],  const char suffix[], const char cwd[])
{
    int err_code = 0;
    char file_name[max_len];
    if(cwd == NULL)
    {
        chdir(cwd);
    }
    *file_p = NULL;
    if(get_str(prompt, max_len, file_name) == NULL)
    {
        err_code = 1;
    }
    else if(!has_suffix(file_name, suffix))
    {
        err_code = 2;
    }
    else if((*file_p = fopen(file_name, mode)) == NULL)
    {
        err_code = 3;
    }
    return err_code;
}