all: main.cpp person.cpp person.h person main
main: main.cpp
	g++ -pedantic-errors -g main.cpp person -o main
person: person.cpp person.h
	g++ -pedantic-errors -g -c person.cpp -o person