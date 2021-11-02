#ifndef __MOCK_H__
#define __MOCK_H__

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
 * Destroy a game previously allocated with @c mock_game_new.
 */
void
mock_game_destroy(game_t* game);

/**
 * Dump the current grid from the player point of view.
 */
void
mock_game_dump(game_t* game);

#endif /* !__GAME_H__ */
