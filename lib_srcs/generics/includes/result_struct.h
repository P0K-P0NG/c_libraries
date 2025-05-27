/**
 * @file result_struct.h
 *
 * @brief
 *  Structs of generic result (err, data) data type and Macros for creating and
 *  using them.
 *
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2024-03-24
 */
#ifndef RESULT_STRUCT_H
#define RESULT_STRUCT_H

#include <errno.h>

#define defer(...) __VA_ARGS__
#define expand(...) __VA_ARGS__
#define blank(...)
#define joinUnderscore(a, b) a##_##b
#define joinU(a, b) defer(joinUnderscore)(a, b)
#define joinSpace(a, b) a b
#define joinS(a, b) defer(joinSpace)(a, b)
#define join1(f, a, ...) f(a, blank())
#define join2(f, a, ...) f(a, join1(f, __VA_ARGS__))
#define join3(f, a, ...) f(a, join2(f, __VA_ARGS__))
#define selectJoinN(_1, _2, _3, N, ...) join##N
#define join(f, ...) selectJoinN(__VA_ARGS__, 3, 2, 1)(f, __VA_ARGS__)
#define joinResult(f, ...) joinU(Result, join(f, __VA_ARGS__))

// #define joinSR(f, a, ...) a f(__VA_AGRS__)
// #define joinSR1(a, ...) a joinSR(joinSR, __VA_ARGS__)
// #define joinSR2(a, ...) a joinSR1(__VA_ARGS__)

/**
 * @brief
 *  Declares the struct for the provided non-pointer and non-array type
 *
 * @attention
 *  The struct keyword must be included before the macro.
 *
 * @warning
 *  Do not use pointer or array types, the code will break. For those refer to
 *  their intended macros. defPointerResult for pointers and defArrayResult for
 *  arrays.
 *
 * @example
 *  struct defResult(int);
 */
#define defResult(...)                                                         \
    joinResult(joinU, __VA_ARGS__)                                             \
    {                                                                          \
        unsigned int err;                                                      \
        join(joinS, __VA_ARGS__) data;                                         \
    }

/**
 * @brief
 *  A abbreviation for the struct created with defResult(type)
 *
 * @attention
 *  The struct keyword must be included before the macro.
 *
 * @warning
 *  Do not use pointer or array types, the code will break. For those refer to
 *  their intended macros. pointerResult for pointers and arrayResult for
 * arrays.
 *
 * @example
 *  struct result(int) number;
 */
#define result(type) Result_##type##_

/**
 * @brief
 *  Declares the struct for the provided pointer type
 *
 * @attention
 *  The struct keyword must be included before the macro.
 *
 * @warning
 *  Do not use non-pointer types. For those refer to their intended macros.
 *  defResult for plain types (i.e. no special characters) and defArrayResult
 *  for arrays.
 *
 * @example
 *  struct defPointerResult(int);
 */
#define defPointerResult(typetars)                                             \
    Result_##type##_ptr                                                        \
    {                                                                          \
        unsigned int err;                                                      \
        type stars##data;                                                      \
    }

/**
 * @brief
 *  A abbreviation for the struct created with defPointerResult(type)
 *
 * @attention
 *  The struct keyword must be included before the macro.
 *
 * @warning
 *  Do not use non-pointer types. For those refer to their intended macros.
 *  result for plain types (i.e. no special characters) and arrayResult for
 *  arrays.
 *
 * @example
 *  struct pointerResult(int) number;
 */
#define pointerResult(type) Result_##type##_ptr

/**
 * @brief
 *  Declares the struct for the provided array type
 *
 * @attention
 *  The struct keyword must be included before the macro.
 *
 * @warning
 *  Do not use non-array types. For those refer to their intended macros.
 *  defResult for plain types (i.e. no special characters) and defPointerResult
 *  for pointers.
 *
 * @example
 *  struct defArrayResult(int);
 */
#define defArrayResult(type, len)                                              \
    Result_##type##len##_arr                                                   \
    {                                                                          \
        unsigned int err;                                                      \
        type data[len];                                                        \
    }

/**
 * @brief
 *  A abbreviation for the struct created with defArrayResult(type)
 *
 * @attention
 *  The struct keyword must be included before the macro.
 *
 * @warning
 *  Do not use non-array types. For those refer to their intended macros.
 *  result for plain types (i.e. no special characters) and pointerResult for
 *  pointer.
 *
 * @example
 *  struct arrayResult(int) number;
 */
#define arrayResult(type) Result_##type##_arr

struct defResult(char);
struct defResult(int);
struct defResult(double);

#endif