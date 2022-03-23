#ifndef LEXER_H_
#define LEXER_H_

#include <vector>
#include <string>
#include <fstream>
#include <cerrno>
#include <iostream>
#include <cstring>

#include "tokens.hpp"

std::vector <Token> tokenize_file(std::string path);

#endif // LEXER_H_
