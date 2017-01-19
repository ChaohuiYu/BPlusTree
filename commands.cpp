#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include "commands.h"
#include "Relation.h"
using namespace std;

map<string, Relation<int>*> relationNameToRelationInt;
map<string, Relation<string>*> relationNameToRelationStr;

// R, Chat, integer, 90
// R, Movie, String, 100
void createRelation(const string& relationName, const string& keyType, int recordLength) {
    cout << "Try to create relation \"" << relationName << "\":\n";

    // check if relationName exists
    if (isRelationExist(relationName)) {
        cout << "    Error: Relation " << relationName << " already exists.\n";
        return;
    }

    // check if keyType is integer or string
    if (!(keyType == "integer" || keyType == "Integer" || keyType == "int"
    || keyType == "string" || keyType == "String" || keyType == "str")) {
        cout << "    Error: Key type \"" << keyType << "\" is invalid.\n";
        return;
    }

    // check if recordLength <= 500
    if (recordLength > 500) {
        cout << "    Error: Record length > 500\n";
        return;
    }

    if (keyType == "integer" || keyType == "Integer" || keyType == "int") {
        auto relationPtr = new Relation<int>(relationName, "integer", recordLength);
        relationNameToRelationInt[relationName] = relationPtr;
    }
    else if (keyType == "string" || keyType == "String" || keyType == "str") {
        auto relationPtr = new Relation<string>(relationName, "string", recordLength);
        relationNameToRelationStr[relationName] = relationPtr;
    }
}

// I, Chat, 416, "Hello world!"
// I, Movie, "nkpgrtgadybxphreddb", "xnrmnw osiyjc spidi"
// convert key to int if the relation use int key
// quotation mark (") should have been removed
void insertRecord(const string& relationName, const string& key, const string& record) {
    // need to check if key should be integer
    // need to check if key exists

    if (!isRelationExist(relationName)) {
        cout << "Error: Relation " << relationName << " doesn't exist.\n";
        return;
    }

    if (isRelationInRelationInt(relationName)) {
        if (!is_number(key)) {
            cout << "Error: Key " << key << " is not a number.\n";
            return;
        }
        relationNameToRelationInt[relationName]->insertRecord(stoi(key), record);
    }
    else if (isRelationInRelationStr(relationName)) {
        relationNameToRelationStr[relationName]->insertRecord(key.substr(1, 10), record);
    }
}

// D, Chat, 140
// D, Movie, "skbeefznqbhky"
void deleteRecord(const string& relationName, const string& key) {
    // need to check if key should be integer
    // need to check if key exists

    if (!isRelationExist(relationName)) {
        cout << "Error: Relation " << relationName << " doesn't exist.\n";
        return;
    }

    if (isRelationInRelationInt(relationName)) {
        if (!is_number(key)) {
            cout << "Error: Key " << key << " is not a number.\n";
            return;
        }
        relationNameToRelationInt[relationName]->deleteRecord(stoi(key));
    }
    else if (isRelationInRelationStr(relationName)) {
        relationNameToRelationStr[relationName]->deleteRecord(key.substr(1, 10));
    }
}

// Scan Chat
void scanRelation(const string& relationName) {
    if (!isRelationExist(relationName)) {
        cout << "Error: Relation " << relationName << " doesn't exist.\n";
        return;
    }

    if (isRelationInRelationInt(relationName)) {
        relationNameToRelationInt[relationName]->scanIndex();
    }
    else if (isRelationInRelationStr(relationName)) {
        relationNameToRelationStr[relationName]->scanIndex();
    }
}

// q Chat 81
// q Movie "fhhhoujqvdxejh"
void queryRecord(const string& relationName, const string& key) {
    if (!isRelationExist(relationName)) {
        cout << "Error: Relation " << relationName << " doesn't exist.\n";
        return;
    }

    if (isRelationInRelationInt(relationName)) {
        if (!is_number(key)) {
            cout << "Error: Key " << key << " is not a number.\n";
            return;
        }
        relationNameToRelationInt[relationName]->queryRid(stoi(key));
    }
    else if (isRelationInRelationStr(relationName)) {
        relationNameToRelationStr[relationName]->queryRid(key.substr(1, 10));
    }
}

// q Chat 170 296
// q Movie "owjafbcada" "xzrlijkeuufoyxj"
void rangeQueryRecords(const string& relationName, const string& key1, const string& key2) {
    if (!isRelationExist(relationName)) {
        cout << "Error: Relation " << relationName << " doesn't exist.\n";
        return;
    }

    if (isRelationInRelationInt(relationName)) {
        if (!is_number(key1)) {
            cout << "Error: Key1 " << key1 << " is not a number.\n";
            return;
        }
        if (!is_number(key2)) {
            cout << "Error: Key2 " << key2 << " is not a number.\n";
            return;
        }
        relationNameToRelationInt[relationName]->rangeQueryRid(stoi(key1), stoi(key2));
    }
    else if (isRelationInRelationStr(relationName)) {
        relationNameToRelationStr[relationName]->rangeQueryRid(key1.substr(1, 10), key2.substr(1, 10));
    }
}

// p relation-name page-id
void displayPage(const string& relationName, const string& pageId) {
    if (!isRelationExist(relationName)) {
        cout << "Error: Relation " << relationName << " doesn't exist.\n";
        return;
    }

    if (!is_number(pageId)) {
        cout << "Error: page id should be 0 or a positive integer\n";
        return;
    }

    int pageIdInt = stoi(pageId);

    if (pageIdInt < 0) {
        cout << "Error: page id should be 0 or a positive integer\n";
        return;
    }

    if (isRelationInRelationInt(relationName)) {
        relationNameToRelationInt[relationName]->printPage(pageIdInt);
    }
    else if (isRelationInRelationStr(relationName)) {
        relationNameToRelationStr[relationName]->printPage(pageIdInt);
    }
}

// c Chat
void statisticsRelation(const string& relationName) {
    if (!isRelationExist(relationName)) {
        cout << "Error: Relation " << relationName << " doesn't exist.\n";
        return;
    }

    if (isRelationInRelationInt(relationName)) {
        relationNameToRelationInt[relationName]->printStatistics();
    }
    else if (isRelationInRelationStr(relationName)) {
        relationNameToRelationStr[relationName]->printStatistics();
    }
}

bool isRelationExist(const string& relationName) {
    return isRelationInRelationInt(relationName) || isRelationInRelationStr(relationName);
}

bool isRelationInRelationInt(const string& relationName) {
    return relationNameToRelationInt.find(relationName) != relationNameToRelationInt.end();
}

bool isRelationInRelationStr(const string& relationName) {
    return relationNameToRelationStr.find(relationName) != relationNameToRelationStr.end();
}

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
