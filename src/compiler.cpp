#include "compiler.hpp"

void stack_push(int value)
{
    if (!(stack_size < STACK_CAP))
    {
        std::cerr << "ERROR: could not add items to the stack: stack overflow\n";
	exit(1);
    }
    stack[stack_size++] = value; 
}

int stack_pop()
{
    if (!(stack_size > 0))
    {
	std::cerr << "ERROR: could not remove items from the stack: stack underflow\n";
	exit(1);
    }
    return stack[--stack_size];
}

void simulate_program(Op *program, size_t stack_sz)
{
    std::cerr << "ERROR: TODO: simulate_program is not implemented yet.\n";
}
