#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <ctime>
using namespace std;

// #define DEBUG

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

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

std::vector<std::string> splitStr(std::string s, const std::string & delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

void parseCommands(const string& filename) {
    ifstream infile(filename);
    string line, command, relationName, keyType, index, record, index1, index2, pageId;
    int recordLength = 0;
    std::vector<std::string> commandVector, commandVectorSections;

    while(getline(infile, line)) {
        stringstream lineStream(line);

        // parse the first token as action
        if (!getline(lineStream, command, ' ')) {
            D(cerr << "invalid command: empty\n");
            continue;
        }

        // call different functions depending on command
        if (command == "R,") {
            commandVector = splitStr(line, ", ");
            if (commandVector.size() != 4) {
                D(cerr << "invalid command: " << "commandVector.size() != 4 in: " << line << endl);
                continue;
            }

            try {
                recordLength = std::stoi(commandVector[3]);
            }
            catch (const std::exception& e) {
                D(cerr << "invalid command: " << "recordLength not integer in: " << line << endl);
                continue;
            }
            relationName = commandVector[1];
            keyType = commandVector[2];

            createRelation(relationName, keyType, recordLength);
        }
        else if (command == "I,") {
            commandVectorSections = splitStr(line, "; ");

            if (commandVectorSections.size() == 0) {
                D(cerr << "invalid command: commandVectorSections.size() == 0 in: " << line << endl);
                continue;
            }

            // handle the first command
            commandVector = splitStr(commandVectorSections[0], ", ");
            if (commandVector.size() != 4) {
                D(cerr << "invalid command: commandVector.size() != 4 in: " << line << endl);
                continue;
            }
            relationName = commandVector[1];
            index = commandVector[2];
            record = commandVector[3];

            insertRecord(relationName, index, record);

            // handle the commands after ;
            for (size_t i = 1; i < commandVectorSections.size(); i++) {
                commandVector = splitStr(commandVectorSections[i], ", ");
                if (commandVector.size() != 2) {
                    D(cerr << "invalid command: commandVector.size() != 2 in: " << line << endl);
                    continue;
                }
                index = commandVector[0];
                record = commandVector[1];
                insertRecord(relationName, index, record);
            }
        }
        else if (command == "D,") {
            commandVector = splitStr(line, ", ");
            if (commandVector.size() != 3) {
                D(cerr << "invalid command: commandVector.size() != 3 in: " << line << endl);
                continue;
            }

            relationName = commandVector[1];
            index = commandVector[2];
            deleteRecord(relationName, index);
        }
        else if (command == "Scan") {
            commandVector = splitStr(line, " ");
            if (commandVector.size() != 2) {
                D(cerr << "invalid command: commandVector.size() != 2 in: " << line << endl);
                continue;
            }

            relationName = commandVector[1];
            scanRelation(relationName);
        }
        else if (command == "q") {
            commandVector = splitStr(line, " ");
            if (commandVector.size() < 3 or commandVector.size() > 4) {
                D(cerr << "invalid command: commandVector.size() not 3 or 4 in: " << line << endl);
                continue;
            }

            if (commandVector.size() == 3) {
                relationName = commandVector[1];
                index = commandVector[2];
                queryRecord(relationName, index);
            }
            if (commandVector.size() == 4) {
                relationName = commandVector[1];
                index1 = commandVector[2];
                index2 = commandVector[3];
                rangeQueryRecords(relationName, index1, index2);
            }
        }
        else if (command == "p") {
            commandVector = splitStr(line, " ");
            if (commandVector.size() != 3) {
                D(cerr << "invalid command: commandVector.size() != 3 in: " << line << endl);
                continue;
            }
            relationName = commandVector[1];
            pageId = commandVector[2];
            displayPage(relationName, pageId);
        }
        else if (command == "c") {
            commandVector = splitStr(line, " ");
            if (commandVector.size() != 2) {
                D(cerr << "invalid command: commandVector.size() != 2 in: " << line << endl);
                continue;
            }

            relationName = commandVector[1];
            statisticsRelation(relationName);
        }
        else {
            D(cerr << "invalid command: " << line << endl);
        }
    }
}

int main() {
    const string inputData = "input_data.txt";
    const string testData = "DBMS_ProjectB_Data/ProjectB_data.txt";

    // parseInputData(inputData);
    // parseTestData(testData);

    parseCommands(testData);

    return 0;
}
