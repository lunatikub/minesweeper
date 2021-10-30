#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utest.h"

static inline uint64_t
get_ns(void)
{
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
    abort();
  }
  return ts.tv_sec * UINT64_C(1000000000) + ts.tv_nsec;
}

const struct test*
find_test(const struct test_suite* ts, const char* name)
{
  for (uint32_t i = 0; i < ts->nr_test; i++) {
    if (strcmp(ts->tests[i].name, name) == 0) {
      return &ts->tests[i];
    }
  }
  return NULL;
}

bool
run_test(const struct test* t)
{
  bool ok = true;
  printf(" -\n");
  printf(YELLOW " [start test] " PURPLE "(%s)" RESET BOLD " %s\n" RESET,
         t->section,
         t->name);
  const uint64_t start = get_ns();
  ok = t->test_f();
  const uint64_t end = (get_ns() - start) / 1000;
  const char* res = ok ? GREEN "OK" RESET : RED "KO" RESET;
  printf(YELLOW " [end test] %s (%lums)\n", res, end);
  return ok;
}

bool
run_test_suite(const struct test_suite* ts)
{
  bool ok = true;
  const struct test* t;
  printf(CYAN "[start test suite] " BOLD "%s\n" RESET, ts->name);
  const uint64_t start = get_ns();
  for (t = &ts->tests[0]; t != &ts->tests[ts->nr_test]; ++t) {
    if (run_test(t) == false) {
      ok = false;
      break;
    }
  }
  const uint64_t end = (get_ns() - start) / 1000;
  const char* res = ok ? GREEN "OK" RESET : RED "KO" RESET;
  printf(CYAN "[end test suite] %s (%lums)\n", res, end);
  return ok;
}
