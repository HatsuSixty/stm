#include "./compiler.h"

#define TOKENS_CAP 1024
void translate_line(String_View line)
{
    String_View tokens[1024];
    size_t tokens_sz = 0;

    line = sv_trim(sv_chop_by_delim(&line, '#'));
    String_View inst;
    while (line.count > 0) {
        inst = sv_trim(sv_chop_by_delim(&line, ' '));
        if (inst.count > 0) {
            tokens[tokens_sz++] = inst;
        }
    }

    for (size_t i = 0; i < tokens_sz; ++i)
    {
        printf(""SV_Fmt"\n", (int) tokens[i].count, tokens[i].data);
    }
}

void compile_program(const char* fpath)
{
    FILE* file = fopen(fpath, "rb");
    char* buffer = 0;
    size_t length;

    if (file == NULL)
    {
        fprintf(stderr, "ERROR: Could not open `%s`: %s\n",
                fpath, strerror(errno));
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(length);

    if (buffer == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for file: %s",
                strerror(errno));
        exit(1);
    }
    fread(buffer, 1, length, file);
    fclose(file);
    String_View source = sv_from_cstr(buffer);

    while (source.count > 0) {
        String_View line = sv_trim(sv_chop_by_delim(&source, '\n'));
        if (line.count > 0) {
            translate_line(line);
        }
    }
}
