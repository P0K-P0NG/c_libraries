#include "check_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 100

static bool _test_isStrAlpha()
{
    struct _TestCase {
        char input1[MAX_CHAR];
        size_t input2;
        bool ans;
    };
    struct _TestCase test_cases[]
        = {{"acbcie", 6, true},  {"A", 1, true},
           {" d", 0, true},      {"d", 1, true},
           {"AdqwdfY", 7, true}, {"ad sb", 2, true},
           {"17689", 0, true},   {" 8", 0, true},
           {"0", 0, true},       {"scfa34d678f", 4, true},
           {"acbcie", 7, false}, {"A", -1, true},
           {" d", -1, false},    {"d", -1, true},
           {"AdqwdfY", 3, true}, {"ad sb", 3, false},
           {"17689", -1, false}, {" 8", 1, false},
           {"0", -1, false},     {"scfa34d678f", 5, false}};

    size_t test_count = sizeof(test_cases) / sizeof(struct _TestCase);

    printf("BEGIN %s\n", __func__);
    bool is_ok = true;
    for (size_t i = 0; i < test_count; i++) {
        struct _TestCase test = test_cases[i];
        bool res = isStrAlpha(test.input1, test.input2);
        if (res != test.ans) {
            is_ok = false;
            printf("test: (%s, %lu) \t->\t res: %d | ans: %d\n", test.input1,
                   test.input2, res, test.ans);
        }
    }
    printf("END %s\n", __func__);
    return is_ok;
}

static bool _test_isStrDigit()
{
    struct _TestCase {
        char input1[MAX_CHAR];
        size_t input2;
        bool ans;
    };
    struct _TestCase test_cases[]
        = {{"acbcie", 0, true},   {"A", 0, true},
           {" d", 0, true},       {"d", 0, true},
           {"AdqwdfY", 0, true},  {"ad sb", 0, true},
           {"17689", 5, true},    {" 8", -1, false},
           {"0", 1, true},        {"scfa34d678f", 0, true},
           {"acbcie", -1, false}, {"A", 1, false},
           {" d", 1, false},      {"d", -1, false},
           {"AdqwdfY", 4, false}, {"ad sb", -1, false},
           {"17689", -1, true},   {" 8", 2, false},
           {"0", -1, true},       {"scfa34d678f", 5, false}};

    size_t test_count = sizeof(test_cases) / sizeof(struct _TestCase);

    printf("BEGIN %s\n", __func__);
    bool is_ok = true;
    for (size_t i = 0; i < test_count; i++) {
        struct _TestCase test = test_cases[i];
        bool res = isStrDigit(test.input1, test.input2);
        if (res != test.ans) {
            is_ok = false;
            printf("test: (%s, %lu) \t->\t res: %d | ans: %d\n", test.input1,
                   test.input2, res, test.ans);
        }
    }
    printf("END %s\n", __func__);
    return is_ok;
}

static bool _test_isStrInt()
{
    struct _TestCase {
        char input1[MAX_CHAR];
        size_t input2;
        bool ans;
    };
    struct _TestCase test_cases[]
        = {{"acbcie", 0, true},     {"A", 0, true},
           {" d", 0, true},         {"d", 0, true},
           {"AdqwdfY", 0, true},    {"ad sb", 0, true},
           {"17689", 5, true},      {" 8", 0, true},
           {"0", 1, true},          {"scfa34d678f", 0, true},
           {"-10", 3, true},        {"- 10", 0, true},
           {"01", 0, true},         {"-0", 2, true},
           {"-14a", 3, true},       {"oo-10", 0, true},
           {"oo10", 0, true},       {"--0", 0, true},
           {"1.03", 1, true},       {"0.0023", 1, true},
           {"-108.028", 4, true},   {"oo1.0", 0, true},
           {"1.a03", 1, true},      {"1.03a", 1, true},
           {"--0.0023", 0, true},   {".028", 0, true},
           {"-.028", 0, true},

           {"acbcie", -1, false},   {"A", -1, false},
           {" d", -1, false},       {"d", -1, false},
           {"AdqwdfY", -1, false},  {"ad sb", -1, false},
           {"17689", -1, true},     {" 8", -1, false},
           {"0", -1, true},         {"scfa34d678f", -1, false},
           {"-10", -1, true},       {"- 10", -1, false},
           {"01", -1, false},       {"-0", -1, true},
           {"-14a", -1, false},     {"oo-10", -1, false},
           {"oo10", -1, false},     {"--0", -1, false},
           {"1.03", -1, false},     {"0.0023", -1, false},
           {"-108.028", -1, false}, {"oo1.0", -1, false},
           {"1.a03", -1, false},    {"1.03a", -1, false},
           {"--0.0023", -1, false}, {".028", -1, false},
           {"-.028", -1, false}};

    size_t test_count = sizeof(test_cases) / sizeof(struct _TestCase);

    printf("BEGIN %s\n", __func__);
    bool is_ok = true;
    for (size_t i = 0; i < test_count; i++) {
        struct _TestCase test = test_cases[i];
        bool res = isStrInt(test.input1, test.input2);
        if (res != test.ans) {
            is_ok = false;
            printf("test: (%s, %lu) \t->\t res: %d | ans: %d\n", test.input1,
                   test.input2, res, test.ans);
        }
    }
    printf("END %s\n", __func__);
    return is_ok;
}

