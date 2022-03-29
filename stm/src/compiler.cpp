#include "./compiler.hpp"

std::vector <Op> load(std::string path)
{
    static_assert(OP_COUNT == 19 /* Exhaustive handling of OPs in load() */);

    std::vector <Op> program;
    
    std::ifstream infile(path);

    if (!infile.is_open())
    {
	std::cerr << "ERROR: could not open file " << path << ": " << strerror(errno) << '\n';
	exit(3);
    }
    
    std::vector <char> buffer;
    
    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);
    
    if (length > 0) {
        buffer.resize(length);    
        infile.read(&buffer[0], length);
    }
    
    for (size_t i = 0; i < buffer.size(); ++i)
    {
	switch (buffer[i])
	{
	case 1: {
	    program.push_back({.type = OP_PUTC});
	} break;
	    
	case 2: {
	    program.push_back({.type = OP_PUTI});
	} break;

	case 3: {
	    program.push_back({.type = OP_PLUS});
	} break;

	case 4: {
	    program.push_back({.type = OP_MINUS});
	} break;

	case 5: {
	    program.push_back({.type = OP_MULT});
	} break;

	case 6: {
	    program.push_back({.type = OP_DIV});
	} break;

	case 7: {
	    int num = buffer[++i];
	    program.push_back({.type = OP_PUSH_INT, .content = num});
	} break;

	case 8: {
	    program.push_back({.type = OP_DROP});
	} break;

	case 9: {
	    program.push_back({.type = OP_DUP});
	} break;

	case 10: {
	    program.push_back({.type = OP_SWAP});
	} break;

	case 11: {
	    program.push_back({.type = OP_ROT});
	} break;

	case 12: {
	    program.push_back({.type = OP_OVER});
	} break;

	case 13: {
	    int num = buffer[++i];
	    program.push_back({.type = OP_JMP, .content = num});
	} break;

	case 14: {
	    int num = buffer[++i];
	    program.push_back({.type = OP_JMP_IF, .content = num});
	} break;
	    
	case 15: {
	    program.push_back({.type = OP_DEBUG_STACK});
	} break;

	case 16: {
	    program.push_back({.type = OP_QUIT});
	} break;

	case 17: {
	    program.push_back({.type = OP_EQU});
	} break;

	case 18: {
	    program.push_back({.type = OP_LESS});
	} break;

	case 19: {
	    program.push_back({.type = OP_NOT});
	} break;
	    
	default:
	    std::cerr << "ERROR: Unreachable\n";
	    exit(2);
	}
    }
    
    return program;
}

void save(std::string path, std::vector <Op> program)
{
    static_assert(OP_COUNT == 19 /* Exhaustive handling of OPs in save() */);
    
    std::ofstream stream;
    stream.open(path);
    
    for (size_t i = 0; i < program.size(); ++i)
    {
	switch (program[i].type)
	{
	case OP_PUTC: {
	    stream.put(1);
	} break;
	    
	case OP_PUTI: {
	    stream.put(2);
	} break;
	
	case OP_PLUS: {
	    stream.put(3);
	} break;
	
	case OP_MINUS: {
	    stream.put(4);
	} break;
	
	case OP_MULT: {
	    stream.put(5);
	} break;
	
	case OP_DIV: {
	    stream.put(6);
	} break;
	
	case OP_PUSH_INT: {
	    stream.put(7);
	    stream.put(program[i].content);
	} break;
	
	case OP_DROP: {
	    stream.put(8);
	} break;
	
	case OP_DUP: {
	    stream.put(9);
	} break;
	
	case OP_SWAP: {
	    stream.put(10);
	} break;
	
	case OP_ROT: {
	    stream.put(11);
	} break;

	case OP_OVER: {
	    stream.put(12);
	} break;

	case OP_JMP: {
	    stream.put(13);
	    stream.put(program[i].content);
	} break;

	case OP_JMP_IF: {
	    stream.put(14);
	    stream.put(program[i].content);
	} break;
	    
	case OP_DEBUG_STACK: {
	    stream.put(15);
	} break;

	case OP_QUIT: {
	    stream.put(16);
	} break;
	    
	case OP_EQU: {
	    stream.put(17);
	} break;

	case OP_LESS: {
	    stream.put(18);
	} break;

	case OP_NOT: {
	    stream.put(19);
	} break;
	    
	default:
	    std::cerr << "ERROR: Unreachable\n";
	    exit(2);
	}
    }

    stream.close();
}

