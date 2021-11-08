#ifndef __GAME_H__
#define __GAME_H__

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

#endif /* !__GAME_H__ */
