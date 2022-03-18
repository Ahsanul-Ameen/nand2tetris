CC=g++
CFLAGS=-pipe -O2 -std=c++17 -Wshadow -Wall -Wno-unused-result -fconcepts -lm

.PHONY: all clean debug

all: clean
all: CFLAGS+=-D NDEBUG
all: JackCompiler		

JackCompiler: JackCompiler.o JackTokenizer.o SymbolTable.o VMWriter.o CompilationEngine.o 
	$(CC) $(CFLAGS) JackCompiler.o JackTokenizer.o SymbolTable.o VMWriter.o CompilationEngine.o -o JackCompiler


JackCompiler.o: JackCompiler.cpp 
	$(CC) $(CFLAGS) -c JackCompiler.cpp
	
JackTokenizer.o: JackTokenizer.cpp 
	$(CC) $(CFLAGS) -c JackTokenizer.cpp
	
SymbolTable.o: SymbolTable.cpp 
	$(CC) $(CFLAGS) -c SymbolTable.cpp
	
VMWriter.o: VMWriter.cpp 
	$(CC) $(CFLAGS) -c VMWriter.cpp
	
CompilationEngine.o: CompilationEngine.cpp 
	$(CC) $(CFLAGS) -c CompilationEngine.cpp
	

clean:
	rm -rf *.o JackCompiler

debug: CFLAGS+=-g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -fconcepts -lm
debug: VMTranslator
