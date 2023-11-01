/**
 * @file get_terminal_input.h
 * 
 * @brief 
 *  Functions for getting various types of inputs from terminal.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#ifndef GET_TERMINAL_INPUT_H
#define GET_TERMINAL_INPUT_H

#include <stddef.h>

/**
 * @brief 
 *  Gets string input from console/terminal and parses into the specified data type.
 * 
 * @note
 *  For strings only the first word is resgistered.
 * 
 * @param prompt    input prompt
 * @param max_len   maximum input charater length
 * @param type      string indicating the data type to parse into
 * @param ptr       pointer to store to
 * 
 * @return 
 *   1 : successful @n
 *   0 : parsing unsuccessful @n
 *  -1 : no input or contains only the newline character @n
 */
int get_input(const char prompt[], size_t max_len, const char type[], void* ptr);

/**
 * @brief 
 *  Gets full string input from console/terminal.
 * 
 * @param prompt    input prompt
 * @param max_len   maximum input charater length
 * @param str       string to store to
 * 
 * @return Pointer to the string unless it is emtpy, then NULL is returned.
 */
char* get_full_str(const char prompt[], size_t max_len, char str[]);

/**
 * @brief 
 *  Gets a string input from console/terminal and removes the trailing newline character.
 * 
 * @param prompt    input prompt
 * @param max_len   maximum input charater length
 * @param str       string to store to
 * 
 * @return Pointer to the string unless it is emtpy, then NULL is returned.
 */
char* get_str(const char prompt[], size_t max_len, char str[]);
#endif