#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <assert.h>

#include "./sv.h"

void compile_program(const char* fpath, const char* outpath);
void translate_line(String_View line);
void update_labels(String_View source);
int is_label(String_View token);

#endif // COMPILER_H_
