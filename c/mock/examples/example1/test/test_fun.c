#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "fun.h"

//------------------
//#include "tf/mock.h"
//#include "tf/test.h"
//------------------

//typedef enum { type_int, type_string, type_double, type_void_ptr } type_t;

typedef struct {
  void* value;
  unsigned size_in_bytes;
  char* type_name;
} mock_value_t;

typedef struct {
  char* name;
  /*mock_value_t*/ int values[100];
  unsigned values_size;
  bool always;
} mock_in_param_t;

typedef struct {
  char* name;
  unsigned calls;
  unsigned expect_calls;
  mock_in_param_t in_params[100];
  unsigned in_params_size;
  //out_params
  /*mock_value_t*/int returns[100];
  unsigned returns_size;
  bool always;
  //char* return_type;
} mock_t;

/*
typedef struct {
  char* name;
  char* message;
  bool passed;
  bool ignore;
} test_case_t;

typedef struct {
  test_case_t test_cases;
  //void(*) setup;
  //void(*) teardown;
} test_fixture_t;

typedef struct {
  test_fixture_t fixtures[100];  
  unsigned fixtures_size;
  //void(*) global_setup;
  //void(*) global_teardown;
} test_suite_t;
*/

static mock_t g_mocks[100];
static unsigned g_mocks_size = 0;

void g_mocks_reset() {
  for (unsigned i = 0; i < g_mocks_size; ++i) {
    free(g_mocks[i].name);
  }
  g_mocks_size = 0;
}

mock_t* mock_add(const char* name) {
  mock_t* mock = &g_mocks[g_mocks_size];
  ++g_mocks_size;
  mock->name = NULL;
  mock->expect_calls = 0;
  mock->calls = 0;
  mock->in_params_size = 0;
  mock->returns_size = 0;
  mock->always = false;
  return mock;
}

mock_t* mock_find(const char* name) {
  for (unsigned i = 0; i < g_mocks_size; ++i) {
    if (strcmp(g_mocks[i].name, name) == 0) {
      return &g_mocks[i];
    }
  }
  return NULL;
}

int mock_return(const char* name) {
  mock_t* mock = mock_find(name);
  assert(mock);
  unsigned i = mock->always ? 0 : mock->calls - 1;
  int x = mock->returns[i];
//  printf("x = %d\n", x);
  return x;
}

mock_in_param_t* mock_in_param_add(mock_t* mock, const char* param_name) {
  assert(mock);
  mock_in_param_t* param = &mock->in_params[mock->in_params_size];
  ++(mock->in_params_size);
  param->name = strdup(param_name);
  param->values_size = 0;
  param->always = false;
  return param;
}

mock_in_param_t* mock_in_param_find(mock_t* mock, const char* param_name) {
  assert(mock);
  for (unsigned i = 0; i < mock->in_params_size; ++i) {
    if (strcmp(mock->in_params[i].name, param_name) == 0) {
      return &mock->in_params[i];
    }
  }
  return NULL;
}  

void expect_call(const char* name, unsigned expect_calls) {
  mock_t* mock = mock_find(name);
  if (!mock) {
    mock = mock_add(name);
  }
  mock->name = strdup(name);
  mock->expect_calls = expect_calls;
}

void mock_call(const char* name) {
  mock_t* mock = mock_find(name);
  assert(mock);
  mock->calls++;
}

void expect_param_always(const char* function_name, const char* param_name, int value) {
  mock_t* mock = mock_find(function_name);
  mock_in_param_t* param = mock_in_param_find(mock, param_name);
  if (!param) {
    param = mock_in_param_add(mock, param_name);
  }
  param->values[0] = value;
  param->values_size = 1;
  param->always = true;
}

void expect_param(const char* function_name, const char* param_name, int value, unsigned times) {
  mock_t* mock = mock_find(function_name);
  mock_in_param_t* param = mock_in_param_find(mock, param_name);
  if (!param) {
    param = mock_in_param_add(mock, param_name);
  }
  param->always = false;
  for (unsigned i = 0; i < times; ++i) {
    param->values[param->values_size] = value;
    //printf("expect value = %d (%u)\n", value, param->values_size);
    ++(param->values_size);
  }
}

void will_return_always(const char* name, int value) {
  mock_t* mock = mock_find(name);
  assert(mock);
  mock->returns[0] = value;
  mock->returns_size = 1;
  mock->always = true;
}

void will_return(const char* name, int value, unsigned times) {
  mock_t* mock = mock_find(name);
  assert(mock);
  mock->always = false;
  for (unsigned i = 0; i < times; ++i) {
    mock->returns[i] = value;
    ++(mock->returns_size);
  }
}

void mock_check_param(const char* function_name, const char* param_name, const int value) {
  mock_t* mock = mock_find(function_name);
  mock_in_param_t* param = mock_in_param_find(mock, param_name);
  assert(param);
  //printf("check %d = %d (%u)\n", value, param->values[mock->calls - 1], mock->calls);
  assert(value == param->values[mock->calls - 1]);
}

/*
void test_case_init(test_case_t* tc, const char* name, const char* message, bool ignore) {
  tc->name = strdup(name);
  tc->message = strdup(message);
  tc->passed = false;
  tc->ignore = ignore;
}
*/

void verify_expectations() {
  for (unsigned i = 0; i < g_mocks_size; ++i) {
    mock_t* mock = &g_mocks[i];
    assert(mock->expect_calls == mock->calls);
  }
}

//TODO MOCK(dep, int(int in, int* out));

int dep(int in, int* out) {
  mock_call("dep");
  //printf("mock dep\n");
  mock_check_param("dep", "in", in); //TODO generalize it
  //mock_set_param("dep", "out", out);
  *out = 3;
  return mock_return("dep");
}

//TEST(fun, "should do x") {
void test_fun() {
//  test_case_t tc;
//  test_case_init(&tc, __func__, "should do x", false);
//  if (tc->setup) tc->setup();
  g_mocks_reset();
  expect_call("dep", 2/*two calls*/);
  expect_param("dep", "in", /*int*/ 5, 2/*twice with the same values for parameter in*/);
//  SET_PARAM(dep, out, {3});
  will_return_always("dep", 1);
  assert(fun("hello") == 7); // == 2 * 3 + 1
  assert(fun("world") == 7);
  verify_expectations();
//  if (tc->teardown) tc->teardown();
}

int main() {
//  TEST_FIXTURE(setup, teardown);
  test_fun();
  return 0;
}
