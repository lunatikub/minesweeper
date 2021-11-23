#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <stdbool.h>

#include <minesweeper/grid.h>

/* 0 to 8 are used for uncovered cell */
enum
{
  EMPTY = 0,
  COVERED = 9,
  FLAGGED = 10,
  MINE = FLAGGED,
};

/**
 * Coordinates of a cell in the grid.
 */
struct coord
{
  unsigned x;
  unsigned y;
};

/**
 * If the number contained in an uncovered cell at position {i,j} is called
 * C{i,j} and the number of flagged adjacent mines is called F{i,j} then:
 *  + a cell is unsolved if C{i,j} < F{i,j}: return false
 *  + a cell is solved if C{i,j} = F{i,j}: return true
 */
bool
is_solved(const struct grid* grid, unsigned x, unsigned y);

/**
 * Return true if the both coordinates are adjacent, otherwise return false.
 */
bool
is_adjacent(struct coord* c1, struct coord* c2);

#endif /* !__MINESWEEPER_H__ */
