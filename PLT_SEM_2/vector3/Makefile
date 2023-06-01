all: program

clean:
	rm -rf program *.o
main.o: main.cpp
	g++ -c -o main.o main.cpp
vector3.o: vector3.cpp
	g++ -c -o vector3.o vector3.cpp
program: main.o vector3.o
	g++ -o program main.o vector3.o
