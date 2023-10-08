#ifndef CBUILD_ALLOC_H
#define CBUILD_ALLOC_H

#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t new_size);

#endif
