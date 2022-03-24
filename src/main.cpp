#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>

#include "./operators.hpp"
#include "./compiler.hpp"

void save(std::string path, std::vector <Op> program)
{
    static_assert(OP_COUNT == 11 /* Exhaustive handling of OPs in save() */);
    
    std::fstream stream;
    stream.open(path, std::ios::out);
    
    for (size_t i = 0; i < program.size(); ++i)
    {
	switch (program[i].type)
	{
	case OP_PRINT: {
	    stream << 1;
	} break;
	
	case OP_PLUS: {
	    stream << 2;
	} break;
	
	case OP_MINUS: {
	    stream << 3;
	} break;
	
	case OP_MULT: {
	    stream << 4;
	} break;
	
	case OP_DIV: {
	    stream << 5;
	} break;
	
	case OP_PUSH_INT: {
	    stream << 6;
	} break;
	
	case OP_DROP: {
	    stream << 7;
	} break;
	
	case OP_DUP: {
	    stream << 8;
	} break;
	
	case OP_SWAP: {
	    stream << 9;
	} break;
	
	case OP_ROT: {
	    stream << 10;
	} break;
	
	case OP_DEBUG_STACK: {
	    stream << 11;
	} break;
	
	default:
	    std::cerr << "Unreachable\n";
	    exit(2);
	}
    }

    stream.close();
}

std::vector <Op> program = {
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
    {.type = OP_DEBUG_STACK},
    {.type = OP_PRINT},
};

int main()
{
    save("test.stasm", program);
    simulate_program(program);
    return 0;
}
