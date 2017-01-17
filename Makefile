CXX=g++
CXXFLAGS=-std=c++11 -Wall

all: main

run: main
	./main

main: main.o parser.o commands.o
	$(CXX) -o main main.o parser.o commands.o $(CXXFLAGS)

main.o: main.cpp parser.h
	$(CXX) -c main.cpp $(CXXFLAGS)

parser.o: parser.cpp commands.h
	$(CXX) -c parser.cpp $(CXXFLAGS)

commands.o: commands.cpp
	$(CXX) -c commands.cpp $(CXXFLAGS)


run_test_slotted_page: test_slotted_page
	./test_slotted_page

test_slotted_page: test_slotted_page.cpp SlottedPage.cpp
	$(CXX) -o test_slotted_page test_slotted_page.cpp SlottedPage.cpp $(CXXFLAGS)
