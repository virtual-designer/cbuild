#include "alloc.h"

void *
xmalloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
    {
	perror("xmalloc");
	exit(-1);
    }

    return ptr;
}
