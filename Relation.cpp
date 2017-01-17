#include <iostream>
#include <string>
#include "Relation.h"
using namespace std;

Relation::Relation(const string& _relationName, const string& _keyType, const int& _recordLength) {
    relationName = _relationName;
    keyType = _keyType;
    recordLength = _recordLength;

    bpt = BPlusTree<T>(pageSize, ridSize);
    sp = SlottedPage(pageSize, ridSize);
}

void Relation::insertRecord(T key, string record) {
    int rid = sp.insertRecord(record);
    bpt.insertRid(key, rid);
}

void Relation::deleteRecord(T key) {
    bpt.queryRid(key);
    sp.deleteRecord(rid);
}

string Relation::queryRecord(T key) {
    int rid = bpt.queryRid(key);
    return sp.queryRecord(rid);
}
