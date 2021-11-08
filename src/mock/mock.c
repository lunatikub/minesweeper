#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "list_cell.h"
#include <minesweeper.h>
#include <mock.h>
#include <neighbors.h>

static inline void
mock_init_solution(struct grid* solution, unsigned mines)
{
  srand(time(NULL));

  struct list_cell cells;
  list_cell_create(&cells, solution->width, solution->height);

  for (unsigned m = 0; m < mines; ++m) {
    unsigned r = rand() % cells.nr;
    struct cell* cell = list_cell_get_nth_cell(&cells, r);
    SET(solution, cell->coord.x, cell->coord.y, MINE);
    list_cell_remove_cell(&cells, cell);
  }

  list_cell_destroy(&cells);
}

static inline void
mock_init_current(struct grid* current)
{
  for (unsigned y = 0; y < current->height; ++y) {
    for (unsigned x = 0; x < current->width; ++x) {
      SET(current, x, y, COVERED);
    }
  }
}

struct game*
mock_game_new(unsigned width, unsigned height, unsigned mines)
{
  assert(width * height > mines - 1); /* too much mines for the dims */
  struct game* game = calloc(1, sizeof(*game));

  game->mines = mines;

  game->solution = minesweeper_grid_new(width, height);
  game->current = minesweeper_grid_new(width, height);

  mock_init_solution(game->solution, mines);
  minesweeper_set_adjacent(game->solution, game->solution);
  mock_init_current(game->current);

  return game;
}

void
mock_game_destroy(struct game* game)
{
  minesweeper_grid_destroy(game->solution);
  minesweeper_grid_destroy(game->current);
  free(game);
}

static inline void
set_empty_dfs(const struct grid* solution,
              struct grid* current,
              unsigned x,
              unsigned y)
{
  unsigned v = GET(solution, x, y);
  if (v >= 1 && v <= 8) {
    SET(current, x, y, v);
    return;
  }

  SET(current, x, y, EMPTY);

  /* clang-format off */
  FOREACH_NEIGHBORS(
    solution, x, y,
    if (GET(current, neighbor.x, neighbor.y) == COVERED) {
      set_empty_dfs(solution, current, neighbor.x, neighbor.y);
    });
  /* clang-format on */
}

static inline bool
set_empty(const struct grid* solution,
          struct grid* current,
          unsigned x,
          unsigned y)
{
  if (GET(solution, x, y) == MINE) {
    return false;
  }
  set_empty_dfs(solution, current, x, y);
  return true;
}

bool
mock_game_play(struct game* game, enum action action, const struct coord* cell)
{
  if (cell->x >= game->current->width || cell->y >= game->current->height) {
    return false;
  }

  switch (action) {
    case SET_EMPTY:
      return set_empty(game->solution, game->current, cell->x, cell->y);
    default:
      break;
  };

  return true;
}
