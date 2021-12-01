#ifndef __MOCK_H__
#define __MOCK_H__

#include <stdbool.h>

#include <minesweeper/minesweeper.h>

/** Opaque structure of a minesweeper game */
typedef struct game game_t;

/**
 * Create a new game of minesweeper with a grid
 * of size 'width' x 'heigh' and 'mines' number of mines.
 */
game_t*
mock_game_new(unsigned width, unsigned heigh, unsigned mines);

/**
 * Destroy a game previously created by 'mock_game_new'.
 */
void
mock_game_destroy(game_t* game);

/**
 * Dump the current grid from the player point of view.
 */
void
mock_game_dump(game_t* game);

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
mock_game_play(game_t* game, enum action action, const struct coord* cell);

#endif /* !__GAME_H__ */
