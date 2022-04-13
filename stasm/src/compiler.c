#include "./compiler.h"

// i cant put it in a header :(
#define OP_PUTC             (char)  1;
#define OP_PUTI             (char)  2;
#define OP_PLUS             (char)  3;
#define OP_MINUS            (char)  4;
#define OP_MULT             (char)  5;
#define OP_DIV              (char)  6;
#define OP_PUSH_INT         (char)  7;
#define OP_DROP             (char)  8;
#define OP_DUP              (char)  9;
#define OP_SWAP             (char) 10;
#define OP_ROT              (char) 11;
#define OP_OVER             (char) 12;
#define OP_JMP              (char) 13;
#define OP_JMP_IF           (char) 14;
#define OP_DEBUG_STACK      (char) 15;
#define OP_QUIT             (char) 16;
#define OP_EQU              (char) 17;
#define OP_LESS             (char) 18;
#define OP_GREATER          (char) 19;
#define OP_NOT              (char) 20;
#define OP_OR               (char) 21;
#define OP_AND              (char) 22;
#define OP_READK            (char) 23;
#define OP_AT               (char) 24;
#define OP_NQDEBUG_STACK    (char) 25;
#define OP_PRINT            (char) 26;
#define OP_TMP_PUSH_INT     (char) 27;
#define OP_TMP_DROP         (char) 28;
#define OP_NQDEBUG_TMP_BUFF (char) 29;
#define OP_TMP_AT           (char) 30;
#define OP_ARR_PUSH_INT     (char) 31;
#define OP_ARR_DROP         (char) 32;
#define OP_ARR_AT           (char) 33;
#define OP_NQDEBUG_TMP_ARR  (char) 34;
#define OP_OPEN             (char) 35;
#define OP_CLOSE            (char) 36;
#define OP_WRITE            (char) 37;
#define OP_READ             (char) 38;
#define OP_PUT              (char) 39;
#define OP_RAND             (char) 40;
#define OP_MOD              (char) 41;
#define OP_NULL             (char) 42;
#define OP_COUNT            (char) 43;

#define PROGRAM_CAP 1024
char program[PROGRAM_CAP] = {0};
size_t program_sz;

#define TOKENS_CAP 1024
void translate_line(String_View line)
{
    String_View tokens[1024];
    size_t tokens_sz = 0;

    line = sv_trim(sv_chop_by_delim(&line, ';'));
    String_View inst;
    while (line.count > 0) {
        inst = sv_trim(sv_chop_by_delim(&line, ' '));
        if (inst.count > 0) {
            tokens[tokens_sz++] = inst;
        }
    }

    for (size_t i = 0; i < tokens_sz; ++i) {
        if (sv_eq(tokens[i], sv_from_cstr("pushi")))
        {
            program[program_sz++] = OP_PUSH_INT;
            program[program_sz++] = (char) sv_to_int(tokens[++i]);
        }
        else if (sv_eq(tokens[i], sv_from_cstr("plus")))
        {
            program[program_sz++] = OP_PLUS;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("puti")))
        {
            program[program_sz++] = OP_PUTI;
        }
        else
        {
            fprintf(stderr, "ERROR: Unknown instruction: "SV_Fmt"\n",
                    (int) tokens[i].count, tokens[i].data);
            exit(1);
        }
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

    FILE* output = fopen("output.stm", "wb");
    fwrite(program, sizeof(program[0]), sizeof(program[0]) * program_sz,
           output);
    fclose(output);
}
