/**
 * @file string_funcs.h
 * 
 * @brief 
 *  Functions for sorting data.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include <string.h>
#include <ctype.h>
#include "string_funcs.h"

int split_str(char str[], char *substrs[], int count, char delimiter[])
{
    if(str == NULL || count < 1)
    {
        return -1;
    }
    /* MAIN LOGIC */

    int i = 0;
    int spilt_count = 0;
    substrs[i] = strtok(str, delimiter);
    if(substrs[i] != NULL)
    {
        spilt_count++;
    }
    for(i++; i < count; i++)
    {
        substrs[i] = strtok(NULL, delimiter);
        if(substrs[i] != NULL)
        {
            spilt_count++;
        }
    }
    return spilt_count;
}

char* str_add_buffer(
    char str[], size_t max_len, int front_len, int back_len, char buffer_char)
{
    if(str == NULL)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    char temp_str[strlen(str) + 1];
    strcpy(temp_str, str);
    memset(str, buffer_char, front_len);
    strcpy(&str[front_len], temp_str);
    memset(&str[front_len + strlen(temp_str)], buffer_char, back_len);
    str[max_len - 1] = '\0';
    return str;
}

char* str_align(char str[], size_t max_len, char mode, char buffer_char)
{
    if(str == NULL)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    int front_len = 0;
    int back_len = 0;
    int buffer_len = max_len - strlen(str) - 1;
    switch(mode)
    {
    case 'l':
        back_len = buffer_len;
        break;
    case 'r':
        front_len = buffer_len;
        break;
    case 'c':
        front_len = buffer_len/2;
        back_len = buffer_len/2 + buffer_len%2;
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
    if(str == NULL)
    {
        return -1;
    }
    /* MAIN LOGIC */

    int del_count = 0;
    del_count += trim_front(str, char_to_del);
    del_count += trim_end(str, char_to_del);
    return del_count;
}

int trim_front(char str[], char char_to_del)
{
    if(str == NULL)
    {
        return -1;
    }
    /* MAIN LOGIC */

    int i, k;
    for(i = 0; str[i] != '\0' && str[i] == char_to_del; i++);
    for(k = i; k != '\0'; k++)
    {
        str[k - i] = str[k];
    }
    str[k] = '\0';
    return i;
}

int trim_end(char str[], char char_to_del)
{
    if(str == NULL)
    {
        return -1;
    }
    /* MAIN LOGIC */

    int max_idx = strlen(str) - 1;
    int i = max_idx;
    for(; str[i] == char_to_del && i >= 0; i--);
    str[i + 1] = '\0';
    return max_idx - i;
}

char* str_to_upper(char str[])
{
    if(str == NULL)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    for(int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

char* str_to_lower(char str[])
{
    if(str == NULL)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    for(int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

char* remove_newline(char str[])
{
    if(str == NULL)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    int last_idx = strlen(str) - 1;
    if(str[0] != '\0' && str[last_idx] == '\n')
    {
        str[last_idx] = '\0';
    }
    return str;
}

char* case_format(char str[])
{
    if(str == NULL)
    {
        return NULL;
    }
    /* MAIN LOGIC */
    
    int len = strlen(str);
    str[0] = toupper(str[0]);
    for(int i = 1; i < len; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}