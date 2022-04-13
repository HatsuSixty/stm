CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb

all: stasm

stasm: ./src/main.o ./src/compiler.o ./src/sv.o
	$(CC) $(CFLAGS) -o stasm ./src/main.o ./src/compiler.o ./src/sv.o

./src/main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -o ./src/main.o

./src/compiler.o: ./src/compiler.c
	$(CC) $(CFLAGS) -c ./src/compiler.c -o ./src/compiler.o

./src/sv.o: ./src/sv.c
	$(CC) $(CFLAGS) -c ./src/sv.c -o ./src/sv.o

clean:
	rm ./stasm
	rm ./src/*.o

./src/main.c: ./src/compiler.h
./src/sv.c: ./src/sv.h ./src/operators.h
