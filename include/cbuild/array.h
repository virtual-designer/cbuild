#ifndef CBUILD_ARRAY_H
#define CBUILD_ARRAY_H

#include <stdlib.h>

typedef struct {
    char **elements;
    size_t size;
} char_array_t;

__BEGIN_DECLS

char_array_t *char_array_init();
void char_array_push(char_array_t *, const char *);
void char_array_free(char_array_t *);
char *char_array_to_str(const char_array_t *);

__END_DECLS

#endif
