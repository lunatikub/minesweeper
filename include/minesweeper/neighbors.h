#ifndef __NEIGHBORS_H__
#define __NEIGHBORS_H__

#include <minesweeper/minesweeper.h>

/**
 * Relative coordinate of neighbors.
 */
/* clang-format off */
const static struct coord neighbors[] = {
    { -1, -1 }, { -1, 0 }, { -1, 1 },
    {  0, -1 },            {  0, 1 },
    {  1, -1 }, {  1, 0 }, {  1, 1 },
};
/* clang-format on */

/**
 * Execute the 'CODE' foreach valid neighbor.
 * Pprovide the variable 'neighbor' of type struct coord.
 *   + 'G': is The current grid.
 *   + 'X': Source cell coord.
 *   + 'Y': Source cell coord.
 *   + 'CODE': code to execute.
 */
#define FOREACH_NEIGHBORS(G, X, Y, CODE)                                       \
  do {                                                                         \
    const struct coord* N;                                                     \
    unsigned END = sizeof(neighbors) / sizeof(struct coord);                   \
    for (N = &neighbors[0]; N != &neighbors[END]; ++N) {                       \
      const struct coord neighbor = { (X) + N->x, (Y) + N->y };                \
      if (neighbor.y >= 0 && neighbor.y < G->height && neighbor.x >= 0 &&      \
          neighbor.x < G->width) {                                             \
        CODE;                                                                  \
      }                                                                        \
    }                                                                          \
  } while (0)

#endif /* !__NEIGHBORS_H__ */
