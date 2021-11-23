#include <minesweeper/minesweeper.h>
#include <minesweeper/neighbors.h>

bool
is_solved(const struct grid* grid, unsigned x, unsigned y)
{
  unsigned v = GET(grid, x, y);
  unsigned nr = 0;

  /* not an uncovered cell */
  if (v > 8) {
    return false;
  }

  /* clang-format off */
  FOREACH_NEIGHBORS(
    grid, x, y,
    if (GET(grid, neighbor.x, neighbor.y) == FLAGGED) {
      ++nr;
    });
  /* clang-format on */

  return v == nr;
}

bool
is_adjacent(struct coord* c1, struct coord* c2)
{
  int dx = c1->x - c2->x;
  int dy = c1->y - c2->y;
  return dx >= -1 && dx <= 1 && dy >= -1 && dy <= 1;
}
