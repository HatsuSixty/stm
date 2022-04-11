all: stasm

stasm: ./src/main.o ./src/compiler.o
	$(CC) $(CFLAGS) -o stasm ./src/main.o ./src/compiler.o

./src/main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -o ./src/main.o

./src/compiler.o: ./src/compiler.c
	$(CC) $(CFLAGS) -c ./src/compiler.c -o ./src/compiler.o

clean:
	rm ./stasm
	rm ./src/*.o

./src/main.c: ./src/compiler.h
