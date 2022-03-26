#include <iostream>
#include <vector>

#include "./operators.hpp"
#include "./compiler.hpp"

std::vector <Op> program = {
    {.type = OP_PUSH_INT, .content = 69},
    {.type = OP_PUSH_INT, .content = 34},
    {.type = OP_PUSH_INT, .content = 35},
    {.type = OP_PLUS},
    {.type = OP_PUSH_INT, .content = 35},
    {.type = OP_MINUS},
    {.type = OP_PUSH_INT, .content = 35},
    {.type = OP_PLUS},
    {.type = OP_PUSH_INT, .content = 2},
    {.type = OP_MULT},
    {.type = OP_PUSH_INT, .content = 2},
    {.type = OP_DIV},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_SWAP},
    {.type = OP_DUP},
    {.type = OP_DROP},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_ROT},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
    {.type = OP_OVER},
//    {.type = OP_DEBUG_STACK},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
};

int main(void)
{
    save("./test.stasm", program);
    std::vector <Op> generated_program = load("./test.stasm");
    simulate_program(generated_program);
    return 0;
}