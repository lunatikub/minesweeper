#ifndef __TEST_H__
#define __TEST_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Colors */
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define YELLOW "\033[0;33m"

#define BOLD "\e[1m"

/* Declare a test. */
#define TEST_F(section, name) static bool test_##section##name(void)

/* clang-format off */
/* Add a test to the test suite. */
#define TEST(section, name)                                  \
  {                                                          \
    #section, #name, test_ ## section ## name                \
  }
/* clang-format on */

/**
 * Structure used to declare a test.
 * Use helper @c TEST.
 */
struct test
{
  char* section;
  char* name;
  bool (*test_f)(void);
};

/**
 * Structure used to declare a test suite.
 * Use helper @c TEST_SUITE.
 */
struct test_suite
{
  char* name;
  uint32_t nr_test;
  const struct test* tests;
};

/* Run a specific test. */
bool
run_test(const struct test* t);

/* Find a specific test in a test suite from the name.
 * Return NULL if not found. */
const struct test*
find_test(const struct test_suite* ts, const char* name);

/* Run a test suite. */
bool
run_test_suite(const struct test_suite* ts);

/* Declare a test suite. */
#define TEST_SUITE(name)                                                       \
  const static struct test_suite name##_test_suite = {                         \
    #name,                                                                     \
    sizeof(name##_tests) / sizeof(struct test),                                \
    name##_tests,                                                              \
  };                                                                           \
                                                                               \
  int main(void) { return run_test_suite(&name##_test_suite) ? 0 : -1; }

/********************************************************
 * Following macro are helpers to be used in the tests. *
 ********************************************************/

#define ERR                                                                    \
  fprintf(stderr,                                                              \
          RED " [test failed] " RESET "file:%s, line:%i\n",                    \
          __FILE__,                                                            \
          __LINE__)

#define EXPECT_UINT_EQ(V1, V2)                                                 \
  if (V1 != V2) {                                                              \
    fprintf(stderr,                                                            \
            RED " [test failed] " RESET "EXPECT_UINT_EQ(%s:%u,%s:%u)\n",       \
            #V1,                                                               \
            V1,                                                                \
            #V2,                                                               \
            V2);                                                               \
    ERR;                                                                       \
    return false;                                                              \
  }

#define EXPECT_INT_GT(V1, V2)                                                  \
  if (V1 < V2) {                                                               \
    fprintf(stderr,                                                            \
            RED " [test failed] " RESET "EXPECT_UINT_GET(%s:%i > %s:%i)\n",    \
            #V1,                                                               \
            V1,                                                                \
            #V2,                                                               \
            V2);                                                               \
    ERR;                                                                       \
    return false;                                                              \
  }

#define EXPECT_STR_EQ(S1, S2)                                                  \
  if (strlen(S1) != strlen(S2) || (strcmp(S1, S2) != 0)) {                     \
    fprintf(                                                                   \
      stderr, RED " [test failed] " RESET "EXPECT_STREQ(%s,%s)\n", S1, S2);    \
    ERR;                                                                       \
    return false;                                                              \
  }

#define EXPECT_TRUE(EXP)                                                       \
  if ((EXP) != true) {                                                         \
    fprintf(stderr, RED " [test failed] " RESET "EXPECT_TRUE(%s)\n", #EXP);    \
    ERR;                                                                       \
    return false;                                                              \
  }

/* Print information about the test. */
#define INFO(...)                                                              \
  printf(YELLOW " [info] " RESET __VA_ARGS__);                                 \
  printf("\n");

#endif /* !__TEST_H__ */
