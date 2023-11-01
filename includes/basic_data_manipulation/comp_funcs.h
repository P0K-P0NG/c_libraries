/**
 * @file comp_funcs.h
 * 
 * @brief 
 *  Functions for comparing data passed in as void pointers.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#ifndef COMP_FUNC_H
#define COMP_FUNC_H

/**
 * @brief 
 *  Compares two integers, received as void pointers, through subtraction.
 *  INT_1 - INT_2.
 * 
 * @param int1  pointer to integer 1
 * @param int2  pointer to integer 2
 * 
 * @return difference of INT_1 - INT_2
 */
int comp_int(const void* int1, const void* int2);

/**
 * @brief 
 *  Compares 2 strings, received as void pointers, 
 *  by the ascii values of their characters.
 * 
 * @param str1    pointer to string 1
 * @param str2    pointer to string 2
 * 
 * @return an integer siginifying the strings alphabetical order relative to one another. @n
 *  < 0 : if the first string comes before the second @n
 *  > 0 : if the first string comes after the second @n
 *    0 : if the strings are the same @n
 */
int comp_str(const void* str1, const void* str2);

/**
 * @brief 
 *  Compares 2 strings while ignoring case differences, received as void pointers, 
 *  by the ascii values of their characters.
 * 
 * @param str1    pointer to string 1
 * @param str2    pointer to string 2
 * 
 * @return 
 *  an integer siginifying the strings alphabetical order, 
 *  disregarding the case, relative to one another. @n
 *  < 0 : if the first string comes before the second @n
 *  > 0 : if the first string comes after the second @n
 *    0 : if the strings are the same @n
 */
int comp_str_ignore_case(const void* str1, const void* str2);


/**
 * @brief 
 *  Compares two pointers, received as void pointers, through subtraction.
 *  PTR_1 - PTR_1.
 * 
 * @param int1  pointer 1
 * @param int2  pointer 2
 * 
 * @return difference of PTR_1 - PTR_2
 */
int comp_ptr(const void *ptr1, const void *ptr2);
#endif