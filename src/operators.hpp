#ifndef OPERATORS_HPP_
#define OPERATORS_HPP_

typedef enum {
    OP_PRINT,
    OP_PLUS,
    OP_MINUS,
    OP_MULT,
    OP_DIV,
    OP_PUSH_INT,
    OP_DROP,
    OP_COUNT
} OpType;

typedef struct {
    OpType type;
    int content;
} Op;

#endif // OPERATORS_HPP_
