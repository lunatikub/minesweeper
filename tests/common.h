#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>

#include <solver.h>

#include "grid.h"

#define M FLAGGED
#define C COVERED

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

#define CELLS_SZ(G) (G->width * G->height * sizeof(unsigned))

#define CELLS_EQ(C1, C2, SZ) (memcmp(C1, C2, SZ) == 0)

#define CELLS_SET(G, C) memcpy(G->cells, C, CELLS_SZ(G))

#endif /* !__COMMON_H__ */
