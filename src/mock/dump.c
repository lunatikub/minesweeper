#include <stdio.h>

#include "game.h"
#include <minesweeper.h>
#include <mock.h>

static inline void
dump_meta(struct game* game)
{
  printf(">> [%u] mines: %u, flagged: %u, covered: %u\n",
         game->turn,
         game->mines,
         game->flagged,
         game->covered);
}

static inline void
dump_x_coord(unsigned width)
{
  printf("    ");
  for (unsigned x = 0; x < width; ++x) {
    printf("%2u ", x);
  }
  printf("\n    ");
  for (unsigned x = 0; x < width; ++x) {
    printf("---");
  }
  printf("\n");
}

static inline void
dump_cell(unsigned v)
{
  if (v == COVERED) {
    printf(" C ");
  } else if (v == FLAGGED) {
    printf(" F ");
  } else if (v == 0) {
    printf("   ");
  } else {
    printf("%2u ", v);
  }
}

static inline void
dump_current(struct grid* current)
{
  for (unsigned y = 0; y < current->height; ++y) {
    printf("%2u |", y);
    for (unsigned x = 0; x < current->width; ++x) {
      dump_cell(GET(current, x, y));
    }
    printf("\n");
  }
}

void
mock_game_dump(struct game* game)
{
  dump_meta(game);
  dump_x_coord(game->current->width);
  dump_current(game->current);
  printf("\n");
}

void
mock_game_dump_solution(struct game* game)
{
  printf("-------------- solution --------------\n");
  dump_x_coord(game->current->width);
  dump_current(game->solution);
  printf("\n");
}
