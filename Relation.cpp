#include <iostream>
#include <string>
#include "Relation.h"
using namespace std;

Relation::Relation(const string& _relationName, const string& _keyType, const int& _recordLength) {
    relationName = _relationName;
    keyType = _keyType;
    recordLength = _recordLength;

    bpt = BPlusTree<T>(pageSize, ridSize);
    sp = SlottedPageStructure(pageSize, ridSize);
}

void Relation::insertRecord(T key, string record) {
    int rid = sp.insertRecord(record);
    bpt.insertRid(key, rid);
}

void Relation::deleteRecord(T key) {
    int rid = bpt.queryRid(key);
    sp.deleteRecord(rid);
    bpt.deleteKeyAndRid(key);
}

// string Relation::queryRecord(T key) {
//     int rid = bpt.queryRid(key);
//     string record = sp.queryRecord(rid)
//     return record;
// }

int queryRid(T key) {
    int rid = bpt.queryRid(key);
    return rid;
}

vector<int> rangeQueryRid(T key1, T key2) {
    vector<int> ridList = bpt.rangeQueryRid(key1, key2);
    return ridList;
}
