CC=g++
CFLAGS=-pipe -O2 -std=c++17 -Wshadow -Wall -Wno-unused-result -fconcepts -lm

.PHONY: all clean debug

all: clean
all: CFLAGS+=-D NDEBUG
all: JackAnalyzer		

JackAnalyzer: JackAnalyzer.o JackTokenizer.o CompilationEngine.o
	$(CC) $(CFLAGS) JackAnalyzer.o JackTokenizer.o CompilationEngine.o -o JackAnalyzer


JackAnalyzer.o: JackAnalyzer.cpp 
	$(CC) $(CFLAGS) -c JackAnalyzer.cpp
	
JackTokenizer.o: JackTokenizer.cpp 
	$(CC) $(CFLAGS) -c JackTokenizer.cpp
	
CompilationEngine.o: CompilationEngine.cpp 
	$(CC) $(CFLAGS) -c CompilationEngine.cpp
	

clean:
	rm -rf *.o JackAnalyzer

debug: CFLAGS+=-g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -fconcepts -lm
debug: VMTranslator
