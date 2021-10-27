#ifndef __NEIGHBORS_H__
#define __NEIGHBORS_H__

#include <solver.h>

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
 * Foreach valid neighbor: call the function given in
 * parameter with the source and destination coordinates.
 *
 * @param G The current grid
 * @param X Source cell coord
 * @param Y Source cell coord
 * @param F Function to call for each valid neighbor
 * @param A Argument of the function
 */
#define FOREACH_NEIGHBORS(G, X, Y, F, A)                                       \
  do {                                                                         \
    const struct coord* N;                                                     \
    const struct coord SRC = { (X), (Y) };                                     \
    unsigned END = sizeof(neighbors) / sizeof(struct coord);                   \
    for (N = &neighbors[0]; N != &neighbors[END]; ++N) {                       \
      const struct coord DST = { (X) + N->x, (Y) + N->y };                     \
      if (DST.y >= 0 && DST.y < G->height && DST.x >= 0 && DST.x < G->width) { \
        F(G, &SRC, &DST, A);                                                   \
      }                                                                        \
    }                                                                          \
  } while (0)

#endif /* !__NEIGHBORS_H__ */
