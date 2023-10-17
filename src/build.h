#ifndef CBUILD_BUILD_H
#define CBUILD_BUILD_H

#include <stdbool.h>

char *build_file_path(char *dirpath, bool *failed);
void compile_build_file(const char *filepath);
void exec_build_file(char *dirpath);
void remove_build_exec_file();
void start_build();
void prepare_build();
void end_build();

#endif
