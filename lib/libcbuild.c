/* The library that gets linked with build scripts. Depends on -lbuild */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <cbuild/build.h>
#include <cbuild/alloc.h>

#define CONCAT(...) str_concat(__VA_ARGS__, NULL)

char *
str_concat(const char *s1, ...)
{
    va_list args;
    size_t len = strlen(s1) + 1;
    char *buf = strdup(s1);
    va_start(args, s1);
    const char *sarg = va_arg(args, const char *);

    while (sarg != NULL)
    {
	len += strlen(sarg);
	buf = xrealloc(buf, len);
	strcat(buf, sarg);
	sarg = va_arg(args, const char *);
    }
	
    va_end(args);
    return buf;
}

char *
str_concat_dest(char **s1, const char *s2)
{
    size_t len = (*s1 == NULL ? 0 : strlen(*s1)) + strlen(s2) + 1;
    *s1 = xrealloc(*s1, len);
    strcat(*s1, s2);
    return *s1;
}

int
command(const char *restrict cmd)
{
    log_exec(cmd);
    char **argv = NULL;
    size_t argc = 0;

    for (size_t i = 0; i < strlen(cmd); i++)
    {
        char *arg = NULL;
	size_t arglen = 0;
	
	while (!isspace(cmd[i]))
	{
	    arg = xrealloc(arg, ++arglen);
	    arg[arglen - 1] = cmd[i];
	    i++;
	}
	
	arg = xrealloc(arg, ++arglen);
	arg[arglen - 1] = 0;

	argv = xrealloc(argv, sizeof (char *) * (++argc));
	argv[argc - 1] = arg;
    }

    argv = xrealloc(argv, sizeof (char *) * (++argc));
    argv[argc - 1] = NULL;

    pid_t pid = fork();

    if (pid == 0)
    {
	exit(execvp(argv[0], argv));
    }
    else
    {
	int status = 0;
	wait(&status);

	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
	{
	    log_error("Exit code of the last cmd is non-zero (%i). Aborting.", WIFEXITED(status));	    
	    exit(-1);
	}
    }
}

int
execute_v(void *start, ...)
{
    va_list args;
    char **argv = NULL;
    size_t argc = 0;

    va_start(args, start);
    
    char *arg = va_arg(args, char *);
    char *command_str = NULL;
    
    while (arg != NULL)
    {
	argv = xrealloc(argv, sizeof (char *) * (++argc));
	argv[argc - 1] = strdup(arg);
	str_concat_dest(&command_str, argv[argc - 1]);
	str_concat_dest(&command_str, " ");
	arg = va_arg(args, char *);
    }

    argv = xrealloc(argv, sizeof (char *) * (++argc));
    argv[argc - 1] = NULL;
	
    va_end(args);
    log_exec("%s", command_str);
    free(command_str);

    pid_t pid = fork();

    if (pid == 0)
    {
	exit(execvp(argv[0], argv));
    }
    else
    {
	int status = 0;
	wait(&status);

	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
	{
	    log_error("Exit code of the last command is non-zero (%i). Aborting.", WIFEXITED(status));	    
	    exit(-1);
	}
    }
}

#define TARGET_MAX 512

static target_t global_targets[TARGET_MAX] = { 0 };
static size_t target_index = 0;

static void
target_add(target_t *target)
{
    global_targets[target_index++] = *target;
}

target_t
target(const char *name, enum target_type type)
{
    target_t target = {
	.type = type,
	.name = strdup(name),
	.sources = char_array_init(),
	.cflags = char_array_init(),
    };

    target_add(&target);
    return target;
}

void
sources(const target_t *target, const char *file)
{
    char_array_push(target->sources, file);
}
 
void
compile()
{
    (TARGETS_FN)();
    
    for (size_t i = 0; i < target_index; i++)
    {
	log_info("Target: %s", global_targets[i].name);

	for (size_t j = 0; j < global_targets[i].sources->size; j++)
	    log_info("Compile: %s", global_targets[i].sources->elements[j]);
    }
}
