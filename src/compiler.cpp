#include "compiler.hpp"

void simulate_program(Op *program, size_t program_sz)
{
    static_assert(OP_COUNT == 3 /* Exhaustive handling of OPs in simulate_program */);
    std::vector <int> stack = {0};
    
    for (size_t ip = 0; ip < program_sz; ++ip)
    {
	switch (program[ip].type)
	{
	case OP_PLUS: {
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(a + b);
	} break;

	case OP_PUSH_INT: {
	    stack.push_back(program[ip].content);
	} break;

	case OP_PRINT: {
	    std::cout << stack.back(); stack.pop_back();
	} break;
	    
	default:
	    std::cerr << "ERROR: Unreachable\n";
	    exit(2);
	}
    }
}
