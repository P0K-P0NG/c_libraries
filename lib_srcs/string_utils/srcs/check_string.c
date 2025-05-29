/**
 * @file check_string.c
 *
 * @brief
 *  Functions for verifying a string's characteristics.
 *
 * @implements
 *  check_string.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include "check_string.h"
#include <ctype.h>
#include <string.h>

int isStrAlpha(const char str[])
{
    if (str == NULL)
        return -1;

    int i = 0;
    for (; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            i = 0;
            break;
        }
    }
    return i;
}

int isStrDigit(const char str[])
{
    if (str == NULL)
        return -1;

    int i = 0;
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            i = 0;
            break;
        }
    }
    return i;
}

int isStrInt(const char str[])
{
    if (str == NULL)
        return -1;

    int is_valid = 0;
    int i = 0;
    if (str[0] == '-')
        i++;
    if (str[i] == '0')
        return 0;
    for (; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            is_valid = 1;
        } else {
            is_valid = 0;
            break;
        }
    }
    return is_valid * i;
}

int isStrFloat(const char str[])
{
    if (str == NULL)
        return -1;

    int deci_pt_count = 0;
    int is_valid = 0;
    int i = 0;
    if (str[0] == '-')
        i++;
    if (str[i] != '0') {
        // Skip
    } else if (str[i + 1] == '.') {
        deci_pt_count++;
        i += 2;
    } else {
        return 0;
    }
    for (; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            deci_pt_count++;
            if (deci_pt_count > 1) {
                is_valid = 0;
                break;
            }
        } else if (isdigit(str[i])) {
            is_valid = 1;
        } else {
            is_valid = 0;
            break;
        }
    }
    return is_valid * i;
}

int getIntStrLength(const char str[])
{
    if (str == NULL)
        return -1;

    int is_valid = 0;
    int i = 0;
    if (str[0] == '-')
        i++;
    if (str[i] == '0')
        return 0;
    for (; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            is_valid = 1;
        } else {
            break;
        }
    }
    return is_valid * i;
}

int getFloatStrLength(const char str[])
{
    if (str == NULL)
        return -1;

    int deci_pt_count = 0;
    int is_valid = 0;
    int i = 0;
    if (str[0] == '-')
        i++;
    if (str[i] != '0') {
        // Skip
    } else if (str[i + 1] == '.') {
        deci_pt_count++;
        i += 2;
    } else {
        return 0;
    }
    for (; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            deci_pt_count++;
            if (deci_pt_count > 1)
                break;
        } else if (isdigit(str[i])) {
            is_valid = 1;
        } else {
            break;
        }
    }
    return is_valid * i;
}

int hasSuffix(const char str[], const char suffix[])
{
    if (str == NULL || suffix == NULL)
        return -1;

    int result = 0;
    int suffix_start = strlen(str) - strlen(suffix);
    if (suffix_start >= 0 && strcmp(&str[suffix_start], suffix) == 0) {
        result = 1;
    }
    return result;
}