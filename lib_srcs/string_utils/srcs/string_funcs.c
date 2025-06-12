/**
 * @file string_funcs.c
 *
 * @brief
 *  Functions for strings.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include "string_funcs.h"
#include <assert.h>
#include <ctype.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>


char *joinStrs(char joined_str[], size_t max_len, char *str_list[],
               size_t count, const char delim[])
{
    size_t delim_len = strlen(delim);
    size_t total_len = strlen(str_list[0]);

    if (total_len >= max_len)
        return NULL;
    memcpy(&joined_str[0], str_list[0], total_len);

    for (size_t i = 1; i < count; i++) {
        size_t item_len = strlen(str_list[i]);
        if (total_len + delim_len + item_len >= max_len)
            return NULL;
        memcpy(&joined_str[total_len], delim, delim_len);
        total_len += delim_len;
        memcpy(&joined_str[total_len], str_list[i], item_len);
        total_len += item_len;
    }
    joined_str[total_len] = '\0';
    return joined_str;
}

size_t splitStr(char str[], char *substrs[], size_t count, const char delim[])
{
    assert(str != NULL);

    regex_t regex_buf;
    if (regcomp(&regex_buf, delim, 0) != 0)
        return 0;

    char *curr = str;
    int status;
    size_t idx = 0;
    regmatch_t offsets;
    while (idx < count) {
        status = regexec(&regex_buf, curr, 1, &offsets, 0);
        if (status == 0) {
            if (offsets.rm_so != 0) {
                substrs[idx] = curr;
                idx++;
            }
            curr[offsets.rm_so] = '\0';
            curr += offsets.rm_eo;
        } else if (status == REG_NOMATCH) {
            break;
        } else {
            regfree(&regex_buf);
            return 0;
        }
    }
    regfree(&regex_buf);

    if (idx < count && (idx == 0 || *curr != '\0')) {
        substrs[idx] = curr;
        idx++;
    }

    for (size_t i = idx; i < count; i++) {
        substrs[i] = NULL;
    }
    return idx;
}

size_t removeRegexMatches(char str[], const char pattern[])
{
    assert(str != NULL);

    regex_t regex_buf;
    if (regcomp(&regex_buf, pattern, 0) != 0)
        return 0;

    size_t str_len = strlen(str);
    char *copy_buf = calloc(str_len + 1, sizeof(char));
    if (copy_buf == NULL) {
        regfree(&regex_buf);
        return 0;
    }

    char *curr = str;
    int status = 0;
    size_t remove_len = 0;
    size_t count = 0;
    regmatch_t offsets;
    status = regexec(&regex_buf, curr, 1, &offsets, 0);
    if (status == 0) {
        curr += offsets.rm_eo;
        remove_len += offsets.rm_eo - offsets.rm_so;
        count++;
    }
    while (status == 0) {
        status = regexec(&regex_buf, curr, 1, &offsets, 0);
        if (status != 0)
            break;

        memcpy(copy_buf, curr, offsets.rm_so);
        memcpy(curr - remove_len, copy_buf, offsets.rm_so);
        curr += offsets.rm_eo;
        remove_len += offsets.rm_eo - offsets.rm_so;
        count++;
    }
    regfree(&regex_buf);

    if (status != REG_NOMATCH) {
        count = 0;
    } else if (remove_len != 0) {
        size_t len = str + str_len + 1 - curr;
        memcpy(copy_buf, curr, len);
        memcpy(curr - remove_len, copy_buf, len);
    }
    free(copy_buf);
    return count;
}

char *strAddBuffer(struct String str_block, int buffer_len[2], char buffer_char)
{
    char *str = str_block.items;
    int max_len = str_block.len;

    assert(str != NULL);

    char temp_str[strlen(str) + 1];
    strcpy(temp_str, str);
    memset(str, buffer_char, buffer_len[0]);
    strcpy(&str[buffer_len[0]], temp_str);
    memset(&str[buffer_len[0] + strlen(temp_str)], buffer_char, buffer_len[1]);
    str[max_len - 1] = '\0';
    return str;
}

char *strAlign(struct String str_block, char mode, char buffer_char)
{
    char *str = str_block.items;
    int max_len = str_block.len;

    assert(str != NULL);

    int front_len = 0;
    int back_len = 0;
    int buffer_len = max_len - strlen(str) - 1;
    switch (mode) {
    case 'l':
        back_len = buffer_len;
        break;
    case 'r':
        front_len = buffer_len;
        break;
    case 'c':
        front_len = buffer_len / 2;
        back_len = buffer_len / 2 + buffer_len % 2;
        break;
    default:
        break;
    }
    char temp_str[strlen(str) + 1];
    strcpy(temp_str, str);
    memset(str, buffer_char, front_len);
    strcpy(&str[front_len], temp_str);
    memset(&str[front_len + strlen(temp_str)], buffer_char, back_len);
    str[max_len - 1] = '\0';
    return str;
}

int trim(char str[], char char_to_del)
{
    if (str == NULL)
        return -1;

    int del_count = 0;
    del_count += trimFront(str, char_to_del);
    del_count += trimEnd(str, char_to_del);
    return del_count;
}

int trimFront(char str[], char char_to_del)
{
    if (str == NULL)
        return -1;

    int i, k;
    for (i = 0; str[i] != '\0' && str[i] == char_to_del; i++)
        ;
    for (k = i; k != '\0'; k++) {
        str[k - i] = str[k];
    }
    str[k] = '\0';
    return i;
}

int trimEnd(char str[], char char_to_del)
{
    if (str == NULL)
        return -1;

    int max_idx = strlen(str) - 1;
    int i = max_idx;
    for (; str[i] == char_to_del && i >= 0; i--)
        ;
    str[i + 1] = '\0';
    return max_idx - i;
}

char *strToUpper(char str[])
{
    assert(str != NULL);

    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

char *strToLower(char str[])
{
    assert(str != NULL);

    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

char *removeNewline(char str[])
{
    assert(str != NULL);

    int last_idx = strlen(str) - 1;
    if (str[0] != '\0' && str[last_idx] == '\n') {
        str[last_idx] = '\0';
    }
    return str;
}

char *caseFormat(char str[])
{
    assert(str != NULL);

    int len = strlen(str);
    str[0] = toupper(str[0]);
    for (int i = 1; i < len; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}