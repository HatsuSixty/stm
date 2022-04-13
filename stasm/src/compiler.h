#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

#include "./sv.h"
#include "./operators.h"

void compile_program(const char* fpath);
void translate_line(String_View line);

#endif // COMPILER_H_
