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
#include <regex.h>
#include <string.h>

bool isStrAlpha(const char str[], size_t len)
{
    bool is_valid = true;

    if (len == -1)
        len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (!isalpha(str[i])) {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool isStrDigit(const char str[], size_t len)
{
    bool is_valid = true;

    if (len == -1)
        len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool isStrInt(const char str[], size_t len)
{
    bool is_valid = false;
    size_t i = 0;

    if (len == -1) {
        len = strlen(str);
    } else if (len == 0) {
        return true;
    }

    if (str[i] == '-')
        i++;

    if (str[i] != '0') {
        // Skip
    } else if (i + 1 == len) {
        return len;
    } else {
        return 0;
    }
    for (; i < len; i++) {
        if (isdigit(str[i])) {
            is_valid = true;
        } else {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool isStrFloat(const char str[], size_t len)
{
    int is_valid = 0;
    int deci_pt_count = 0;
    size_t i = 0;

    if (len == -1) {
        len = strlen(str);
    } else if (len == 0) {
        return true;
    }

    if (str[0] == '-')
        i++;

    if (str[i] == '0') {
        i++;
        if (str[i] == '.') {
            deci_pt_count++;
            i++;
        } else if (str[i] == '\0') {
            return i;
        } else {
            return false;
        }
    } else if (str[i] == '.') {
        return false;
    }

    for (; i < len; i++) {
        if (str[i] == '.') {
            deci_pt_count++;
            if (deci_pt_count > 1) {
                is_valid = false;
                break;
            }
            if (i + 1 == len) {
                is_valid = false;
                break;
            }
        } else if (isdigit(str[i])) {
            is_valid = true;
        } else {
            is_valid = false;
            break;
        }
    }
    return is_valid;
}

bool isDelimStrInt(const char str[], const char delim[])
{
    int len;
    if (delim == NULL) {
        len = strlen(str);
    } else {
        regmatch_t offsets;
        int status = matchRegex(str, delim, &offsets);
        switch (status) {
        case 1:
            len = offsets.rm_so;
            break;
        case 0:
            len = 0;
            break;
        case -1:
            return false;
        }
    }
    return isStrInt(str, len);
}

bool isDelimStrFloat(const char str[], const char delim[])
{
    int len;
    if (delim == NULL) {
        len = strlen(str);
    } else {
        regmatch_t offsets;
        int status = matchRegex(str, delim, &offsets);
        switch (status) {
        case 1:
            len = offsets.rm_so;
            break;
        case 0:
            len = 0;
            break;
        case -1:
            return false;
        }
    }
    return isStrFloat(str, len);
}

size_t hasSuffix(const char str[], const char suffix[])
{
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (str_len < suffix_len)
        return 0;
    size_t result = 0;
    size_t suffix_start = str_len - suffix_len;
    if (suffix_start >= 0 && strcmp(&str[suffix_start], suffix) == 0) {
        result = 1;
    }
    return result;
}

int matchRegex(const char str[], const char pattern[], regmatch_t *offsets)
{
    regex_t buf;
    regmatch_t match_arr[1];
    if (regcomp(&buf, pattern, 0) != 0)
        return -1;
    int match_status = regexec(&buf, str, 1, match_arr, 0);
    regfree(&buf);

    switch (match_status) {
    case 0:
        *offsets = match_arr[0];
        return 1;
    case REG_NOMATCH:
        return 0;
    default:
        return -1;
    }
}