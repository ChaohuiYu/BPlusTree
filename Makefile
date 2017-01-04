all: main
	./main

main: main.cpp
	g++ -std=c++11 -o main main.cpp

run_main: main
	./main
