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

test_slotted_page: test_slotted_page.cpp SlottedPageStructure.cpp
	$(CXX) -o test_slotted_page test_slotted_page.cpp SlottedPageStructure.cpp $(CXXFLAGS)

run_test_bptSim: test_bptSim
	./test_bptSim

test_bptSim: test_bptSim.cpp BPlusTreeSimulator.cpp
	$(CXX) -o test_bptSim test_bptSim.cpp BPlusTreeSimulator.cpp $(CXXFLAGS)

test_relation: test_relation.cpp Relation.o SlottedPageStructure.o BPlusTreeSimulator.o
	$(CXX) -o test_relation test_relation.cpp Relation.o SlottedPageStructure.o BPlusTreeSimulator.o $(CXXFLAGS)
	./test_relation

Relation.o: Relation.cpp
	$(CXX) -c Relation.cpp $(CXXFLAGS)

SlottedPageStructure.o: SlottedPageStructure.cpp
	$(CXX) -c SlottedPageStructure.cpp $(CXXFLAGS)

BPlusTreeSimulator.o: BPlusTreeSimulator.cpp
	$(CXX) -c BPlusTreeSimulator.cpp $(CXXFLAGS)

BPlusTreeInt.o: BPlusTreeInt.cpp
	$(CXX) -c BPlusTreeInt.cpp $(CXXFLAGS)

BPlusTreeRoger.o: BPlusTreeRoger.cpp
	$(CXX) -c BPlusTreeRoger.cpp $(CXXFLAGS)

test_bptRoger: test_bptRoger.cpp BPlusTreeRoger.o
	$(CXX) -o test_bptRoger test_bptRoger.cpp BPlusTreeRoger.o $(CXXFLAGS)
	./test_bptRoger
