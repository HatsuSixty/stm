#ifndef TOKENS_H_
#define TOKENS_H_

#include <string>

typedef enum {
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_PUSH_INT,
    TOKEN_DROP,
    TOKEN_DUP,
    TOKEN_SWAP,
    TOKEN_ROT,
    TOKEN_DEBUG_STACK,
    TOKEN_COUNT
} TokenType;

typedef struct {
    TokenType type;
    std::string loc;
    int ip;
} Token;

#endif // TOKENS_H_
