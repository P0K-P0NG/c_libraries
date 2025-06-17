/**
 * @file string_funcs.h
 *
 * @brief
 *  Functions for strings.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#ifndef STRING_FUNCS_H
#define STRING_FUNCS_H

#include "string_block.h"
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief
 *  Join multiple strings together seperated by a provided string.
 *
 * @param[out] joined_str   string to store the result
 * @param[in]  max_len      max length of output string
 * @param[in]  str_list     list of strings to join
 * @param[in]  count        number of strings to join
 * @param[in]  delim        seperator string
 *
 * @return Pointer to the output string. NULL if failed.
 */
extern char *joinStrs(char joined_str[], size_t max_len, char *str_list[],
                      size_t count, const char delim[]);

/**
 * @brief
 *  Splits a string into a specified number of substrings at the specified
 *  delimiter regex pattern.
 *
 * @note
 *  If the number of spilt sections is less than count the remaining
 *  substrings is set to NULL.
 *
 * @param[in]  str      string to split
 * @param[out] substrs  array of substrings to store in
 * @param[in]  count    number of substrings
 * @param[in]  delim    string marking the point of speration, will be
 *                      replaced
 *
 * @return Number successfully divided sections.
 */
extern size_t splitStr(char str[], char *substrs[], size_t count,
                       const char delim[]);

/**
 * @brief
 *  Removes all matches of the specified regex pattern in a string.
 *
 * @param[in,out] str`      string to modify
 * @param[in]     pattern   pattern to remove
 *
 * @return
 *  true  : execution successful
 *  false : execution failed
 */
bool removeRegexMatches(char str[], const char pattern[]);

/**
 * @brief
 *  Adds a buffer string of a specified character to the front and back
 *  of the string by the specified amount.
 *
 * @param[in,out] str           string to add the buffer to
 * @param[in]     buffer_len    buffer length from the front and back
 * @param[in]     buffer_char   buffer character
 *
 * @return Pointer to the formatted string.
 */
extern char *strAddBuffer(struct String str, int buffer_len[2],
                          char buffer_char);

/**
 * @brief
 *  Aligns a string in the available space in the alignment mode chosen :
 *  l => left @n
 *  r => right @n
 *  c => center @n
 *  Surronded by the given buffer character. @n
 *
 * @param[in,out] str           string to align
 * @param[in]     mode          alignment mode
 * @param[in]     buffer_char   buffer character
 *
 * @return Pointer to the formatted string.
 */
extern char *strAlign(struct String str, char mode, char buffer_char);

/**
 * @brief
 *  Trims a specific character from both ends of a string.
 *
 * @param[in,out] str           string to trim
 * @param[in]     char_to_del   character to remove
 *
 * @return Number of deleted characters.
 */
extern int trim(char str[], const char char_to_del);

/**
 * @brief
 *  Trims a specific character from the font of a string.
 *
 * @param[in,out] str           string to trim
 * @param[in]     char_to_del   character to remove
 *
 * @return Number of deleted characters.
 */
extern int trimFront(char str[], const char char_to_del);

/**
 * @brief
 *  Trims a specific character from the end of a string.
 *
 * @param[in,out] str           string to trim
 * @param[in]     char_to_del   character to remove
 *
 * @return Number of deleted characters.
 */
extern int trimEnd(char str[], const char char_to_del);

/**
 * @brief
 *  Changes all characters in a string to upper case.
 *
 * @param[in,out] str   string to edit
 *
 * @return Pointer to the inputted string.
 */
extern char *strToUpper(char str[]);

/**
 * @brief
 *  Changes all characters in a string to lower case.
 *
 * @param[in,out] str   string to edit
 *
 * @return Pointer to the inputted string.
 */
extern char *strToLower(char str[]);

/**
 * @brief
 *  Removes a trailing newline character if there is any.
 *
 * @param[in,out] str   string to remove from
 *
 * @return Inputted string.
 */
extern char *removeNewline(char str[]);

/**
 * @brief
 *  Formats the first character of a string to uppercase and the rest to
 *  lowercase.
 *
 * @param[in,out] str   string to format
 *
 * @return Formatted string.
 */
extern char *caseFormat(char str[]);
#endif