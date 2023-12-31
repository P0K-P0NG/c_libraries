/**
 * @file check_input.h
 * 
 * @brief 
 *  Functions for verifying characteristics about inputs from terminal.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#ifndef CHECK_INPUT_H
#define CHECK_INPUT_H

/**
 * @brief 
 *  Checks if a string is completely alphabetical.
 * 
 * @param str   string to check
 * 
 * @return 
 *  > 0 : string is alphabetical @n
 *    0 : string isn't alphabetical @n
 *   -1 : NULL pointer was passed in @n
 */
int str_is_alpha(const char str[]);

/**
 * @brief 
 *  Checks if string consist of only digits or not.
 * 
 * @param str   string to check
 * 
 * @return 
 *  > 0 : string is made up of only digits @n
 *    0 : string isn't made up of only digits @n 
 *   -1 : NULL pointer was passed in @n
 */
int str_is_digit(const char str[]);

/**
 * @brief 
 *  Checks if inputted string is compeletely an integer.
 * 
 * @param str   string to check
 * 
 * @return 
 *  > 0 : string is a valid integer @n
 *    0 : string isn't a valid integer @n 
 *   -1 : NULL pointer was passed in @n
 */
int str_is_int(const char str[]);

/**
 * @brief 
 *  Check if a string is compeletely a double.
 * 
 * @param str     string to check
 * 
 * @return
 *  > 0 : string is a valid double @n
 *    0 : string isn't a valid double @n
 *   -1 : NULL pointer was passed in @n
 */
int str_is_double(const char str[]);

/**
 * @brief 
 *  Checks if a string has the suffix specified
 * 
 * @param str       string to check
 * @param suffix    suffix to find in the string
 * 
 * @return
 *   1 : string's suffix matches @n
 *   0 : string's suffix doesn't match @n
 *  -1 : NULL pointer was passed in @n
 */
int has_suffix(const char str[], const char suffix[]);
#endif