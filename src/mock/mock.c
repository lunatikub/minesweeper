#include <stdlib.h>
#include <time.h>

#include <minesweeper/grid.h>
#include <minesweeper/list_cell.h>
#include <minesweeper/neighbors.h>
#include <mock/mock.h>

#include "game.h"

static inline void
mock_init_solution(struct grid* solution, unsigned mines)
{
  srand(time(NULL));

  list_cell_t* cells = list_cell_create();
  for (unsigned y = 0; y < solution->height; ++y) {
    for (unsigned x = 0; x < solution->width; ++x) {
      list_cell_add_head(cells, (struct coord){ x, y });
    }
  }

  for (unsigned m = 0; m < mines; ++m) {
    unsigned r = rand() % list_cell_get_nr(cells);
    cell_t* cell = list_cell_get_nth(cells, r);
    struct coord* coord = list_cell_get_coord(cell);
    SET(solution, coord->x, coord->y, MINE);
    list_cell_remove(cells, cell);
  }

  list_cell_destroy(cells);
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
  /* too much mines for the dims */
  if (mines != 0 && mines > width * height) {
    return NULL;
  }
  struct game* game = calloc(1, sizeof(*game));

  game->mines = mines;

  game->solution = minesweeper_grid_new(width, height);
  game->current = minesweeper_grid_new(width, height);

  mock_init_solution(game->solution, mines);
  minesweeper_set_adjacent(game->solution, game->solution);
  mock_init_current(game->current);
  game->covered = width * height;

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
set_empty_dfs(struct game* game, unsigned x, unsigned y)
{
  --game->covered;

  unsigned v = GET(game->solution, x, y);
  if (v >= 1 && v <= 8) {
    SET(game->current, x, y, v);
    return;
  }
  SET(game->current, x, y, EMPTY);

  /* clang-format off */
  FOREACH_NEIGHBORS(
    game->solution, x, y,
    if (GET(game->current, neighbor.x, neighbor.y) == COVERED &&
        GET(game->solution, neighbor.x, neighbor.y) != MINE) {
      set_empty_dfs(game, neighbor.x, neighbor.y);
    });
  /* clang-format on */
}

static inline bool
set_empty(struct game* game, unsigned x, unsigned y)
{
  if (GET(game->solution, x, y) == MINE) {
    return false;
  }
  set_empty_dfs(game, x, y);
  return true;
}

static inline void
set_flag(struct game* game, unsigned x, unsigned y)
{
  SET(game->current, x, y, FLAGGED);
  if (GET(game->solution, x, y) == MINE) {
    ++game->flagged_mines;
  }
  ++game->flagged;
}

static inline void
set_unflag(struct game* game, unsigned x, unsigned y)
{
  SET(game->current, x, y, COVERED);
  if (GET(game->solution, x, y) == MINE) {
    --game->flagged_mines;
  }
  --game->flagged;
}

enum ret
mock_game_play(struct game* game, enum action action, const struct coord* cell)
{
  ++game->turn;

  switch (action) {
    case SET_EMPTY:
      if (set_empty(game, cell->x, cell->y) == false) {
        return LOST;
      }
      break;
    case FLAG:
      set_flag(game, cell->x, cell->y);
      break;
    case UNFLAG:
      set_unflag(game, cell->x, cell->y);
      break;
    default:
      return LOST;
  };

  if (game->mines == game->flagged_mines || game->mines == game->covered) {
    return WON;
  }

  return OK;
}
