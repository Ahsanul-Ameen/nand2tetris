CC=g++
CFLAGS=-pipe -O2 -std=c++17 -Wshadow -Wall -Wno-unused-result -fconcepts -lm

.PHONY: all clean debug

all: CFLAGS+=-D NDEBUG
all: VMTranslator		

VMTranslator: VMTranslator.o
	$(CC) $(CFLAGS) VMTranslator.o -o VMTranslator


VMTranslator.o: VMTranslator.cpp
	$(CC) $(CFLAGS) -c VMTranslator.cpp

clean:
	rm -rf *.o VMTranslator

debug: CFLAGS+=-g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -fconcepts -lm
debug: VMTranslator
