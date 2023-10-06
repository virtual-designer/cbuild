#define _POSIX_C_SOURCE 1
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "alloc.h"

static char *progname = NULL;

static void
init_globals(char **argv)
{
    progname = argv[0];
}

static void
print_usage(FILE *stream)
{
    fputs("Usage:\n", stream);
    fprintf(stream, "  %s [options...]\n", progname);
}

static void
usage()
{
    print_usage(stdout);
}

static _Noreturn void
invalid_usage()
{
    print_usage(stderr);
    exit(1);
}

int
main(int argc, char **argv)
{
    init_globals(argv);

    if (argc != 1)
	invalid_usage();

    start_build();
    log("\033[1;32mBUILD SUCCESSFUL\033[0m");
    return 0;
}
