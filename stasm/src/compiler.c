#include "./compiler.h"

// i cant put it in a header :(
const char OP_PUTC             = (char)  1;
const char OP_PUTI             = (char)  2;
const char OP_PLUS             = (char)  3;
const char OP_MINUS            = (char)  4;
const char OP_MULT             = (char)  5;
const char OP_DIV              = (char)  6;
const char OP_PUSH_INT         = (char)  7;
const char OP_DROP             = (char)  8;
const char OP_DUP              = (char)  9;
const char OP_SWAP             = (char) 10;
const char OP_ROT              = (char) 11;
const char OP_OVER             = (char) 12;
const char OP_JMP              = (char) 13;
const char OP_JMP_IF           = (char) 14;
const char OP_DEBUG_STACK      = (char) 15;
const char OP_QUIT             = (char) 16;
const char OP_EQU              = (char) 17;
const char OP_LESS             = (char) 18;
const char OP_GREATER          = (char) 19;
const char OP_NOT              = (char) 20;
const char OP_OR               = (char) 21;
const char OP_AND              = (char) 22;
const char OP_READK            = (char) 23;
const char OP_AT               = (char) 24;
const char OP_NQDEBUG_STACK    = (char) 25;
const char OP_PRINT            = (char) 26;
const char OP_TMP_PUSH_INT     = (char) 27;
const char OP_TMP_DROP         = (char) 28;
const char OP_NQDEBUG_TMP_BUFF = (char) 29;
const char OP_TMP_AT           = (char) 30;
const char OP_ARR_PUSH_INT     = (char) 31;
const char OP_ARR_DROP         = (char) 32;
const char OP_ARR_AT           = (char) 33;
const char OP_NQDEBUG_TMP_ARR  = (char) 34;
const char OP_OPEN             = (char) 35;
const char OP_CLOSE            = (char) 36;
const char OP_WRITE            = (char) 37;
const char OP_READ             = (char) 38;
const char OP_PUT              = (char) 39;
const char OP_RAND             = (char) 40;
const char OP_MOD              = (char) 41;
const char OP_NULL             = (char) 42;
const char OP_COUNT            = (char) 43;

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
