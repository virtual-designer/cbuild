#ifndef CBUILD_MACROS_H
#define CBUILD_MACROS_H

#include "build.h"

#define BUILD_FN cbuild_build
#define TARGETS_FN cbuild_targets
#define execute(...) execute_v(NULL, __VA_ARGS__, NULL)

#define build void cbuild_build()
#define targets void cbuild_targets()

__BEGIN_DECLS

extern build;
extern targets;

__END_DECLS

#endif
