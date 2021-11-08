/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(game, lost)
{
  CFG(3, 3, 9);
  struct game* game = mock_game_new(w, h, m); /* Fill all cells with mines */

  /* out of bounds */
  EXPECT_FALSE(mock_game_play(game, SET_EMPTY, 4, 4));

  /* set an empty cell on a mine */
  EXPECT_FALSE(mock_game_play(game, SET_EMPTY, 1, 1));

  mock_game_destroy(game);
  return true;
}
