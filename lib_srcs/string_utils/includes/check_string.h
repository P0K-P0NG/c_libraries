/**
 * @file check_string.h
 *
 * @brief
 *  Functions for verifying a string's characteristics.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#ifndef CHECK_STRING_H
#define CHECK_STRING_H

#include <regex.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief
 *  Checks if the inputted string up to provided length entirely
 *  alphabetical.
 *
 * @param[in] str   string to check
 * @param[in] len   length to check
 *
 * @return true  : substring is valid 
 * @return false : substring is invalid
 */
extern bool isStrAlpha(const char str[], size_t len);

/**
 * @brief
 *  Checks if the inputted string up to provided length consists of only
 *  digits or not.
 *
 * @param[in] str   string to check
 * @param[in] len   length to check
 *
 * @return true  : substring is valid 
 * @return false : substring is invalid
 */
extern bool isStrDigit(const char str[], size_t len);

/**
 * @brief
 *  Checks if the inputted string up to provided length is a valid an
 *  integer.
 *
 * @param[in] str   string to check
 * @param[in] len   length to check
 *
 * @return true  : substring is valid 
 * @return false : substring is invalid
 */
extern bool isStrInt(const char str[], size_t len);

/**
 * @brief
 *  Checks if the inputted string up to provided length is a valid a floating
 *  point number.
 *
 * @param[in] str   string to check
 * @param[in] len   length to check
 *
 * @return
 *  true  : substring is valid @n false : substring is invalid @n
 */
extern bool isStrFloat(const char str[], size_t len);

/**
 * @brief
 *  Checks if the inputted string up to provided delimiter is a valid an
 *  integer.
 *
 * @param[in] str       string to check
 * @param[in] delim     delimiter to check up to
 *
 * @return
 *  true  : substring is valid @n false : substring is invalid @n
 */
extern bool isDelimStrInt(const char str[], const char delim[]);

/**
 * @brief
 *  Checks if the inputted string up to provided delimiter is a valid a floating
 *  point number.
 *
 * @param[in] str       string to check
 * @param[in] delim     delimiter to check up to
 *
 * @return true  : substring is valid 
 * @return false : substring is invalid
 */
bool isDelimStrFloat(const char str[], const char delim[]);

/**
 * @brief
 *  Checks if a string has the suffix specified.
 *
 * @param[in] str       string to check
 * @param[in] suffix    suffix to find in the string
 *
 * @return
 *  > 0 : length of valid string @n
 *    0 : string's suffix doesn't match @n
 */
extern size_t hasSuffix(const char str[], const char suffix[]);

/**
 * @brief
 *  finds the position of the first match to given pattern in the given string.
 *
 * @param[in]  str      string to format
 * @param[in]  pattern  pattern to find
 * @param[out] offsets  offsets of the matched substring
 *
 * @return
 *   1 : a match is found @n
 *   0 : no match is found @n
 *  -1 : an error occurred @n
 */
extern int matchRegex(const char str[], const char pattern[],
                      regmatch_t *offsets);
#endif