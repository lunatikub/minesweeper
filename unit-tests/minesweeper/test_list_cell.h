/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(list_cell, simple)
{
  list_cell_t* cells = list_cell_create();
  cell_t* cell;
  struct coord* coord;

  EXPECT_UINT_EQ(list_cell_get_nr(cells), 0);

  list_cell_add_head(cells, (struct coord){ 42, 42 });

  cell = list_cell_get_nth(cells, 0);
  coord = list_cell_get_coord(cell);

  EXPECT_UINT_EQ(list_cell_get_nr(cells), 1);

  EXPECT_UINT_EQ(coord->x, 42);
  EXPECT_UINT_EQ(coord->y, 42);

  list_cell_add_head(cells, (struct coord){ 41, 41 });
  EXPECT_UINT_EQ(list_cell_get_nr(cells), 2);

  cell = list_cell_get_nth(cells, 1);
  coord = list_cell_get_coord(cell);
  EXPECT_UINT_EQ(coord->x, 42);
  EXPECT_UINT_EQ(coord->y, 42);

  cell = list_cell_get_nth(cells, 0);
  coord = list_cell_get_coord(cell);
  EXPECT_UINT_EQ(coord->x, 41);
  EXPECT_UINT_EQ(coord->y, 41);

  list_cell_remove(cells, cell);
  EXPECT_UINT_EQ(list_cell_get_nr(cells), 1);

  coord = list_cell_get_coord(list_cell_get_nth(cells, 0));
  EXPECT_UINT_EQ(coord->x, 42);
  EXPECT_UINT_EQ(coord->y, 42);

  list_cell_destroy(cells);
  return true;
}

TEST_F(list_cell, unbound)
{
  list_cell_t* cells = list_cell_create();
  EXPECT_TRUE(list_cell_get_nth(cells, 1) == NULL);
  list_cell_destroy(cells);
  return true;
}

TEST_F(list_cell, exist)
{
  list_cell_t* cells = list_cell_create();

  list_cell_add_head(cells, (struct coord){ 42, 42 });
  list_cell_add_head(cells, (struct coord){ 41, 41 });

  EXPECT_TRUE(list_cell_exist(cells, (struct coord){ 42, 42 }));
  EXPECT_TRUE(list_cell_exist(cells, (struct coord){ 41, 41 }));
  EXPECT_FALSE(list_cell_exist(cells, (struct coord){ 42, 41 }));
  EXPECT_FALSE(list_cell_exist(cells, (struct coord){ 41, 42 }));

  list_cell_destroy(cells);
  return true;
}
