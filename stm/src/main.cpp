#include <iostream>
#include <vector>
#include <cstdio>

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
};

std::vector <Op> hello = {
    {.type = OP_TMP_PUSH_INT, .content = 104},
    {.type = OP_TMP_PUSH_INT, .content = 101},
    {.type = OP_TMP_PUSH_INT, .content = 108},
    {.type = OP_TMP_PUSH_INT, .content = 108},
    {.type = OP_TMP_PUSH_INT, .content = 111},
    {.type = OP_TMP_PUSH_INT, .content =  44},
    {.type = OP_TMP_PUSH_INT, .content =  32},
    {.type = OP_TMP_PUSH_INT, .content = 119},
    {.type = OP_TMP_PUSH_INT, .content = 111},
    {.type = OP_TMP_PUSH_INT, .content = 114},
    {.type = OP_TMP_PUSH_INT, .content = 108},
    {.type = OP_TMP_PUSH_INT, .content = 100},
    {.type = OP_TMP_PUSH_INT, .content =  33},
    {.type = OP_TMP_PUSH_INT, .content =  10},
    {.type = OP_PRINT},
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
    {.type = OP_PUSH_INT, .content = 1},
    {.type = OP_PUSH_INT, .content = 0},
    {.type = OP_AND},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
};

std::vector <Op> readk {
    {.type = OP_READK},
    {.type = OP_PRINT},
};

std::vector <Op> op_at {
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUSH_INT, .content = 20},
    {.type = OP_PUSH_INT, .content = 30},
    {.type = OP_PUSH_INT, .content = 40},
    {.type = OP_PUSH_INT, .content = 50},
    {.type = OP_PUSH_INT, .content = 60},
    {.type = OP_PUSH_INT, .content =  2},
    {.type = OP_AT},
    {.type = OP_PUTI},
};

std::vector <Op> nqdebug {
    {.type = OP_PUSH_INT, .content = 1},
    {.type = OP_PUSH_INT, .content = 2},
    {.type = OP_PUSH_INT, .content = 3},
    {.type = OP_PUSH_INT, .content = 4},
    {.type = OP_NQDEBUG_STACK},
};

std::vector <Op> tmp_buff {
    {.type = OP_TMP_PUSH_INT, .content = 100},
    {.type = OP_TMP_PUSH_INT, .content = 101},
    {.type = OP_TMP_DROP},
    {.type = OP_TMP_PUSH_INT, .content = 101},
    {.type = OP_NQDEBUG_TMP_BUFF},
    {.type = OP_PRINT},
    {.type = OP_NQDEBUG_TMP_BUFF},
};

std::vector <Op> op_tmp_at = {
    {.type = OP_TMP_PUSH_INT, .content = 10},
    {.type = OP_TMP_PUSH_INT, .content = 20},
    {.type = OP_PUSH_INT, .content = 0},
    {.type = OP_TMP_AT},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
    {.type = OP_PUSH_INT, .content = 1},
    {.type = OP_TMP_AT},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
};

std::vector <Op> tmp_arr {
    {.type = OP_ARR_PUSH_INT, .content = 10},
    {.type = OP_ARR_PUSH_INT, .content = 20},
    {.type = OP_ARR_DROP},
    {.type = OP_ARR_PUSH_INT, .content = 20},
    {.type = OP_ARR_PUSH_INT, .content = 30},
    {.type = OP_PUSH_INT, .content = 0},
    {.type = OP_ARR_AT},
    {.type = OP_PUTI},
    {.type = OP_PUSH_INT, .content = 10},
    {.type = OP_PUTC},
    {.type = OP_NQDEBUG_TMP_ARR},
};

std::vector <Op> files = {
    {.type = OP_TMP_PUSH_INT, .content = 104},
    {.type = OP_TMP_PUSH_INT, .content = 101},
    {.type = OP_TMP_PUSH_INT, .content = 108},
    {.type = OP_TMP_PUSH_INT, .content = 108},
    {.type = OP_TMP_PUSH_INT, .content = 111},
    {.type = OP_TMP_PUSH_INT, .content =  46},
    {.type = OP_TMP_PUSH_INT, .content = 116},
    {.type = OP_TMP_PUSH_INT, .content = 120},
    {.type = OP_TMP_PUSH_INT, .content = 116},
    {.type = OP_OPEN},
    {.type = OP_TMP_PUSH_INT, .content = 104},
    {.type = OP_TMP_PUSH_INT, .content = 101},
    {.type = OP_TMP_PUSH_INT, .content = 108},
    {.type = OP_TMP_PUSH_INT, .content = 108},
    {.type = OP_TMP_PUSH_INT, .content = 111},
    {.type = OP_TMP_PUSH_INT, .content =  10},
    {.type = OP_WRITE},
    {.type = OP_READ},
    {.type = OP_PRINT},
    {.type = OP_CLOSE},
};

////////// END EXAMPLES //////////

