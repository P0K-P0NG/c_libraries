#include "string_funcs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

static void _printStrLists(char *strs[], size_t count)
{
    printf("%s", strs[0]);
    for (size_t i = 1; i < count; i++) {
        printf(", %s", strs[i]);
    }
}

static bool _testCase_joinStrs(char *input3[], size_t input4, char *input5,
                               char ans[])
{
    char res[MAX_CHAR];
    char *ret = joinStrs(res, MAX_CHAR, input3, input4, input5);
    if (ret == NULL || strcmp(res, ans) != 0) {
        // Not using the joinStrs function to limit coupling
        printf("test: ({");
        _printStrLists(input3, input4);
        printf("}, %lu, %s) \t->\t res: \"%s\" | ans: \"%s\"\n", input4, input5,
               res, ans);

        return false;
    } else {
        return true;
    }
}

static bool _test_joinStrs()
{
    bool (*test)(char *[], size_t, char *, char[]) = _testCase_joinStrs;

    printf("BEGIN %s\n", __func__);

    bool is_ok = true;
    is_ok &= test((char *[]){"a", "b", "ie"}, 3, "c", "acbcie");
    is_ok &= test((char *[]){"ac", "cie"}, 2, "b", "acbcie");
    is_ok &= test((char *[]){"a", "ie"}, 2, "[bc]", "a[bc]ie");
    is_ok &= test((char *[]){"a", "b", "ie"}, 3, "c", "acbcie");
    is_ok &= test((char *[]){"ac", "cie"}, 2, "b", "acbcie");
    is_ok &= test((char *[]){"a", "ie"}, 2, "[bc]", "a[bc]ie");
    is_ok &= test((char *[]){"a", "bcie"}, 2, "c", "acbcie");
    is_ok &= test((char *[]){"ac", "cie"}, 2, "b", "acbcie");
    is_ok &= test((char *[]){"a", "bcie"}, 2, "[bc]", "a[bc]bcie");

    printf("END %s\n", __func__);
    return is_ok;
}

static bool _testCase_splitStr(char *input1, size_t input3, char *input4,
                               char *ans[], size_t ans_count)
{
    bool is_ok = true;
    char **res = calloc(input3, sizeof(char *));
    if (res == NULL) {
        perror("Program failed: %s");
        return false;
    }
    char buf[MAX_CHAR];
    strncpy(buf, input1, MAX_CHAR);
    size_t split_count = splitStr(buf, res, input3, input4);
    if (split_count != ans_count) {
        is_ok = false;
    } else {
        for (size_t i = 0; i < split_count; i++) {
            if (strcmp(res[i], ans[i]) != 0) {
                is_ok = false;
                break;
            }
        }
    }
    if (!is_ok) {
        char res_joined[MAX_CHAR], ans_joined[MAX_CHAR];
        if (joinStrs(res_joined, MAX_CHAR, res, split_count, ", ") == NULL
            || joinStrs(ans_joined, MAX_CHAR, ans, ans_count, ", ") == NULL)
            fprintf(stderr, "joinStrs buffer length exceeded.");

        printf("test: (%s, %lu, %s) \t->\t res: {%s} | ans: {%s}\n", input1,
               input3, input4, res_joined, ans_joined);
    }
    free(res);
    return is_ok;
}

static bool _test_splitStr()
{
    bool (*test)(char *, size_t, char *, char *[], size_t) = _testCase_splitStr;

    printf("BEGIN %s\n", __func__);

    bool is_ok = true;
    is_ok &= test("acbcie", 3, "c", (char *[]){"a", "b", "ie"}, 3);
    is_ok &= test("acbcie", 2, "b", (char *[]){"ac", "cie"}, 2);
    is_ok &= test("acbcie", 2, "[bc]", (char *[]){"a", "ie"}, 2);
    is_ok &= test("acbcie", 4, "c", (char *[]){"a", "b", "ie"}, 3);
    is_ok &= test("acbcie", 5, "b", (char *[]){"ac", "cie"}, 2);
    is_ok &= test("acbcie", 3, "[bc]", (char *[]){"a", "ie"}, 2);
    is_ok &= test("acbcie", 1, "c", (char *[]){"a"}, 1);
    is_ok &= test("acbcie", 1, "b", (char *[]){"ac"}, 1);
    is_ok &= test("acbcie", 1, "[bc]", (char *[]){"a"}, 1);

    is_ok &= test("AdqwdfY", 2, "[bc]", (char *[]){"AdqwdfY"}, 1);
    is_ok &= test("AdqwdfY", 3, "[[:lower:]]", (char *[]){"A", "Y"}, 2);
    is_ok &= test("ad sb", 3, "[ ]", (char *[]){"ad", "sb"}, 2);
    is_ok &= test("scfa34d678f", 3, "[[:alpha:]]", (char *[]){"34", "678"}, 2);
    is_ok &= test("scfa34d678f", 2, "[[:alnum:]]", (char *[]){""}, 1);

    printf("END %s\n", __func__);
    return is_ok;
}

static bool _testCase_removeRegexMatches(char *input1, char *input2, char ans[])
{
    bool is_ok = true;
    size_t buf_len = strlen(input1) + 1;
    char *res = calloc(buf_len, sizeof(char));
    if (res == NULL) {
        perror("Program failed: %s");
        return false;
    }
    memcpy(res, input1, buf_len);
    size_t count = removeRegexMatches(res, input2);
    if (strcmp(res, ans) != 0) {
        printf("test: (%s, %s) \t->\t res: %s | ans: %s\n", input1, input2, res,
               ans);
        is_ok = false;
    }
    free(res);
    return is_ok;
}

static bool _test_removeRegexMatches()
{
    bool (*test)(char[], char[], char[]) = _testCase_removeRegexMatches;

    printf("BEGIN %s\n", __func__);

    bool is_ok = true;
    is_ok &= test("acbcie", "c", "abie");
    is_ok &= test("acbcie", "b", "accie");
    is_ok &= test("acbcie", "[bc]", "aie");
    is_ok &= test("acbcie", "c", "abie");
    is_ok &= test("acbcie", "b", "accie");
    is_ok &= test("acbcie", "[bc]", "aie");
    is_ok &= test("acbcie", "c", "abie");
    is_ok &= test("acbcie", "b", "accie");
    is_ok &= test("acbcie", "[bc]", "aie");

    is_ok &= test("AdqwdfY", "[bc]", "AdqwdfY");
    is_ok &= test("AdqwdfY", "[[:lower:]]", "AY");
    is_ok &= test("ad sb", "[ ]", "adsb");
    is_ok &= test("scfa34d678f", "[[:alpha:]]", "34678");
    is_ok &= test("scfa34d678f", "[[:alnum:]]", "");

    printf("END %s\n", __func__);
    return is_ok;
}

int main()
{
    bool is_ok = true;
    is_ok &= _test_joinStrs();
    is_ok &= _test_splitStr();
    is_ok &= _test_removeRegexMatches();
    if (is_ok) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}