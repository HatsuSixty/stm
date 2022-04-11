#include "./compiler.hpp"

std::vector <Op> load(std::string path)
{
    static_assert(OP_COUNT == 41 /* Exhaustive handling of OPs in load() */);

    std::vector <Op> program;

    std::ifstream infile(path);

    if (!infile.is_open())
    {
        std::cerr << "ERROR: Could not open file " << path << ": " << strerror(errno) << '\n';
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
            program.push_back({.type = OP_GREATER});
        } break;

        case 20: {
            program.push_back({.type = OP_NOT});
        } break;

        case 21: {
            program.push_back({.type = OP_OR});
        } break;

        case 22: {
            program.push_back({.type = OP_AND});
        } break;

        case 23: {
            program.push_back({.type = OP_READK});
        } break;

        case 24: {
            program.push_back({.type = OP_AT});
        } break;

        case 25: {
            program.push_back({.type = OP_NQDEBUG_STACK});
        } break;

        case 26: {
            program.push_back({.type = OP_PRINT});
        } break;

        case 27: {
            int num = buffer[++i];
            program.push_back({.type = OP_TMP_PUSH_INT, .content = num});
        } break;

        case 28: {
            program.push_back({.type = OP_TMP_DROP});
        } break;

        case 29: {
            program.push_back({.type = OP_NQDEBUG_TMP_BUFF});
        } break;

        case 30: {
            program.push_back({.type = OP_TMP_AT});
        } break;

        case 31: {
            int num = buffer[++i];
            program.push_back({.type = OP_ARR_PUSH_INT, .content = num});
        } break;

        case 32: {
            program.push_back({.type = OP_ARR_DROP});
        } break;

        case 33: {
            program.push_back({.type = OP_ARR_AT});
        } break;

        case 34: {
            program.push_back({.type = OP_NQDEBUG_TMP_ARR});
        } break;

        case 35: {
            program.push_back({.type = OP_OPEN});
        } break;

        case 36: {
            program.push_back({.type = OP_CLOSE});
        } break;

        case 37: {
            program.push_back({.type = OP_WRITE});
        } break;

        case 38: {
            program.push_back({.type = OP_READ});
        } break;

        case 39: {
            program.push_back({.type = OP_PUT});
        } break;

        case 40: {
            program.push_back({.type = OP_RAND});
        } break;

        case 41: {
            program.push_back({.type = OP_MOD});
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
    static_assert(OP_COUNT == 41 /* Exhaustive handling of OPs in save() */);

    std::ofstream stream;
    stream.open(path);

    if (!stream.is_open())
    {
        std::cerr << "ERROR: Could not open file " << path << ": " << strerror(errno) << '\n';
        exit(3);
    }

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

        case OP_GREATER: {
            stream.put(19);
        } break;

        case OP_NOT: {
            stream.put(20);
        } break;

        case OP_OR: {
            stream.put(21);
        } break;

        case OP_AND: {
            stream.put(22);
        } break;

        case OP_READK: {
            stream.put(23);
        } break;

        case OP_AT: {
            stream.put(24);
        } break;

        case OP_NQDEBUG_STACK: {
            stream.put(25);
        } break;

        case OP_PRINT: {
            stream.put(26);
        } break;

        case OP_TMP_PUSH_INT: {
            stream.put(27);
            stream.put(program[i].content);
        } break;

        case OP_TMP_DROP: {
            stream.put(28);
        } break;

        case OP_NQDEBUG_TMP_BUFF: {
            stream.put(29);
        } break;

        case OP_TMP_AT: {
            stream.put(30);
        } break;

        case OP_ARR_PUSH_INT: {
            stream.put(31);
            stream.put(program[i].content);
        } break;

        case OP_ARR_DROP: {
            stream.put(32);
        } break;

        case OP_ARR_AT: {
            stream.put(33);
        } break;

        case OP_NQDEBUG_TMP_ARR: {
            stream.put(34);
        } break;

        case OP_OPEN: {
            stream.put(35);
        } break;

        case OP_CLOSE: {
            stream.put(36);
        } break;

        case OP_WRITE: {
            stream.put(37);
        } break;

        case OP_READ: {
            stream.put(38);
        } break;

        case OP_PUT: {
            stream.put(39);
        } break;

        case OP_RAND: {
            stream.put(40);
        } break;

        case OP_MOD: {
            stream.put(41);
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
    static_assert(OP_COUNT == 41 /* Exhaustive handling of OPs in simulate_program() */);
    std::vector <long int> stack = {0};
    std::vector <long int> tmp_buff;
    std::vector <long int> tmp_vect;

    std::fstream progstream;
    std::string curf;

    for (size_t ip = 0; ip < program.size(); ++ip)
    {
        switch (program[ip].type)
        {
        case OP_PLUS: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_PLUS\n";
                exit(1);
            }
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            stack.push_back(a + b);
        } break;

        case OP_MINUS: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_MINUS\n";
                exit(1);
            }
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            stack.push_back(b - a);
        } break;

        case OP_MULT: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_MULT\n";
                exit(1);
            }
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            stack.push_back(b * a);
        } break;

        case OP_DIV: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_DIV\n";
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
                std::cerr << "ERROR: Not enough items for OP_PUTC\n";
                exit(1);
            }
            std::cout << (char) stack.back(); stack.pop_back();
        } break;

        case OP_PUTI: {
            if (stack.size() < 1)
            {
                std::cerr << "ERROR: Not enough items for OP_PUTI\n";
                exit(1);
            }
            std::cout << stack.back(); stack.pop_back();
        } break;

        case OP_DROP: {
            if (stack.size() < 1)
            {
                std::cerr << "ERROR: Not enough items for OP_DROP\n";
                exit(1);
            }
            stack.pop_back();
        } break;

        case OP_DUP: {
            if (stack.size() < 1)
            {
                std::cerr << "ERROR: Not enough items for OP_DUP\n";
                exit(1);
            }
            stack.push_back(stack.back());
        } break;

        case OP_SWAP: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_SWAP\n";
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
                std::cerr << "ERROR: Not enough items for OP_OVER\n";
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
                std::cerr << "ERROR: Not enough items for OP_JMP_IF\n";
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

        case OP_GREATER: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_GREATER\n";
                exit(1);
            }
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            if (b > a)
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

        case OP_OR: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_OR\n";
                exit(1);
            }
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();

            if (a != 0 || b != 0)
            {
                stack.push_back(1);
            }
            else
            {
                stack.push_back(0);
            }
        } break;

        case OP_AND: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_AND\n";
                exit(1);
            }
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();

            if (a != 0 && b != 0)
            {
                stack.push_back(1);
            }
            else
            {
                stack.push_back(0);
            }
        } break;

        case OP_READK: {
            tmp_buff = {};
            std::string str;
            std::getline(std::cin, str);

            for (auto &ch : str)
            {
                tmp_buff.push_back((char) ch);
            }
            tmp_buff.push_back((char) 10);
        } break;

        case OP_AT: {
            if (stack.size() < 1)
            {
                std::cerr << "ERROR: Not enough items for OP_AT\n";
                exit(1);
            }

            int a = stack.back(); stack.pop_back();

            if ((long unsigned int) a > stack.size())
            {
                std::cerr << "ERROR: Element not found on the stack during the execution of OP_AT\n";
                exit(1);
            }

            if (a < 0)
            {
                std::cerr << "ERROR: Use negative numbers to access the stack is not allowed\n";
                exit(1);
            }

            stack.push_back(stack[a]);
        } break;

        case OP_NQDEBUG_STACK: {
            std::cout << "\n!!NOTE!! - Current state of the stack:\nSTART\n";
            for (size_t i = 0; i < stack.size(); ++i)
            {
                std::cout << stack[i] << " ";
            }
            std::cout << "\nEND\n";
        } break;

        case OP_PRINT: {
            std::string str;
            while (!tmp_buff.empty())
            {
                long int c = tmp_buff.front(); tmp_buff.erase(tmp_buff.begin());
                str.push_back((char) c);
            }
            std::cout << str;
            tmp_buff = {};
        } break;

        case OP_TMP_PUSH_INT: {
            tmp_buff.push_back(program[ip].content);
        } break;

        case OP_TMP_DROP: {
            tmp_buff.pop_back();
        } break;

        case OP_NQDEBUG_TMP_BUFF: {
            std::cout << "\n!!NOTE!! - Current state of the temporary buffer:\nSTART\n";
            for (size_t i = 0; i < tmp_buff.size(); ++i)
            {
                std::cout << tmp_buff[i] << " ";
            }
            std::cout << "\nEND\n";
        } break;

        case OP_TMP_AT: {
            if (stack.size() < 1)
            {
                std::cerr << "ERROR: Not enough items for OP_TMP_AT\n";
                exit(1);
            }

            int a = stack.back(); stack.pop_back();

            if ((long unsigned int) a > tmp_buff.size())
            {
                std::cerr << "ERROR: Element not found on the stack during the execution of OP_TMP_AT\n";
                exit(1);
            }

            if (a < 0)
            {
                std::cerr << "ERROR: Use negative numbers to access the temporary buffer is not allowed\n";
                exit(1);
            }

            stack.push_back(tmp_buff[a]);
        } break;

        case OP_ARR_PUSH_INT: {
            tmp_vect.push_back(program[ip].content);
        } break;

        case OP_ARR_DROP: {
            tmp_vect.pop_back();
        } break;

        case OP_ARR_AT: {
            if (stack.size() < 1)
            {
                std::cerr << "ERROR: Not enough items for OP_ARR_AT\n";
                exit(1);
            }

            int a = stack.back(); stack.pop_back();

            if ((long unsigned int) a > tmp_vect.size())
            {
                std::cerr << "ERROR: Element not found on the stack during the execution of OP_ARR_AT\n";
                exit(1);
            }

            if (a < 0)
            {
                std::cerr << "ERROR: Use negative numbers to access the temporary array is not allowed\n";
                exit(1);
            }

            stack.push_back(tmp_vect[a]);
        } break;

        case OP_NQDEBUG_TMP_ARR: {
            std::cout << "\n!!NOTE!! - Current state of the temporary array:\nSTART\n";
            for (size_t i = 0; i < tmp_vect.size(); ++i)
            {
                std::cout << tmp_vect[i] << " ";
            }
            std::cout << "\nEND\n";
        } break;

        case OP_OPEN: {
            if (tmp_buff.empty())
            {
                std::cerr << "ERROR: Input file name is not provided\n";
                exit(1);
            }

            if (progstream.is_open())
            {
                std::cerr << "ERROR: Another file is already open\n";
                exit(1);
            }
            std::string str;
            while (!tmp_buff.empty())
            {
                long int c = tmp_buff.front(); tmp_buff.erase(tmp_buff.begin());
                str.push_back((char) c);
            }
            tmp_buff = {};
            curf = str;

            if (!std::filesystem::is_regular_file(str))
            {
                std::ofstream ofile(str);
                ofile << ' ';
                ofile.close();
            }

            progstream.open(str, std::fstream::in|std::fstream::out);

            if (!progstream.is_open())
            {
                stack.push_back(-1);
            }
        } break;

        case OP_CLOSE: {
            if (!progstream.is_open())
            {
                std::cerr << "ERROR: File is already closed\n";
                exit(1);
            }

            curf = "";
            progstream.close();
        } break;

        case OP_WRITE: {
            if (!progstream.is_open())
            {
                std::cerr << "ERROR: The file stream is not open\n";
                exit(1);
            }

            if (tmp_buff.empty())
            {
                std::cerr << "ERROR: Line to write to the file is not provided\n";
                exit(1);
            }

            std::string str;
            while (!tmp_buff.empty())
            {
                long int c = tmp_buff.front(); tmp_buff.erase(tmp_buff.begin());
                str.push_back((char) c);
            }
            tmp_buff = {};

            progstream << str;
        } break;

        case OP_READ: {
            tmp_buff = {};
            if (!progstream.is_open())
            {
                std::cerr << "ERROR: The file stream is not open\n";
                exit(1);
            }
            progstream.close();

            std::fstream ifs(curf, std::fstream::in);
            std::string str((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));
            ifs.close();

            progstream.open(curf, std::fstream::in|std::fstream::out);
            for (auto &ch : str)
            {
                tmp_buff.push_back((char) ch);
            }
        } break;

        case OP_PUT: {
            if (stack.size() < 1)
            {
                std::cerr << "ERROR: Not enough items for OP_PUT\n";
                exit(1);
            }

            if (!progstream.is_open())
            {
                std::cerr << "ERROR: The file stream is not open\n";
                exit(1);
            }

            int a = stack.back(); stack.pop_back();

            progstream.put(a);
        } break;

        case OP_RAND: {
            stack.push_back(rand());
        } break;

        case OP_MOD: {
            if (stack.size() < 2)
            {
                std::cerr << "ERROR: Not enough items for OP_MOD\n";
                exit(1);
            }
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            stack.push_back(b % a);
        } break;

        default:
            std::cerr << "ERROR: Unreachable\n";
            exit(2);
        }
    }
}
