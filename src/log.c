#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "log.h"

const char *
log_level_to_str(enum log_level level)
{
    const char *translate[] = {
	[LOG_DEBUG] = "\033[2mDEBUG\033[0m",
	[LOG_INFO] = "\033[1;36mINFO\033[0m",
	[LOG_WARN] = "\033[1;33mWARNING\033[0m",
	[LOG_ERROR] = "\033[1;31mERROR\033[0m",
	[LOG_SUCCESS] = "\033[1;32mSUCCESS\033[0m",
	[LOG_GENERIC] = "\033[1mGENERIC\033[0m"
    };

    return translate[level];
}

void
log_message(enum log_level level, const char *fmt, ...)
{
    va_list args;
    FILE *stream = level == LOG_WARN || level == LOG_ERROR ? stderr : stdout;
    
    va_start(args, fmt);
    
    if (level != LOG_GENERIC)
	fprintf(stream, "[%s] ", log_level_to_str(level));

    vfprintf(stream, fmt, args);
    fprintf(stream, "\n");
    va_end(args);
}
