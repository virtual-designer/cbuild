#ifndef CBUILD_ALLOC_H
#define CBUILD_ALLOC_H

#include <stdio.h>
#include <stdlib.h>

__BEGIN_DECLS

void *xmalloc(size_t size);
void *xcalloc(size_t size, size_t n);
void *xrealloc(void *ptr, size_t new_size);

__END_DECLS

#endif
