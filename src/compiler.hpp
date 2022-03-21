#ifndef COMPILER_HPP_
#define COMPILER_HPP_

#include <cstddef>
#include <cassert>
#include <iostream>

#include "operators.hpp"

#define STACK_CAP 1024
int stack[STACK_CAP] = {0};
size_t stack_size = 0;

void simulate_program(Op *program, size_t stack_sz);

#endif // COMPILER_HPP_
