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

char *
char_array_to_str(const char_array_t *array)
{
	char *str = xmalloc(1);
	strcpy(str, "");
	size_t index = 0;
	size_t prevsize = 1;

	for (size_t i = 0; i < array->size; i++)
	{
		prevsize += strlen(array->elements[i] + ((i != array->size - 1) ? 1 : 0));
		str = xrealloc(str, prevsize);
		strcat(str, array->elements[i]);
		strcat(str, " "); 
	}

	str[prevsize - 1] = 0;
	return str;
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
