CXX      = g++
CXXFLAGS = -Wall -Wextra -ggdb -pedantic -std=c++20

all: systack

systack: ./src/main.o ./src/compiler.o
	$(CXX) $(CXXFLAGS) -o systack ./src/main.o ./src/compiler.o

./src/main.o: ./src/main.cpp
	$(CXX) $(CXXFLAGS) -c ./src/main.cpp -o ./src/main.o

./src/compiler.o: ./src/compiler.cpp
	$(CXX) $(CXXFLAGS) -c ./src/compiler.cpp -o ./src/compiler.o

clean:
	rm ./src/*.o
	rm ./systack

./src/main.cpp: ./src/operators.hpp
./src/compiler.cpp: ./src/compiler.hpp ./src/operators.hpp
