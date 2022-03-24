#ifndef COMPILER_HPP_
#define COMPILER_HPP_

#include <cstddef>
#include <cassert>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

#include "./operators.hpp"

std::vector <Op> load(std::string path);
void save(std::string path, std::vector <Op> program);
void simulate_program(std::vector <Op> program);

#endif // COMPILER_HPP_
