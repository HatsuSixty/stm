#include <iostream>

#include "operators.hpp"
#include "compiler.hpp"

Op program[] = {
    {.type = OP_PUSH_INT, .content = 34},
    {.type = OP_PUSH_INT, .content = 35},
    {.type = OP_PLUS},
    {.type = OP_PUSH_INT, .content = 35},
    {.type = OP_MINUS},
    {.type = OP_PUSH_INT, .content = 35},
    {.type = OP_PLUS},
    {.type = OP_PRINT},
};
#define PROGRAM_SIZE (sizeof(program) / sizeof(program[0]))

int main()
{
    simulate_program(program, PROGRAM_SIZE);
    return 0;
}
