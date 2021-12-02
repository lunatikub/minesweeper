#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdbool.h>
#include <stdio.h>

#include <minesweeper/grid.h>
#include <minesweeper/minesweeper.h>

#define M MINE
#define C COVERED
#define F FLAGGED

static inline void
grid_dump(const struct grid* grid)
{
  printf("--------------\n");
  for (unsigned i = 0; i < grid->height; ++i) {
    for (unsigned j = 0; j < grid->width; ++j) {
      printf("%2u ", grid->cells[i * grid->height + j]);
    }
    printf("\n");
  }
  printf("--------------\n");
}

static inline bool
find_first_not_mine(const struct grid* grid, struct coord* coord)
{
  unsigned x, y;
  for (y = 0; y < grid->height; ++y) {
    for (x = 0; x < grid->width; ++x) {
      if (GET(grid, x, y) != MINE) {
        coord->x = x;
        coord->y = y;
        return true;
      }
    }
  }
  return false;
}

static inline bool
find_first_mine(const struct grid* grid, struct coord* coord)
{
  unsigned x, y;
  for (y = 0; y < grid->height; ++y) {
    for (x = 0; x < grid->width; ++x) {
      if (GET(grid, x, y) == MINE) {
        coord->x = x;
        coord->y = y;
        return true;
      }
    }
  }
  return false;
}

#define CELLS_SZ(G) (G->width * G->height * sizeof(unsigned))

#define CELLS_EQ(C1, C2, SZ) (memcmp(C1, C2, SZ) == 0)

#define CELLS_SET(G, C) memcpy(G->cells, C, CELLS_SZ(G))

#define CFG(W, H, M)                                                           \
  const static unsigned w __attribute__((unused)) = W;                         \
  const static unsigned h __attribute__((unused)) = H;                         \
  const static unsigned m __attribute__((unused)) = M;

#define GRID(G, W, H, INIT_GRID)                                               \
  G = grid_create(W, H);                                                       \
  CELLS_SET(G, G_INIT);

#endif /* !__COMMON_H__ */
