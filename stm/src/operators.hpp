#ifndef OPERATORS_HPP_
#define OPERATORS_HPP_

typedef enum {
    OP_PUTC,
    OP_PUTI,
    OP_PLUS,
    OP_MINUS,
    OP_MULT,
    OP_DIV,
    OP_PUSH_INT,
    OP_DROP,
    OP_DUP,
    OP_SWAP,
    OP_ROT,
    OP_OVER,
    OP_JMP,
    OP_JMP_IF,
    OP_DEBUG_STACK,
    OP_QUIT,
    OP_EQU,
    OP_LESS,
    OP_GREATER,
    OP_NOT,
    OP_OR,
    OP_AND,
    OP_COUNT
} OpType;

typedef struct {
    OpType type;
    int content = 0;
} Op;

#endif // OPERATORS_HPP_
