#include <cbuild/alloc.h>
#include <stdlib.h>

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

void *
xcalloc(size_t size, size_t n)
{
    void *ptr = calloc(size, n);

    if (ptr == NULL)
    {
        perror("xcalloc");
        exit(-1);
    }

    return ptr;
}

void *
xrealloc(void *ptr, size_t new_size)
{
    void *ret_ptr = realloc(ptr, new_size);

    if (ret_ptr == NULL)
    {
        perror("xrealloc");
        exit(-1);
    }

    return ret_ptr;
}
