#ifndef BASIC_STATS_H
#define BASIC_STATS_H

#include <stddef.h>

/**
 * @brief
 *  Finds the larger of two inputted integers.
 *
 * @param[in] num1  integer 1
 * @param[in] num2  integer 2
 *
 * @return Larger integer.
 */
extern int maxInt(const int num1, const int num2);

/**
 * @brief
 *  Finds the smaller of two inputted integers.
 *
 * @param[in] num1  integer 1
 * @param[in] num2  integer 2
 *
 * @return Smaller integer.
 */
extern int minInt(const int num1, const int num2);

/**
 * @brief
 *  Finds the larger of two inputted floats.
 *
 * @param[in] num1  float 1
 * @param[in] num2  float 2
 *
 * @return Larger float.
 */
extern float maxFloat(const float num1, const float num2);

/**
 * @brief
 *  Finds the smaller of two inputted floats.
 *
 * @param[in] num1  float 1
 * @param[in] num2  float 2
 *
 * @return Smaller float.
 */
extern float minFloat(const float num1, const float num2);

/**
 * @brief
 *  Finds the larger of two inputted doubles.
 *
 * @param[in] num1  double 1
 * @param[in] num2  double 2
 *
 * @return Larger double.
 */
extern double maxDouble(const double num1, const double num2);

/**
 * @brief
 *  Finds the smaller of two inputted doubles.
 *
 * @param[in] num1  double 1
 * @param[in] num2  double 2
 *
 * @return Smaller double.
 */
extern double minDouble(const double num1, const double num2);

/**
 * @brief 
 *  Sums an array of size_t numbers.
 * 
 * @param[in] arr       array to sum
 * @param[in] count     number of array items
 *  
 * @return Summed result. 
 */
extern size_t sumSizeT(const size_t *arr, size_t count);
#endif