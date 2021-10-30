#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <minesweeper.h>

struct configuration
{
  int a;
};

struct configuration*
solver_configuration_get(const struct grid* grid);

#endif /* !__CONFIGURATION_H__ */
