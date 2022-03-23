#include "compiler.hpp"

void simulate_program(std::vector <Op> program)
{
    static_assert(OP_COUNT == 11 /* Exhaustive handling of OPs in simulate_program */);
    std::vector <int> stack = {0};
    
    for (size_t ip = 0; ip < program.size(); ++ip)
    {
	switch (program[ip].type)
	{
	case OP_PLUS: {
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(a + b);
	} break;

	case OP_MINUS: {
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(b - a);
	} break;

	case OP_MULT: {
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(b * a);
	} break;

	case OP_DIV: {
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(b / a);
	} break;
	    
	case OP_PUSH_INT: {
	    stack.push_back(program[ip].content);
	} break;

	case OP_PRINT: {
	    std::cout << stack.back(); stack.pop_back();
	} break;

	case OP_DROP: {
	    stack.pop_back();
	} break;

	case OP_DUP: {
	    stack.push_back(stack.back());
	} break;

	case OP_SWAP: {
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(a); stack.push_back(b);
	} break;

	case OP_ROT: {
	    if (!(stack.size() >= 3))
	    {
		std::cerr << "ERROR: Not enough items for OP_ROT\n";
	    }
	    
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    int c = stack.back(); stack.pop_back();
	    stack.push_back(a); stack.push_back(b); stack.push_back(c);
	} break;

	case OP_DEBUG_STACK: {
	    std::cout << "!!NOTE!! - Current state of the stack:\nSTART\n";
	    for (size_t i = 0; i < stack.size(); ++i)
	    {
		std::cout << stack[i] << " ";
	    }
	    std::cout << "\nEND\n";
	    exit(1);
	} break;
	    
	default:
	    std::cerr << "ERROR: Unreachable\n";
	    exit(2);
	}
    }
}
