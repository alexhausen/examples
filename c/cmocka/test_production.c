
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "production.h"
#include "dependency.h"

int dep(int param, int* out_param) {
  printf("mock dep param %d\n", param);
  check_expected(param);
  return (int)mock();
}

static void test_fun(void **state) {
    (void) state;

    expect_value(dep, param, 1000);
    will_return(dep, 2);

    assert_true(fun() == 3);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_fun),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
