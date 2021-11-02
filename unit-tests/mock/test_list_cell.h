/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(list_cell, simple)
{
  const static unsigned w = 3;
  const static unsigned h = 3;
  struct list_cell cells;
  struct cell *cell;

  list_cell_create(&cells, w, h);
  {
    EXPECT_UINT_EQ(cells.nr, w * h);

    // latest inserted
    cell = list_cell_get_nth_cell(&cells, 0);
    EXPECT_UINT_EQ(cell->coord.x, 2);
    EXPECT_UINT_EQ(cell->coord.y, 2);

    // first inserted
    cell = list_cell_get_nth_cell(&cells, w * h - 1);
    EXPECT_UINT_EQ(cell->coord.x, 0);
    EXPECT_UINT_EQ(cell->coord.y, 0);

    list_cell_remove_cell(&cells, cell);
    EXPECT_UINT_EQ(cells.nr, w * h - 1);
  }
  list_cell_destroy(&cells);
  return true;
}

TEST_F(list_cell, unbound)
{
  const static unsigned w = 3;
  const static unsigned h = 3;
  struct list_cell cells;

  list_cell_create(&cells, w, h);
  {
    EXPECT_TRUE(list_cell_get_nth_cell(&cells, w * h + 1) == NULL);
  }
  list_cell_destroy(&cells);
  return true;
}
