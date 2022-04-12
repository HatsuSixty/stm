#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

#include "./sv.h"

void compile_program(const char* fpath);

#endif // COMPILER_H_
