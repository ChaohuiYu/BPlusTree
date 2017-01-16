#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <ctime>
using namespace std;

// R, Chat, integer, 90
// R, Movie, String, 100
void createRelation(const string& relationName, const string& keyType, const int& recordLength) {
    // need to check if keyType is "integer" or "String"
}

// I, Chat, 416, "Hello world!"
// I, Movie, "nkpgrtgadybxphreddb", "xnrmnw osiyjc spidi"
// convert key to int if the relation use int key
// quotation mark (") should have been removed
void insertRecord(const string& relationName, const string& key, const string& record) {
    // need to check if key should be integer
    // need to check if key exists
}

// D, Chat, 140
// D, Movie, "skbeefznqbhky"
void deleteRecord(const string& relationName, const string& key) {
    // need to check if key should be integer
    // need to check if key exists
}

// Scan Chat
void scanRelation(const string& relationName) {

}

// q Chat 81
// q Movie "fhhhoujqvdxejh"
void queryRecord(const string& relationName, const string& key) {

}

// q Chat 170 296
// q Movie "owjafbcada" "xzrlijkeuufoyxj"
void rangeQueryRecords(const string& relationName, const string& key1, const string& key2) {

}

// p relation-name page-id
void displayPage(const string& relationName, const string& pageId) {

}

// c Chat
void statisticsRelation(const string& relationName) {

}
