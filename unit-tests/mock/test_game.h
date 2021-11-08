/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(game, lost)
{
  CFG(3, 3, 9);
  struct game* game = mock_game_new(w, h, m); /* Fill all cells with mines */

  /* out of bounds */
  struct coord C1 = { 4, 4 };
  EXPECT_FALSE(mock_game_play(game, SET_EMPTY, &C1));

  /* set an empty cell on a mine */
  struct coord C2 = { 1, 1 };
  EXPECT_FALSE(mock_game_play(game, SET_EMPTY, &C2));

  mock_game_destroy(game);
  return true;
}

TEST_F(game, set_empty)
{
  CFG(5, 5, 3);
  struct game* game = mock_game_new(w, h, m);

  struct coord not_mine;
  EXPECT_TRUE(find_first_not_mine(game->solution, &not_mine));
  EXPECT_TRUE(mock_game_play(game, SET_EMPTY, &not_mine));

  mock_game_destroy(game);
  return true;
}
