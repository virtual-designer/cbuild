#ifndef CBUILD_LOG_H
#define CBUILD_LOG_H

#include <stdlib.h>

enum log_level
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_SUCCESS,
    LOG_GENERIC
};

#ifdef NDEBUG
#define log_debug(...) (void) NULL
#else
#define log_debug(...) log_message(LOG_DEBUG, __VA_ARGS__)
#endif

#define log_info(...) log_message(LOG_INFO, __VA_ARGS__)
#define log_error(...) log_message(LOG_ERROR, __VA_ARGS__)
#define log_warn(...) log_message(LOG_WARN, __VA_ARGS__)
#define log_success(...) log_message(LOG_SUCCESS, __VA_ARGS__)
#define log(...) log_message(LOG_GENERIC, __VA_ARGS__)

const char *log_level_to_str(enum log_level level);
void __attribute__((format(printf, 2, 3))) log_message(enum log_level level, const char *fmt, ...);

#endif
