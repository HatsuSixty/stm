#include "compiler.hpp"

std::vector <Op> load(std::string path)
{
    static_assert(OP_COUNT == 11 /* Exhaustive handling of OPs in save() */);

    std::ifstream infile(path);
    std::vector<char> buffer;
    
    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);
    
    if (length > 0) {
        buffer.resize(length);    
        infile.read(&buffer[0], length);
    }
    
    for (size_t i = 0; i < buffer.size(); ++i)
    {
	std::cout << buffer[i];
    }
    
    std::vector <Op> temp;

    return temp;
}

void save(std::string path, std::vector <Op> program)
{
    static_assert(OP_COUNT == 11 /* Exhaustive handling of OPs in save() */);
    
    std::ofstream stream;
    stream.open(path);
    
    for (size_t i = 0; i < program.size(); ++i)
    {
	switch (program[i].type)
	{
	case OP_PRINT: {
	    stream << 1;
	} break;
	
	case OP_PLUS: {
	    stream << 2;
	    stream << program[i].content;
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

void simulate_program(std::vector <Op> program)
{
    static_assert(OP_COUNT == 11 /* Exhaustive handling of OPs in simulate_program() */);
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
