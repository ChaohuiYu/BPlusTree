#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "commands.h"
using namespace std;

// #define DEBUG

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

std::vector<std::string> splitStr(std::string s, const std::string& delimiter) {
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

void parseCommands(const std::string& filename) {
    ifstream infile(filename);
    string line, command, relationName, keyType, index, record, index1, index2, pageId;
    int recordLength = 0;
    std::vector<std::string> commandVector, commandVectorSections;

    while(getline(infile, line)) {
        stringstream lineStream(line);

        // parse the first token as action
        if (!getline(lineStream, command, ' ')) {
            // D(cerr << "invalid command: empty\n");
            continue;
        }

        // call different functions depending on command
        if (command == "R,") {
            commandVector = splitStr(line, ", ");
            if (commandVector.size() != 4) {
                cout << "Error: invalid command: " << line << endl;
                cout << "    R command example: R, Chat, integer, 90\n";
                cout << "    R command example: R, Movie, String, 100\n";
                continue;
            }

            try {
                recordLength = std::stoi(commandVector[3]);
            }
            catch (const std::exception& e) {
                cout << "Error: invalid command: " << line << endl;
                cout << "    record length should be an integer\n";
                continue;
            }
            relationName = commandVector[1];
            keyType = commandVector[2];

            createRelation(relationName, keyType, recordLength);
        }
        else if (command == "I,") {
            commandVectorSections = splitStr(line, "; ");

            if (commandVectorSections.size() == 0) {
                cout << "Error: invalid command: " << line << endl;
                cout << "    I command example: I, Movie, \"nkpgrtxphreddb\", \"xnrmnw osiy\"\n";
                continue;
            }

            // handle the first command
            commandVector = splitStr(commandVectorSections[0], ", ");
            if (commandVector.size() != 4) {
                cout << "Error: invalid command: " << line << endl;
                cout << "    I command example: I, Movie, \"nkpgrtxphred\", \"xnrmnw osiy\"\n";
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
                    cout << "Error: invalid command: " << line << endl;
                    cout << "    I command example: I, Movie, \"nkpgrtxphred\", \"xnrmnw osiy\"; \"nsildfwefoi\", \"dsdisf sdif3fwe9\"\n";
                    // cout << "Error: invalid command: commandVector.size() != 2 in: " << line << endl;
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
                cout << "Error: invalid command: " << line << endl;
                cout << "    D command example: D, Chat, 282\n";
                continue;
            }

            relationName = commandVector[1];
            index = commandVector[2];
            deleteRecord(relationName, index);
        }
        else if (command == "Scan") {
            commandVector = splitStr(line, " ");
            if (commandVector.size() != 2) {
                cout << "Error: invalid command: " << line << endl;
                cout << "    Scan command example: Scan Chat\n";
                continue;
            }

            relationName = commandVector[1];
            scanRelation(relationName);
        }
        else if (command == "q") {
            commandVector = splitStr(line, " ");
            if (commandVector.size() < 3 or commandVector.size() > 4) {
                cout << "Error: invalid command: " << line << endl;
                cout << "    q command example: q Chat 81\n";
                cout << "    q command example: q Chat 81 123\n";
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
                cout << "Error: invalid command: " << line << endl;
                cout << "    p command example: p Chat 1\n";
                continue;
            }
            relationName = commandVector[1];
            pageId = commandVector[2];
            displayPage(relationName, pageId);
        }
        else if (command == "c") {
            commandVector = splitStr(line, " ");
            if (commandVector.size() != 2) {
                cout << "Error: invalid command: " << line << endl;
                cout << "    c command example: c Chat\n";
                continue;
            }

            relationName = commandVector[1];
            statisticsRelation(relationName);
        }
        else {
            cout << "Error: invalid command: " << line << endl;
        }
    }
}
