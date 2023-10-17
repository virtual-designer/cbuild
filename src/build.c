#define _GNU_SOURCE
#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <sys/wait.h>
#include <cbuild/log.h>
#include <cbuild/alloc.h>

#include "build.h"

#define BUILD_FILE_NAME "build.c"
#define BUILD_EXEC_FILE_NAME ".build_exec"
#define LIBCBUILD_PATH "/usr/lib/libcbuild.a"
#define LIBCBUILD_PATH_ENVVAR "LIBCBUILD_PATH"
#define INCLUDE_PATH_ENVVAR "CBUILD_INCLUDE_PATH"
#define INCLUDE_PATH "/usr/include"

static const char *
get_libcbuild_path()
{
    const char *env = getenv(LIBCBUILD_PATH_ENVVAR);

    if (env != NULL)
	    return env;

    return LIBCBUILD_PATH;
}

static const char *
get_include_path()
{
    const char *env = getenv(INCLUDE_PATH_ENVVAR);

    if (env != NULL)
	    return env;

    return INCLUDE_PATH;
}

char *
build_file_path(char *dirpath, bool *failed)
{
    char curr_dir_buf[PATH_MAX];

    if (dirpath == NULL)
	    getcwd(curr_dir_buf, sizeof (curr_dir_buf));
    else
	    strcpy(curr_dir_buf, dirpath);
	
    char *fullpath = xmalloc(strlen(curr_dir_buf) + strlen(BUILD_FILE_NAME) + 2);

    strcpy(fullpath, curr_dir_buf);
    strcat(fullpath, "/" BUILD_FILE_NAME);

    log_debug("Looking for: %s", fullpath);
    
    FILE *file = fopen(fullpath, "r");
    
    if (file == NULL)
	    *failed = true;
    else
    {
        *failed = false;
        fclose(file);
    }

    return fullpath;
}

void
compile_build_file(const char *filepath)
{
    log_info("Compiling build file");
    
    pid_t pid = fork();

    if (pid == 0) 
    {
        exit(execlp("/usr/bin/gcc", "gcc", "-g",
                "-I", get_include_path(),
                filepath, get_libcbuild_path(),
                "-o", BUILD_EXEC_FILE_NAME, NULL));
    }
    else 
    {
        int status = 0;
        
        waitpid(pid, &status, 0);
        
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) 
        {
            log_error("Failed to compile build file");
            exit(-1);
        }
    }
}

void
exec_build_file(char *dirpath)
{
    char curr_dir_buf[PATH_MAX];

    if (dirpath == NULL)
	    getcwd(curr_dir_buf, sizeof (curr_dir_buf));
    else
	    strcpy(curr_dir_buf, dirpath);
	
    char *fullpath = xmalloc(strlen(curr_dir_buf) + strlen(BUILD_EXEC_FILE_NAME) + 2);

    strcpy(fullpath, curr_dir_buf);
    strcat(fullpath, "/" BUILD_EXEC_FILE_NAME);

    log_debug("Attempting to execute: %s", fullpath);
    
    pid_t pid = fork();

    if (pid == 0) 
    {
	    exit(execl(fullpath, basename(strdup(fullpath)), NULL));
    }
    else 
    {
        int status = 0;
        
        waitpid(pid, &status, 0);
        
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) 
        {
            log_error("Failed to execute build file");
            exit(-1);
        }
    }
}

void
remove_build_exec_file()
{
    if (remove(BUILD_EXEC_FILE_NAME) != 0)
    {
	    log_warn("Failed to remove compiled build file executable: %s", strerror(errno));
    }
}

void
start_build()
{
    log_info("Starting build...");
    bool failed = false;
    const char *fullpath = build_file_path(NULL, &failed);
    
    if (failed)
    {
        if (errno == ENOENT)
            log_error("No build.c file found in the current directory!");
        else
            log_error("Failed to open build.c file: %s", strerror(errno));
        
        exit(2);
    }

    log_info("Found build.c file: %s", fullpath);
    compile_build_file(fullpath);
    exec_build_file(NULL);
    remove_build_exec_file();
}

void 
prepare_build()
{
    
}

void 
end_build()
{
    log("\033[1;32mBUILD SUCCESSFUL\033[0m");
}