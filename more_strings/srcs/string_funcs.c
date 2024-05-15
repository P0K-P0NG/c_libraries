/**
 * @file string_funcs.h
 * 
 * @brief 
 *  Functions for strings.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include <string.h>
#include <ctype.h>
#include "string_funcs.h"

int splitStr(char str[], char *substrs[], int count, char delimiter[])
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

char *strAddBuffer(
    String str_block, int buffer_len[2], char buffer_char)
{
    char *str = str_block.items;
    int max_len = str_block.len;

    if(str == NULL)
    {
        return NULL;
    }
    /* MAIN LOGIC */

    char temp_str[strlen(str) + 1];
    strcpy(temp_str, str);
    memset(str, buffer_char, buffer_len[0]);
    strcpy(&str[buffer_len[0]], temp_str);
    memset(&str[buffer_len[0] + strlen(temp_str)], buffer_char, buffer_len[1]);
    str[max_len - 1] = '\0';
    return str;
}

char *strAlign(String str_block, char mode, char buffer_char)
{
    char *str = str_block.items;
    int max_len = str_block.len;
    
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
    del_count += trimFront(str, char_to_del);
    del_count += trimEnd(str, char_to_del);
    return del_count;
}

int trimFront(char str[], char char_to_del)
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

int trimEnd(char str[], char char_to_del)
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

char *strToUpper(char str[])
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

char *strToLower(char str[])
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

char *removeNewline(char str[])
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

char *caseFormat(char str[])
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