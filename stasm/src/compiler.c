#include "./compiler.h"

#define OP_PUTC              1
#define OP_PUTI              2
#define OP_PLUS              3
#define OP_MINUS             4
#define OP_MULT              5
#define OP_DIV               6
#define OP_PUSH_INT          7
#define OP_DROP              8
#define OP_DUP               9
#define OP_SWAP             10
#define OP_ROT              11
#define OP_OVER             12
#define OP_JMP              13
#define OP_JMP_IF           14
#define OP_DEBUG_STACK      15
#define OP_QUIT             16
#define OP_EQU              17
#define OP_LESS             18
#define OP_GREATER          19
#define OP_NOT              20
#define OP_OR               21
#define OP_AND              22
#define OP_READK            23
#define OP_AT               24
#define OP_NQDEBUG_STACK    25
#define OP_PRINT            26
#define OP_TMP_PUSH_INT     27
#define OP_TMP_DROP         28
#define OP_NQDEBUG_TMP_BUFF 29
#define OP_TMP_AT           30
#define OP_ARR_PUSH_INT     31
#define OP_ARR_DROP         32
#define OP_ARR_AT           33
#define OP_NQDEBUG_TMP_ARR  34
#define OP_OPEN             35
#define OP_CLOSE            36
#define OP_WRITE            37
#define OP_READ             38
#define OP_PUT              39
#define OP_RAND             40
#define OP_MOD              41
#define OP_NULL             42
#define OP_COUNT            43

typedef struct {
    String_View name;
    char loc;
} Label;

#define PROGRAM_CAP 1024
char program[PROGRAM_CAP] = {0};
size_t program_sz = 0;

#define LABEL_CAP 1024
Label labels[LABEL_CAP] = {0};
size_t label_sz = 0;

int silent = 0;

void compiler_info(const char* message, ...)
{
    if (!silent)
    {
        va_list args;
        va_start(args, message);
        printf("[INFO] ");
        vfprintf(stdout, message, args);
        va_end(args);
    }
}

void update_labels(String_View source)
{
    char cur_index = 0;
    String_View mut_src = source;
    while (mut_src.count > 0)
    {
        String_View line = sv_trim(sv_chop_by_delim(&mut_src, '\n'));
        if (line.count > 0)
        {
            line = sv_trim(sv_chop_by_delim(&line, ';'));
            String_View inst;
            while (line.count > 0)
            {
                inst = sv_trim(sv_chop_by_delim(&line, ' '));
                if (inst.count > 0)
                {
                    if (is_label(inst))
                    {
                        String_View name = sv_trim(sv_chop_by_delim(&inst, ':'));
                        labels[label_sz++] = (Label) {.name = name, .loc = cur_index - 1};
                    }
                    static_assert(OP_COUNT == 43 /* If another instruction use 2 bytes,
                                                    add to this huge ugly condition */);
                    if (!(sv_eq(inst, sv_from_cstr("pushi"))   ||
                          sv_eq(inst, sv_from_cstr("t-pushi")) ||
                          sv_eq(inst, sv_from_cstr("a-pushi")) ||
                          sv_eq(inst, sv_from_cstr("jmp"))     ||
                          sv_eq(inst, sv_from_cstr("jmp-if"))  ))
                        cur_index += 1;
                }
            }
        }
    }
}

