CXX=g++
CXXFLAGS=-std=c++11 -Wall

all: main

run: main
	./main

main: main.o parser.o commands.o Relation.o SlottedPageStructure.o BPlusTree.o
	$(CXX) -o main main.o parser.o commands.o Relation.o SlottedPageStructure.o BPlusTree.o $(CXXFLAGS)

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

test_relation: test_relation.cpp Relation.o SlottedPageStructure.o BPlusTree.o
	$(CXX) -o test_relation test_relation.cpp Relation.o SlottedPageStructure.o BPlusTree.o $(CXXFLAGS)
	./test_relation

Relation.o: Relation.cpp
	$(CXX) -c Relation.cpp $(CXXFLAGS)

SlottedPageStructure.o: SlottedPageStructure.cpp
	$(CXX) -c SlottedPageStructure.cpp $(CXXFLAGS)

BPlusTreeSimulator.o: BPlusTreeSimulator.cpp
	$(CXX) -c BPlusTreeSimulator.cpp $(CXXFLAGS)

BPlusTreeInt.o: BPlusTreeInt.cpp
	$(CXX) -c BPlusTreeInt.cpp $(CXXFLAGS)

BPlusTree.o: BPlusTree.cpp
	$(CXX) -c BPlusTree.cpp $(CXXFLAGS)

test_bpt: test_bpt.cpp BPlusTree.o
	$(CXX) -o test_bpt test_bpt.cpp BPlusTree.o $(CXXFLAGS)
	./test_bpt
