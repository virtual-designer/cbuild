#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <cbuild/log.h>

static const char *log_level_str_map[] = {
    [LOG_DEBUG] = "debug",
    [LOG_INFO] = "info",
    [LOG_WARN] = "warning",
    [LOG_ERROR] = "error",
    [LOG_SUCCESS] = "success",
    [LOG_GENERIC] = "generic",
    [LOG_EXEC] = "execute"
};

static const char *
log_level_color_str(enum log_level level)
{
    const char *translate[] = {
        [LOG_DEBUG] = "\033[2m",
        [LOG_INFO] = "\033[1;36m",
        [LOG_WARN] = "\033[1;33m",
        [LOG_ERROR] = "\033[1;31m",
        [LOG_SUCCESS] = "\033[1;32m",
        [LOG_GENERIC] = "\033[1m",
        [LOG_EXEC] = "\033[1;35m"
    };

    return translate[level];
}

const char *
log_level_to_str(enum log_level level)
{
    return log_level_str_map[level];
}

static size_t
log_level_padding(enum log_level level)
{
    size_t maxlen = 0;

    for (size_t i = 0; i < sizeof (log_level_str_map) / sizeof (log_level_str_map[0]); i++)
    {
        size_t len = strlen(log_level_str_map[i]);

        if (maxlen < len)
            maxlen = len;
    }
    
    return maxlen - strlen(log_level_str_map[level]);
}

void
log_message(enum log_level level, const char *fmt, ...)
{
    va_list args;
    FILE *stream = level == LOG_WARN || level == LOG_ERROR ? stderr : stdout;
    
    va_start(args, fmt);
    
    if (level != LOG_GENERIC)
    {
        ssize_t padding = (ssize_t) log_level_padding(level);
        fprintf(stream, "%s%s\033[0m", log_level_color_str(level), log_level_to_str(level));

        do
        {
            fputc(' ', stream);
        }
        while (padding --> 0);
    }
    
    vfprintf(stream, fmt, args);
    fprintf(stream, "\n");
    va_end(args);
}
