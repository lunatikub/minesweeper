#ifndef __DEBUG_H__
#define __DEBUG_H__

// Uncomment to enable DEBUG
#define DEBUG

#ifdef DEBUG

#include <stdio.h>
#define DBG(format, ...)                                                       \
  printf("[%s][%s:%i] " format, MODULE, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define DBG_GRID(GRID, NAME)                                                   \
  do {                                                                         \
    DBG("grid: %s\n", NAME);                                                   \
    unsigned i, j;                                                             \
    printf("     ");                                                           \
    for (i = 0; i < GRID->width; ++i) {                                        \
      printf("[%2u] ", i);                                                     \
    }                                                                          \
    printf("\n");                                                              \
    for (i = 0; i < GRID->height; ++i) {                                       \
      printf("[%2u]", i);                                                      \
      for (j = 0; j < GRID->width; ++j) {                                      \
        unsigned v = GRID->cells[i * GRID->width + j];                         \
        if (v == 0) {                                                          \
          printf("   - ");                                                     \
        } else if (v == COVERED) {                                             \
          printf("   C ");                                                     \
        } else if (v == FLAGGED || v == MINE) {                                \
          printf("   F ");                                                     \
        } else {                                                               \
          printf("%4u ", GRID->cells[i * GRID->width + j]);                    \
        }                                                                      \
      }                                                                        \
      printf("\n");                                                            \
    }                                                                          \
  } while (0)

#define DBG_CFG(CFG)                                                           \
  do {                                                                         \
    unsigned i, j;                                                             \
    DBG("unsolved\n");                                                         \
    for (i = 0; i < CFG->nr_unsolved; ++i) {                                   \
      printf(" + (%u:%u): ", CFG->unsolved[i].x, CFG->unsolved[i].y);          \
      for (j = 0; j < CFG->nr_edge[i]; ++j) {                                  \
        printf("%u, ", CFG->edges[i][j]);                                      \
      }                                                                        \
      printf("\n");                                                            \
    }                                                                          \
    DBG("covered\n");                                                          \
    for (i = 0; i < CFG->nr_covered; ++i) {                                    \
      printf(" + (%u:%u)\n", CFG->covered[i].x, CFG->covered[i].y);            \
    }                                                                          \
  } while (0)

#define DBG_MATRIX(MATRIX, NAME)                                               \
  do {                                                                         \
    DBG("matrix: %s\n", NAME);                                                 \
    unsigned i, j;                                                             \
    printf("     ");                                                           \
    for (i = 0; i < MATRIX->n; ++i) {                                          \
      printf("[%2u] ", i);                                                     \
    }                                                                          \
    printf("\n");                                                              \
    for (i = 0; i < MATRIX->m; ++i) {                                          \
      printf("[%2u]", i);                                                      \
      for (j = 0; j < MATRIX->n; ++j) {                                        \
        printf("%4i ", (int)MATRIX->e[i][j]);                                  \
      }                                                                        \
      printf("\n");                                                            \
    }                                                                          \
  } while (0)

#define DBG_SOLUTION(SOL)                                                      \
  do {                                                                         \
    unsigned i = 0;                                                            \
    DBG("empty %u\n", SOL->nr_empty);                                          \
    for (i = 0; i < SOL->nr_empty; ++i) {                                      \
      printf(" + (%u:%u)\n", SOL->empty[i].x, SOL->empty[i].y);                \
    }                                                                          \
    DBG("mines %u\n", SOL->nr_mine);                                           \
    for (i = 0; i < solution->nr_mine; ++i) {                                  \
      printf(" + (%u:%u)\n", SOL->mines[i].x, SOL->mines[i].y);                \
    }                                                                          \
  } while (0)

#else

#define LOG(str, ...)
#define DBG_GRID(GRID, NAME)
#define DBG_CFG(CFG)

#endif /* !DEBUG */

#endif /* !__DEBUG_H__ */
