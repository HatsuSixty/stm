#include <stdio.h>

#include "./compiler.h"

int main(void)
{
    compile_program("sum.stasm");
    return 0;
}
