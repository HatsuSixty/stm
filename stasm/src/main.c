#include <stdio.h>
#include <stdlib.h>
#include "./compiler.h"

int compare(const char a[], const char b[])
{
    int flag = 1;
    int i = 0;

    while((a[i] != '\0') && (b[i] != '\0'))
    {
        if(a[i] != b[i])
        {
            flag = 0;
            break;
        }
        i++;
    }
    return flag;
}

void usage(FILE* stream)
{
    fprintf(stream, "Usage:\n");
    fprintf(stream, "    stasm <flags>\n");
    fprintf(stream, "\n");
    fprintf(stream, "flags:\n");
    fprintf(stream, "    -f | --file   - Compile the specified program into STM bytecode\n");
    fprintf(stream, "    -s | --silent - Do not display log messages\n");
    fprintf(stream, "    -h | --help   - Print this help\n");
}

int main(int argc, char *argv[])
{
    char* fpath = (char*)malloc(sizeof(char) * 255);
    int silent = 0;

    if (argc < 2)
    {
        usage(stderr);
        fprintf(stderr, "ERROR: Argument not provided\n");
        exit(4);
    }

    for (size_t i = 1; i < (size_t) argc; ++i) {
        if (compare(argv[i], "-h") || compare(argv[i], "--help"))
        {
            usage(stdout);
            exit(0);
        }
        else if (compare(argv[i], "-f") || compare(argv[i], "--file"))
        {
            if ((size_t) (argc - 1) < (i + 1))
            {
                fprintf(stderr, "ERROR: No input file is provided\n");
                exit(4);
            }

            fpath = argv[++i];
        }
        else if (compare(argv[i], "-s") || compare(argv[i], "--silent"))
        {
            silent = 1;
        }
        else
        {
            usage(stderr);
            fprintf(stderr, "ERROR: Unknown flag `%s`\n", argv[i]);
            exit(4);
        }
    }

    compile_program(fpath);
    return 0;
}
