#include "./compiler.h"

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
            printf(""SV_Fmt"\n", (int) line.count, line.data);
        }
    }
}