int is_label(String_View token)
{
    for (size_t i = 0; i < token.count; ++i) {
        if (isspace(token.data[i]))
        {
            return 0;
        }
    }
    return sv_ends_with(token, sv_from_cstr(":"));
}

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
        else if (sv_eq(tokens[i], sv_from_cstr("minus")))
        {
            program[program_sz++] = OP_MINUS;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("mult")))
        {
            program[program_sz++] = OP_MULT;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("div")))
        {
            program[program_sz++] = OP_DIV;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("mod")))
        {
            program[program_sz++] = OP_MOD;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("rand")))
        {
            program[program_sz++] = OP_RAND;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("puti")))
        {
            program[program_sz++] = OP_PUTI;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("putc")))
        {
            program[program_sz++] = OP_PUTC;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("t-pushi")))
        {
            program[program_sz++] = OP_TMP_PUSH_INT;
            program[program_sz++] = (char) sv_to_int(tokens[++i]);
        }
        else if (sv_eq(tokens[i], sv_from_cstr("t-drop")))
        {
            program[program_sz++] = OP_TMP_DROP;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("t-at")))
        {
            program[program_sz++] = OP_TMP_AT;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("print")))
        {
            program[program_sz++] = OP_PRINT;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("a-pushi")))
        {
            program[program_sz++] = OP_ARR_PUSH_INT;
            program[program_sz++] = (char) sv_to_int(tokens[++i]);
        }
        else if (sv_eq(tokens[i], sv_from_cstr("a-drop")))
        {
            program[program_sz++] = OP_ARR_DROP;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("a-at")))
        {
            program[program_sz++] = OP_ARR_AT;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("jmp")))
        {
            String_View labelname = sv_trim(sv_chop_by_delim(&tokens[++i], ':'));
            int exists = 0;
            for (size_t l = 0; l < label_sz; ++l) {
                if (sv_eq(labels[l].name, labelname))
                {
                    program[program_sz++] = OP_JMP;
                    program[program_sz++] = labels[l].loc;
                    exists = 1;
                    break;
                }
            }
            if (!exists)
            {
                fprintf(stderr, "ERROR: Label `"SV_Fmt"` does not exists\n", SV_Arg(labelname));
                exit(1);
            }
        }
        else if (sv_eq(tokens[i], sv_from_cstr("jmp-if")))
        {
            String_View labelname = sv_trim(sv_chop_by_delim(&tokens[++i], ':'));
            int exists = 0;
            for (size_t l = 0; l < label_sz; ++l) {
                if (sv_eq(labels[l].name, labelname))
                {
                    program[program_sz++] = OP_JMP_IF;
                    program[program_sz++] = labels[l].loc;
                    exists = 1;
                    break;
                }
            }
            if (!exists)
            {
                fprintf(stderr, "ERROR: Label `"SV_Fmt"` does not exists\n", SV_Arg(labelname));
                exit(1);
            }
        }
        else if (sv_eq(tokens[i], sv_from_cstr("!")))
        {
            program[program_sz++] = OP_NOT;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("=")))
        {
            program[program_sz++] = OP_EQU;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("<")))
        {
            program[program_sz++] = OP_LESS;
        }
        else if (sv_eq(tokens[i], sv_from_cstr(">")))
        {
            program[program_sz++] = OP_GREATER;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("||")))
        {
            program[program_sz++] = OP_OR;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("&&")))
        {
            program[program_sz++] = OP_AND;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("dup")))
        {
            program[program_sz++] = OP_DUP;
        }
        else
        {
            if (!is_label(tokens[i]))
            {
                fprintf(stderr, "ERROR: Unknown instruction: "SV_Fmt"\n", SV_Arg(tokens[i]));
                exit(1);
            }
        }
    }
}

void compile_program(const char* fpath, const char* outpath, int fsilent)
{
    FILE* file = fopen(fpath, "rb");
    char* buffer = 0;
    size_t length;
    silent = fsilent;

    compiler_info("Compiling program...\n");

    if (file == NULL)
    {
        fprintf(stderr, "ERROR: Could not open `%s`: %s\n",
                fpath, strerror(errno));
        exit(3);
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

    if (!silent)
        timefhere();

    update_labels(source);
    while (source.count > 0) {
        String_View line = sv_trim(sv_chop_by_delim(&source, '\n'));
        if (line.count > 0) {
            translate_line(line);
        }
    }

    if (!silent)
        timeresult("Compilation");

    compiler_info("Generating output `%s`...\n", outpath);
    FILE* output = fopen(outpath, "wb");
    fwrite(program, sizeof(program[0]), sizeof(program[0]) * program_sz,
           output);
    fclose(output);
}
