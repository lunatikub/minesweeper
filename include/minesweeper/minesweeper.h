#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

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

#endif /* !__MINESWEEPER_H__ */
