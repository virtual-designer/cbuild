#ifndef CBUILD_BUILD_H_
#define CBUILD_BUILD_H_

#include "array.h"
#include "log.h"
#include "macros.h"
#include <stdlib.h>

enum target_type
{
    TARGET_EXECUTABLE
};

typedef struct target
{
    enum target_type type;
    char *name;
    char_array_t *sources;
    char_array_t *cflags;
} target_t;

int command(const char *restrict cmd);
int execute_v(void *start, ...);
void compile();
target_t target(const char *, enum target_type);
void sources(const target_t *, const char *);

#endif
