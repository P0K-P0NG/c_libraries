/**
 * @file get_file.h
 *
 * @brief
 *  Functions for getting a file pointer from terminal.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-12
 */
#ifndef GET_FILE_H
#define GET_FILE_H

#include "string_block.h"
#include <stdio.h>

/**
 * @brief
 *  Gets and opens a file from its file name inputted from the console/terminal
 *
 * @param[out] p_file       file pointer to get
 * @param[in]  name_len     Max length of the file name
 * @param[in]  mode         mode to open the file in, Ex. "r" for read
 * @param[in]  suffix       suffix required, pass in empty string no checking needed
 * @param[in]  cwd          current working directory of the executable,
 *                          pass in NULL if directory context isn't needed
 * @param[in]  prompt       prompt for the file
 *
 * @return Error code : @n
 *  0 : no error
 *  1 : error no file name read
 *  2 : error incorrect suffix
 *  3 : unable to open file
 */
extern int getFilePtr(FILE **p_file, const size_t name_len, const char mode[],
                      const char suffix[], const char cwd[],
                      const char prompt[]);

#endif