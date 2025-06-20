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
#include "get_file.h"
#include "check_string.h"
#include "get_terminal_input.h"
#include <stdio.h>
#include <unistd.h>

int getFilePtr(FILE **file_p, const size_t name_len, const char mode[],
               const char suffix[], const char cwd[], const char prompt[])
{
    int err_code = 0;
    char file_name[name_len];
    if (cwd == NULL) {
        chdir(cwd);
    }
    *file_p = NULL;
    if (getStr((String_t){file_name, name_len}, prompt) == NULL) {
        err_code = 1;
    } else if (!hasSuffix(file_name, suffix)) {
        err_code = 2;
    } else if ((*file_p = fopen(file_name, mode)) == NULL) {
        err_code = 3;
    }
    return err_code;
}