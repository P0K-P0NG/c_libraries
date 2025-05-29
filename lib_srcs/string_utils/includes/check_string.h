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

/**
 * @brief
 *  Checks if a string is completely alphabetical.
 *
 * @param[in] str   string to check
 *
 * @return
 *  > 0 : string is alphabetical @n
 *    0 : string isn't alphabetical @n
 *   -1 : NULL pointer was passed in @n
 */
extern int isStrAlpha(const char str[]);

/**
 * @brief
 *  Checks if string consist of only digits or not.
 *
 * @param[in] str   string to check
 *
 * @return
 *  > 0 : string is made up of only digits @n
 *    0 : string isn't made up of only digits @n
 *   -1 : NULL pointer was passed in @n
 */
extern int isStrDigit(const char str[]);

/**
 * @brief
 *  Checks if inputted string is compeletely an integer.
 *
 * @param[in] str   string to check
 *
 * @return
 *  > 0 : string is a valid integer @n
 *    0 : string isn't a valid integer @n
 *   -1 : NULL pointer was passed in @n
 */
extern int isStrInt(const char str[]);

/**
 * @brief
 *  Check if a string is completely a floating point number.
 *
 * @param[in] str     string to check
 *
 * @return
 *  > 0 : string is a valid floating point number @n
 *    0 : string isn't a valid floating point number @n
 *   -1 : NULL pointer was passed in @n
 */
extern int isStrFloat(const char str[]);

/**
 * @brief
 *  Finds the length of the longest valid integer from the start of the inputed
 *  string.
 *
 * @param[in] str     string to check
 *
 * @return Length of the longest integer in characters. -1 if NULL pointer was
 *  passed in @n
 */
int getIntStrLength(const char str[]);

/**
 * @brief
 *  Finds the length of the longest valid floating point number from the start
 *  of the inputed string.
 *
 * @param[in] str     string to check
 *
 * @return Length of the longest floating point number in characters. -1 if NULL
 *  pointer was passed in @n
 */
int getFloatStrLength(const char str[]);

/**
 * @brief
 *  Checks if a string has the suffix specified
 *
 * @param[in] str       string to check
 * @param[in] suffix    suffix to find in the string
 *
 * @return
 *   1 : string's suffix matches @n
 *   0 : string's suffix doesn't match @n
 *  -1 : NULL pointer was passed in @n
 */
extern int hasSuffix(const char str[], const char suffix[]);
#endif