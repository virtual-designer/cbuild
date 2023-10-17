#include <cbuild/array.h>
#include <cbuild/alloc.h>
#include <string.h>

char_array_t *
char_array_init()
{
    char_array_t *array = xcalloc(1, sizeof (char_array_t));
    array->elements = NULL;
    array->size = 0;
    return array;
}

void
char_array_free(char_array_t *array)
{
    for (size_t i = 0; i < array->size; i++)
    {
	    free(array->elements[i]);
    }

    free(array->elements);
}

void
char_array_push(char_array_t *array, const char *string)
{
    array->elements = xrealloc(array->elements, sizeof (char *) * (++array->size));
    array->elements[array->size - 1] = strdup(string);
}
