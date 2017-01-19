#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "parser.h"
using namespace std;

int main() {
    const string inputData = "data/input_data.txt";

    parseCommands(inputData);

    return 0;
}
