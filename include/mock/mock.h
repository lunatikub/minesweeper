#ifndef __MOCK_H__
#define __MOCK_H__

#include <stdbool.h>

#include <minesweeper/minesweeper.h>

/**
 * Mock a minesweeper game.
 */
struct game
{
  struct grid* solution; // grid with the mines and numbers of adjacent
  struct grid* current;  // current grid for the player
  unsigned mines;
  unsigned flagged;
  unsigned flagged_mines;
  unsigned covered;
  unsigned turn;
};

/**
 * Create a new game of minesweeper with a grid
 * of size 'width' x 'heigh' and 'mines' number of mines.
 * Set 'first_move' (if not NULL) in order to play the first move.
 */
struct game*
mock_game_new(unsigned width,
              unsigned heigh,
              unsigned mines,
              struct coord* first_move);

/**
 * Destroy a game previously created by 'mock_game_new'.
 */
void
mock_game_destroy(struct game* game);

/**
 * Dump the current grid from the player point of view.
 */
void
mock_game_dump(struct game* game);

/**
 * Dump the solution grid.
 */
void
mock_game_dump_solution(struct game* game);

/** List of the different actions can be done for a play. */
enum action
{
  FLAG,
  UNFLAG,
  SET_EMPTY,
};

/** List of the different results after a play. */
enum ret
{
  LOST,
  WON,
  OK,
};

/**
 * Flag, unflag or set an empty cell.
 */
enum ret
mock_game_play(struct game* game, enum action action, const struct coord* cell);

#endif /* !__GAME_H__ */