void simulate_program(std::vector <Op> program)
{
    static_assert(OP_COUNT == 19 /* Exhaustive handling of OPs in simulate_program() */);
    std::vector <int> stack = {0};
    
    for (size_t ip = 0; ip < program.size(); ++ip)
    {
	switch (program[ip].type)
	{
	case OP_PLUS: {
	    if (stack.size() < 2)
	    {
		std::cerr << "ERROR: not enough items for OP_PLUS\n";
		exit(1);
	    }
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(a + b);
	} break;

	case OP_MINUS: {
	    if (stack.size() < 2)
	    {
		std::cerr << "ERROR: not enough items for OP_MINUS\n";
		exit(1);
	    }
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(b - a);
	} break;

	case OP_MULT: {
	    if (stack.size() < 2)
	    {
		std::cerr << "ERROR: not enough items for OP_MULT\n";
		exit(1);
	    }
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(b * a);
	} break;

	case OP_DIV: {
	    if (stack.size() < 2)
	    {
		std::cerr << "ERROR: not enough items for OP_DIV\n";
		exit(1);
	    }
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(b / a);
	} break;
	    
	case OP_PUSH_INT: {
	    stack.push_back(program[ip].content);
	} break;

	case OP_PUTC: {
	    if (stack.size() < 1)
	    {
		std::cerr << "ERROR: not enough items for OP_PUTC\n";
		exit(1);
	    }
	    std::cout << (char) stack.back(); stack.pop_back();
	} break;
	    
	case OP_PUTI: {
	    if (stack.size() < 1)
	    {
		std::cerr << "ERROR: not enough items for OP_PUTI\n";
		exit(1);
	    }
	    std::cout << stack.back(); stack.pop_back();
	} break;

	case OP_DROP: {
	    if (stack.size() < 1)
	    {
		std::cerr << "ERROR: not enough items for OP_DROP\n";
		exit(1);
	    }
	    stack.pop_back();
	} break;

	case OP_DUP: {
	    if (stack.size() < 1)
	    {
		std::cerr << "ERROR: not enough items for OP_DUP\n";
		exit(1);
	    }
	    stack.push_back(stack.back());
	} break;

	case OP_SWAP: {
	    if (stack.size() < 2)
	    {
		std::cerr << "ERROR: not enough items for OP_SWAP\n";
		exit(1);
	    }
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    stack.push_back(a); stack.push_back(b);
	} break;

	case OP_ROT: {
	    if (stack.size() < 3)
	    {
		std::cerr << "ERROR: Not enough items for OP_ROT\n";
		exit(1);
	    }	    
	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    int c = stack.back(); stack.pop_back();
	    stack.push_back(a); stack.push_back(b); stack.push_back(c);
	} break;

	case OP_OVER: {
	    if (stack.size() < 1)
	    {
		std::cerr << "ERROR: not enough items for OP_OVER\n";
		exit(1);
	    }
	    int a = stack[1];
	    stack.push_back(a);
	} break;

	case OP_JMP: {
	    ip = program[ip].content;
	} break;

	case OP_JMP_IF: {
	    if (stack.size() < 1)
	    {
		std::cerr << "ERROR: not enough items for OP_JMP_IF\n";
		exit(1);
	    }

	    int a = stack.back(); stack.pop_back();
	    if (a != 0)
	    {
		ip = program[ip].content;
	    }
	} break;
	    
	case OP_DEBUG_STACK: {
	    std::cout << "\n!!NOTE!! - Current state of the stack:\nSTART\n";
	    for (size_t i = 0; i < stack.size(); ++i)
	    {
		std::cout << stack[i] << " ";
	    }
	    std::cout << "\nEND\n";
	    exit(1);
	} break;

	case OP_QUIT: {
	    if (stack.size() < 1)
	    {
		std::cerr << "ERROR: Not enough items for OP_QUIT\n";
		exit(1);
	    }
	    int a = stack.back(); stack.pop_back();
	    exit(a);
	} break;
	    
	case OP_EQU: {
	    if (stack.size() < 2)
	    {
		std::cerr << "ERROR: Not enough items for OP_EQU\n";
		exit(1);
	    }
   	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    if (a == b)
	    {
		stack.push_back(1);
	    }
	    else
	    {
		stack.push_back(0);
	    }
	} break;

	case OP_LESS: {
	    if (stack.size() < 2)
	    {
		std::cerr << "ERROR: Not enough items for OP_LESS\n";
		exit(1);
	    }
   	    int a = stack.back(); stack.pop_back();
	    int b = stack.back(); stack.pop_back();
	    if (b < a)
	    {
		stack.push_back(1);
	    }
	    else
	    {
		stack.push_back(0);
	    }
	} break;

	case OP_NOT: {
	    if (stack.size() < 1)
	    {
		std::cerr << "ERROR: Not enough items for OP_NOT\n";
		exit(1);
	    }
	    int a = stack.back(); stack.pop_back();
	    if (a == 0)
	    {
		stack.push_back(1);
	    }
	    else
	    {
		stack.push_back(0);
	    }
	} break;
	    
	default:
	    std::cerr << "ERROR: Unreachable\n";
	    exit(2);
	}
    }
}
