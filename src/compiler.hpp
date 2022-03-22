#ifndef COMPILER_HPP_
#define COMPILER_HPP_

#include <cstddef>
#include <cassert>
#include <iostream>
#include <vector>

#include "operators.hpp"

void simulate_program(Op *program, size_t program_sz);

#endif // COMPILER_HPP_
