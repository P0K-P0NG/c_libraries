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

#include "string_block.h"
#include "universal_pointer.h"
#include <stddef.h>

/**
 * @brief
 *  Gets string input from console/terminal and parses into the specified data
 *  type.
 *
 * @note
 *  For strings only the first word is resgistered.
 *
 * @param[in] max_len   max length of the input string
 * @param[out] ptr       pointer to store to
 * @param[in] prompt    input prompt
 *
 * @return
 *   1 : successful @n
 *   0 : parsing unsuccessful @n
 *  -1 : no input or contains only the newline character @n
 */
extern int getInput(Pointer_t ptr, const size_t max_len,
                    const char prompt[]);

/**
 * @brief
 *  Gets full string input from console/terminal.
 *
 * @param[out] str       string to store to
 * @param[in]  prompt    input prompt
 *
 * @return Pointer to the string unless it is emtpy, then NULL is returned.
 */
extern char *getFullStr(String_t str, const char prompt[]);

/**
 * @brief
 *  Gets a string input from console/terminal and removes the trailing newline
 *  character.
 *
 * @param[out] str       string to store to
 * @param[in]  prompt    input prompt
 *
 * @return Pointer to the string unless it is emtpy, then NULL is returned.
 */
extern char *getStr(String_t str, const char prompt[]);

#endif