all: main.o f1.o f2.o
	g++ -o out main.o f1.o f2.o

compile: main.o f1.o f2.o
	g++ -o out main.o f1.o f2.o

altcompile: main.cpp f1.cpp f2.cpp
	g++ -o out main.cpp f1.cpp f2.cpp

main.o: main.cpp
	g++ -c main.cpp

f1.o: f1.cpp
	g++ -c f1.cpp

f2.o: f2.cpp
	g++ -c f2.cpp

clean:	
	rm -rf *.o out
