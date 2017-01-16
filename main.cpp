#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <ctime>
#include "parser.h"
using namespace std;

int main() {
    const string inputData = "data/input_data.txt";
    const string testData = "data/ProjectB_data.txt";

    parseCommands(testData);

    return 0;
}
