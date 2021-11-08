/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(game, lost)
{
  CFG(3, 3, 9);
  struct game* game = mock_game_new(w, h, m); /* Fill all cells with mines */

  /* set an empty cell on a mine */
  struct coord c = { 1, 1 };
  EXPECT_UINT_EQ(mock_game_play(game, SET_EMPTY, &c), LOST);

  mock_game_destroy(game);
  return true;
}

TEST_F(game, set_empty)
{
  CFG(5, 5, 3);
  struct game* game = mock_game_new(w, h, m);

  struct coord not_mine;
  EXPECT_TRUE(find_first_not_mine(game->solution, &not_mine));
  EXPECT_UINT_EQ(mock_game_play(game, SET_EMPTY, &not_mine), OK);

  mock_game_destroy(game);
  return true;
}

TEST_F(game, flag_unflag)
{
  CFG(5, 5, 3);
  struct game* game = mock_game_new(w, h, m);
  EXPECT_UINT_EQ(game->mines, m);

#define EXPECTED_FLAGS(FM, F, T)                                               \
  EXPECT_UINT_EQ(game->flagged_mines, FM);                                     \
  EXPECT_UINT_EQ(game->flagged, F);                                            \
  EXPECT_UINT_EQ(game->turn, T);

  EXPECTED_FLAGS(0, 0, 0);

  struct coord not_mine;
  EXPECT_TRUE(find_first_not_mine(game->solution, &not_mine));
  struct coord mine;
  EXPECT_TRUE(find_first_mine(game->solution, &mine));

  EXPECT_UINT_EQ(mock_game_play(game, FLAG, &not_mine), OK);
  EXPECTED_FLAGS(0, 1, 1);

  EXPECT_UINT_EQ(mock_game_play(game, FLAG, &mine), OK);
  EXPECTED_FLAGS(1, 2, 2);

  EXPECT_UINT_EQ(mock_game_play(game, UNFLAG, &not_mine), OK);
  EXPECTED_FLAGS(1, 1, 3);

  EXPECT_UINT_EQ(mock_game_play(game, UNFLAG, &mine), OK);
  EXPECTED_FLAGS(0, 0, 4);

  mock_game_destroy(game);
  return true;
#undef EXPECTED_FLAGS
}
