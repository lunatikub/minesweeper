/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(list_cell, simple)
{
  struct list_cell cells;
  struct cell* cell;

  list_cell_init(&cells);
  {
    EXPECT_UINT_EQ(cells.nr, 0);

    list_cell_add_head(&cells, 42, 42);

    cell = list_cell_get_nth_cell(&cells, 0);
    EXPECT_UINT_EQ(cells.nr, 1);
    EXPECT_UINT_EQ(cell->coord.x, 42);
    EXPECT_UINT_EQ(cell->coord.y, 42);

    list_cell_add_head(&cells, 41, 41);
    EXPECT_UINT_EQ(cells.nr, 2);
    cell = list_cell_get_nth_cell(&cells, 1);
    EXPECT_UINT_EQ(cell->coord.x, 42);
    EXPECT_UINT_EQ(cell->coord.y, 42);
    cell = list_cell_get_nth_cell(&cells, 0);
    EXPECT_UINT_EQ(cell->coord.x, 41);
    EXPECT_UINT_EQ(cell->coord.y, 41);

    list_cell_remove_cell(&cells, cell);
    cell = list_cell_get_nth_cell(&cells, 0);
    EXPECT_UINT_EQ(cells.nr, 1);
    EXPECT_UINT_EQ(cell->coord.x, 42);
    EXPECT_UINT_EQ(cell->coord.y, 42);
  }
  list_cell_destroy(&cells);
  return true;
}

TEST_F(list_cell, unbound)
{
  struct list_cell cells;

  list_cell_init(&cells);
  {
    EXPECT_TRUE(list_cell_get_nth_cell(&cells, 1) == NULL);
  }
  list_cell_destroy(&cells);
  return true;
}