bool compare(const char a[], const char b[])
{
    bool flag = true;
    int i = 0;

    while((a[i] != '\0') && (b[i] != '\0'))
    {
        if(a[i] != b[i])
        {
            flag = false;
            break;
        }
        i++;
    }
    return flag;
}

void usage(FILE* stream)
{
    fprintf(stream, "Usage:\n");
    fprintf(stream, "    stm <flags>\n");
    fprintf(stream, "\n");
    fprintf(stream, "flags:\n");
    fprintf(stream, "    -h  | --help               - Print this help\n");
    fprintf(stream, "    -f  | --file <input.stm>   - Simulate the specified file\n");
    fprintf(stream, "    -e  | --example <example>  - Generate the specified example\n");
    fprintf(stream, "    -le | --list-examples      - List avaiable examples\n");
}

int main(int argc, char *argv[])
{
    std::string file_to_simulate;

    if (argc < 2)
    {
        usage(stderr);
        std::cerr << "ERROR: no flag is provided\n";
        exit(4);
    }

    for (size_t i = 1; i < (size_t) argc; ++i)
    {
        if (compare(argv[i], "-h") || compare(argv[i], "--help"))
        {
            usage(stdout);
            exit(0);
        }
        else if (compare(argv[i], "-f") || compare(argv[i], "--file"))
        {
            if ((size_t) (argc - 1) < (i + 1))
            {
                usage(stderr);
                std::cerr << "ERROR: no input file is provided\n";
                exit(4);
            }
            else
            {
                file_to_simulate = argv[++i];
            }
        }
        else if (compare(argv[i], "-le") || compare(argv[i], "--list-examples"))
        {
            std::cout << "Avaiable examples:\n"
                      << "    lessngreater\n"
                      << "    andnor\n"
                      << "    counter\n"
                      << "    ifs\n"
                      << "    hello\n"
                      << "    basics\n"
                      << "    readk\n"
                      << "    op_at\n"
                      << "    nqdebug\n"
                      << "    tmp_buff"
                      << "    op_tmp_at\n"
                      << "    tmp_arr\n"
                      << "    files\n"
                      << "    all\n";
            exit(0);
        }
        else if (compare(argv[i], "-e") || compare(argv[i], "--example"))
        {
            if ((size_t) (argc - 1) < (i + 1))
            {
                usage(stderr);
                std::cerr << "ERROR: no example is provided\n";
                exit(4);
            }

            std::string chosen_example = argv[++i];

            if (chosen_example == "lessngreater")
            {
                save("./lessngreater.stm", lessngreater);
                exit(0);
            }
            else if (chosen_example == "andnor")
            {
                save("./andnor.stm", andnor);
                exit(0);
            }
            else if (chosen_example == "counter")
            {
                save("./counter.stm", counter);
                exit(0);
            }
            else if (chosen_example == "ifs")
            {
                save("./ifs.stm", ifs);
                exit(0);
            }
            else if (chosen_example == "hello")
            {
                save("./hello.stm", hello);
                exit(0);
            }
            else if (chosen_example == "basics")
            {
                save("./basics.stm", program);
                exit(0);
            }
            else if (chosen_example == "readk")
            {
                save("./readk.stm", readk);
                exit(0);
            }
            else if (chosen_example == "op_at")
            {
                save("./op_at.stm", op_at);
                exit(0);
            }
            else if (chosen_example == "nqdebug")
            {
                save("./nqdebug.stm", nqdebug);
                exit(0);
            }
            else if (chosen_example == "tmp_buff")
            {
                save("./tmp_buff.stm", tmp_buff);
                exit(0);
            }
            else if (chosen_example == "op_tmp_at")
            {
                save("./op_tmp_at.stm", op_tmp_at);
                exit(0);
            }
            else if (chosen_example == "tmp_arr")
            {
                save("./tmp_arr.stm", tmp_arr);
                exit(0);
            }
            else if (chosen_example == "files")
            {
                save("./files.stm", files);
                exit(0);
            }
            else if (chosen_example == "all")
            {
                save("./lessngreater.stm", lessngreater);
                save("./andnor.stm", andnor);
                save("./counter.stm", counter);
                save("./ifs.stm", ifs);
                save("./hello.stm", hello);
                save("./readk.stm", readk);
                save("./basics.stm", program);
                save("./op_at.stm", op_at);
                save("./nqdebug.stm", nqdebug);
                save("./tmp_buff.stm", tmp_buff);
                save("./op_tmp_at.stm", op_tmp_at);
                save("./tmp_arr.stm", tmp_arr);
                save("./files.stm", files);
                exit(0);
            }
            else
            {
                std::cerr << "ERROR: unknown example: `" << chosen_example << "`\n";
                exit(4);
            }
        }
        else
        {
            usage(stderr);
            std::cerr << "ERROR: unknown flag: `" << argv[i] << "`\n";
            exit(4);
        }
    }

    std::vector <Op> generated_program = load(file_to_simulate);
    simulate_program(generated_program);
    return 0;
}
