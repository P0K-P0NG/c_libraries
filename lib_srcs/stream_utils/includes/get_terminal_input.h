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
#include "string_block.h"
#include "universal_pointer.h"

/**
 * @brief 
 *  Gets string input from console/terminal and parses into the specified data
 *  type.
 *
 * @note
 *  For strings only the first word is resgistered.
 *
 * @param max_len   max length of the input string
 * @param ptr       pointer to store to
 * @param prompt    input prompt
 *
 * @return 
 *   1 : successful @n 
 *   0 : parsing unsuccessful @n 
 *  -1 : no input or contains only the newline character @n
 */
extern int getInput(const size_t max_len, Pointer ptr, const char prompt[]);

/**
 * @brief 
 *  Gets full string input from console/terminal.
 * 
 * @param str       string to store to
 * @param prompt    input prompt
 * 
 * @return Pointer to the string unless it is emtpy, then NULL is returned.
 */
extern char *getFullStr(String str, const char prompt[]);

/**
 * @brief 
 *  Gets a string input from console/terminal and removes the trailing newline
 *  character.
 *
 * @param str       string to store to
 * @param prompt    input prompt
 *
 * @return Pointer to the string unless it is emtpy, then NULL is returned.
 */
extern char *getStr(String str, const char prompt[]);

#endif