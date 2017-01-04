#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <ctime>
using namespace std;

void parseInputData(const string& filename) {
    ifstream infile(filename);
    string line, cell;

    while(getline(infile, line)) {
    stringstream lineStream(line);
        while(getline(lineStream, cell, ',')) {
            cout << cell << endl;
        }
    }
}

void parseTestData(const string& filename) {
    ifstream infile(filename);
    string line, cell;

    while(getline(infile, line)) {
    stringstream lineStream(line);
        while(getline(lineStream, cell, ' ')) {
            cout << cell << endl;
        }
    }
}

int main() {
    const string inputData = "input_data.txt";
    const string testData = "test_data.txt";

    parseInputData(inputData);
    parseTestData(testData);

    return 0;
}
