#ifndef CBUILD_MACROS_H
#define CBUILD_MACROS_H

#include "build.h"

#define BUILD_FN cbuild_build
#define execute(...) execute_v(NULL, __VA_ARGS__, NULL)

#define build void cbuild_build()

extern build;

#endif
