CC=g++
CFLAGS=-pipe -O2 -std=c++17 -Wshadow -Wall -Wno-unused-result -fconcepts -lm

.PHONY: all clean debug

all: clean
all: CFLAGS+=-D NDEBUG
all: Assembler		

Assembler: Assembler.o SymbolTable.o Code.o Parser.o
	$(CC) $(CFLAGS) Assembler.o SymbolTable.o Code.o Parser.o -o Assembler


Assembler.o: Assembler.cpp 
	$(CC) $(CFLAGS) -c Assembler.cpp

SymbolTable.o: SymbolTable.cpp 
	$(CC) $(CFLAGS) -c SymbolTable.cpp
	
Code.o: Code.cpp 
	$(CC) $(CFLAGS) -c Code.cpp

Parser.o: Parser.cpp 
	$(CC) $(CFLAGS) -c Parser.cpp
	
clean:
	rm -rf *.o Assembler

debug: CFLAGS+=-g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -fconcepts -lm
debug: Assembler
