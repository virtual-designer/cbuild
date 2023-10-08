#ifndef CBUILD_BUILD_H_
#define CBUILD_BUILD_H_

#include "log.h"
#include "macros.h"

int command(const char *restrict cmd);
int execute_v(void *start, ...);

#endif
