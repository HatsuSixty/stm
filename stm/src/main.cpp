#include <iostream>
#include <vector>

#include "./operators.hpp"
#include "./compiler.hpp"

////////// EXAMPLES //////////

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
    {.type = OP_JMP, .content = 0},
};

std::vector <Op> hello = {
    {.type = OP_PUSH_INT},
    {.type = OP_PUSH_INT, .content = 104}, //h
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 101}, //e
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 108}, //l
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 108}, //l
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 111}, //o
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content =  44}, //,
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content =  32}, //
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 119}, //w
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 111}, //o
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 114}, //r
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 108}, //l
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 100}, //d
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content =  33}, //!
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content =  10}, //new line
    {.type = OP_PUTC},
    {.type = OP_JMP, .content = 0},
};

std::vector <Op> ifs = {
    {.type = OP_PUSH_INT, .content = 1},
    {.type = OP_PUSH_INT, .content = 2},
    {.type = OP_EQU},
    {.type = OP_JMP_IF, .content = 9},
    {.type = OP_PUSH_INT, .content = 100},
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 0},
    {.type = OP_QUIT},
};

std::vector <Op> counter = {
    {.type = OP_PUSH_INT, .content = 0},
    {.type = OP_DUP},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_LESS},
    {.type = OP_NOT},
    {.type = OP_JMP_IF, .content = 11},
    {.type = OP_PUSH_INT, .content = 1},
    {.type = OP_PLUS},
    {.type = OP_DUP},
    {.type = OP_PUTI},
    {.type = OP_JMP, .content = 0},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
};

std::vector <Op> lessngreater = {
    {.type = OP_PUSH_INT, .content = 20},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_GREATER},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUSH_INT, .content = 20},
    {.type = OP_LESS},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
};

std::vector <Op> andnor = {
    {.type = OP_PUSH_INT, .content = 1},
    {.type = OP_PUSH_INT, .content = 0},
    {.type = OP_OR},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
};

////////// END EXAMPLES //////////

int main(void)
{
    save("./test.stasm", andnor);
    std::vector <Op> generated_program = load("./test.stasm");
    simulate_program(generated_program);
    return 0;
}
