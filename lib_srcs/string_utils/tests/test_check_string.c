#include "check_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 100

static bool _test_isStrAlpha()
{
    struct _TestCase {
        char input[MAX_CHAR];
        bool ans;
    };
    struct _TestCase test_cases[]
        = {{"acbcie", true}, {"AY", true},     {"AdqwdfY", true},
           {"ad sb", false}, {"17689", false}, {"scfa34d678f", false}};
    size_t test_count = sizeof(test_cases) / sizeof(struct _TestCase);

    printf("BEGIN %s", __func__);
    bool is_ok = true;
    for (size_t i = 0; i < test_count; i++) {
        struct _TestCase test = test_cases[i];
        bool res = isStrAlpha(test.input);
        if (res != test.ans) {
            is_ok = false;
            printf("test: %s \t->\t res: %d | ans: %d", test.input, res,
                   test.ans);
        }
    }
    printf("END %s", __func__);
    return is_ok;
}

int main()
{
    bool is_ok = true;
    is_ok &= _test_isStrAlpha();
    if (is_ok) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}