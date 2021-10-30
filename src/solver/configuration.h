#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "grid.h"

struct configuration
{
  int a;
};

struct configuration*
configuration_get(const struct grid* grid);

#endif /* !__CONFIGURATION_H__ */