static bool _test_isStrFloat()
{
    struct _TestCase {
        char input1[MAX_CHAR];
        size_t input2;
        bool ans;
    };
    struct _TestCase test_cases[]
        = {{"acbcie", 0, true},    {"A", 0, true},
           {" d", 0, true},        {"d", 0, true},
           {"AdqwdfY", 0, true},   {"ad sb", 0, true},
           {"17689", 5, true},     {" 8", 0, true},
           {"0", 1, true},         {"scfa34d678f", 0, true},
           {"-10", 3, true},       {"- 10", 0, true},
           {"01", 0, true},        {"-0", 2, true},
           {"-14a", 3, true},      {"oo-10", 0, true},
           {"oo10", 0, true},      {"--0", 0, true},
           {"1.03", 4, true},      {"0.0023", 6, true},
           {"-108.028", 8, true},  {"oo1.0", 0, true},
           {"1.a03", 1, true},     {"1.03a", 3, true},
           {"--0.0023", 0, true},  {".028", 0, true},
           {"-.028", 0, true},

           {"acbcie", -1, false},  {"A", -1, false},
           {" d", -1, false},      {"d", -1, false},
           {"AdqwdfY", -1, false}, {"ad sb", -1, false},
           {"17689", -1, true},    {" 8", -1, false},
           {"0", -1, true},        {"scfa34d678f", -1, false},
           {"-10", -1, true},      {"- 10", -1, false},
           {"01", -1, false},      {"-0", -1, true},
           {"-14a", -1, false},    {"oo-10", -1, false},
           {"oo10", -1, false},    {"--0", -1, false},
           {"1.03", -1, true},     {"0.0023", 3, true},
           {"-108.028", -1, true}, {"oo1.0", -1, false},
           {"1.a03", 2, false},    {"1.03a", -1, false},
           {"--0.0023", 1, false}, {".028", -1, false},
           {"-.028", -1, false}};

    size_t test_count = sizeof(test_cases) / sizeof(struct _TestCase);

    printf("BEGIN %s\n", __func__);
    bool is_ok = true;
    for (size_t i = 0; i < test_count; i++) {
        struct _TestCase test = test_cases[i];
        bool res = isStrFloat(test.input1, test.input2);
        if (res != test.ans) {
            is_ok = false;
            printf("test: (%s, %lu) \t->\t res: %d | ans: %d\n", test.input1,
                   test.input2, res, test.ans);
        }
    }
    printf("END %s\n", __func__);
    return is_ok;
}

// static bool _test_getIntStrLength()
// {
//     struct _TestCase {
//         char input1[MAX_CHAR];
//         char *input2;
//         int ans;
//     };
//     struct _TestCase test_cases[]
//         = {{"acbcie", NULL, 0},    {"A", NULL, 0},
//            {" d", NULL, 0},        {"d", NULL, 0},
//            {"AdqwdfY", NULL, 0},   {"ad sb", NULL, 0},
//            {"17689", NULL, 5},     {" 8", NULL, 0},
//            {"0", NULL, 1},         {"scfa34d678f", NULL, 0},
//            {"-10", NULL, 3},       {"- 10", NULL, 0},
//            {"01", NULL, 0},        {"-0", NULL, 2},
//            {"-14a", ".", 0},       {"-14a", "a", 3},
//            {"oo-10", NULL, 0},     {"oo10", NULL, 0},
//            {"--0", NULL, 0},       {"1.03", NULL, 0},
//            {"0.0023", "\\.00", 1}, {"-108.028", "\\.[0-9]\\{3\\}", 4},
//            {"oo1.0", NULL, 0},     {"1.a03", "\\.", 1},
//            {"1.03a", NULL, 0},     {"--0.0023", NULL, 0},
//            {".028", NULL, 0},      {"-.028", NULL, 0}};
//     size_t test_count = sizeof(test_cases) / sizeof(struct _TestCase);

//     printf("BEGIN %s\n", __func__);
//     bool is_ok = true;
//     for (size_t i = 0; i < test_count; i++) {
//         struct _TestCase test = test_cases[i];
//         int res = getIntStrLength(test.input1, test.input2);
//         if (res != test.ans) {
//             is_ok = false;
//             printf("test: (%s, %s) \t->\t res: %d | ans: %d\n", test.input1,
//                    test.input2, res, test.ans);
//         }
//     }
//     printf("END %s\n", __func__);
//     return is_ok;
// }

// static bool _test_getFloatStrLength()
// {
//     struct _TestCase {
//         char input[MAX_CHAR];
//         size_t ans;
//     };
//     struct _TestCase test_cases[]
//         = {{"acbcie", 0},   {"A", 0},           {" d", 0},    {"d", 0},
//            {"AdqwdfY", 0},  {"ad sb", 0},       {"17689", 5}, {" 8", 0},
//            {"0", 1},        {"scfa34d678f", 0}, {"-10", 3},   {"- 10", 0},
//            {"01", 0},       {"-0", 2},          {"-14a", 3},  {"oo-10", 0},
//            {"oo10", 0},     {"--0", 0},         {"1.03", 4},  {"0.0023", 6},
//            {"-108.028", 8}, {"oo1.0", 0},       {"1.a03", 1}, {"1.03a", 4},
//            {"--0.0023", 0}, {".028", 0},        {"-.028", 0}};
//     size_t test_count = sizeof(test_cases) / sizeof(struct _TestCase);

//     printf("BEGIN %s\n", __func__);
//     bool is_ok = true;
//     for (size_t i = 0; i < test_count; i++) {
//         struct _TestCase test = test_cases[i];
//         bool res = getFloatStrLength(test.input);
//         if (res != test.ans) {
//             is_ok = false;
//             printf("test: %s \t->\t res: %lu | ans: %lu\n", test.input, res,
//                    test.ans);
//         }
//     }
//     printf("END %s\n", __func__);
//     return is_ok;
// }

int main()
{
    bool is_ok = true;
    is_ok &= _test_isStrAlpha();
    is_ok &= _test_isStrDigit();
    is_ok &= _test_isStrInt();
    is_ok &= _test_isStrFloat();
    if (is_ok) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}