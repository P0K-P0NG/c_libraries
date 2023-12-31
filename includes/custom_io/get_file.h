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

#include <stdio.h>

/**
 * @brief 
 *  Gets and opens a file from its file name inputted from the console/terminal
 * 
 * @param file_p    file pointer to get
 * @param prompt    prompt for the file
 * @param max_len   max length of the file name
 * @param mode      mode to open the file in, Ex. "r" for read
 * @param suffix    suffix required, pass in empty string no checking needed
 * @param cwd       current working directory of the executable, 
 *                  pass in NULL if directory context isn't needed
 * 
 * @return Error code : @n
 *  0 : no error
 *  1 : error no file name read
 *  2 : error incorrect suffix
 *  3 : unable to open file
 */
int get_file_p(FILE **file_p, const char prompt[], size_t max_len, const char mode[], const char suffix[], const char cwd[]);
#endif