#ifndef __MOCK_H__
#define __MOCK_H__

#include <stdbool.h>

#include <minesweeper/minesweeper.h>

/** Opaque structure of a minesweeper game */
typedef struct game game_t;

/**
 * Create a new game of minesweeper.
 *
 * @param width Width of the grid.
 * @param heigh Height of the grid.
 * @param mines Number of mines in the grid.
 *
 * @return Opaque structure handling the game.
 */
game_t*
mock_game_new(unsigned width, unsigned heigh, unsigned mines);

/**
 * Destroy a game.
 *
 * @param game game previsouly allocated with @c mock_game_new.
 */
void
mock_game_destroy(game_t* game);

/**
 * Dump the current grid from the player point of view.
 *
 * @param game Handle of a game.
 */
void
mock_game_dump(game_t* game);

/**
 * Dump the solution grid.
 *
 * @param game Handle of a game.
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
 *
 * @param Handle of a game.
 * @param Action to be done.
 * @param coord Cell on the action has to be done.
 */
enum ret
mock_game_play(game_t* game, enum action action, const struct coord* cell);

#endif /* !__GAME_H__ */
