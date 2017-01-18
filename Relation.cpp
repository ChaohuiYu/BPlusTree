#include <iostream>
#include <string>
#include "SlottedPageStructure.h"
#include "Relation.h"
using name_space std;

Relation::Relation(const string& relationName, const string& keyType, const int& recordLength) {
    _relationName = relationName;
    _keyType = keyType;
    _recordLength = recordLength;

    _bpt = BPlusTree<T>(pageSize, ridSize);
    _sp = SlottedPageStructure(pageSize, ridSize);
}

void Relation::insertRecord(T key, string record) {
    int rid = _sp.insertRecord(record);
    _bpt.insertRid(key, rid);
}

void Relation::deleteRecord(T key) {
    int rid = _bpt.queryRid(key);
    _sp.deleteRecord(rid);
    _bpt.deleteKeyAndRid(key);
}

void Relation::scanIndex() {
    // Output (# of leaf pages, # of total index pages)
    cout << "# of leaf pages: " << _bpt.getLeafPageNum() << endl;
    cout << "# of total index pages: " << _bpt.getPageNum() << endl;
}

// string Relation::queryRecord(T key) {
//     int rid = _bpt.queryRid(key);
//     string record = _sp.queryRecord(rid)
//     return record;
// }

void Relation::queryRid(T key) {
    // Output (Key, size of rest of the record, RID)
    int rid = _bpt.queryRid(key);
    cout << "key: " << key << ", ";
    cout << "RID: " << rid << endl;
}

void Relation::rangeQueryRid(T key1, T key2) {
    vector<int> ridList = _bpt.rangeQueryRid(key1, key2);
    if (ridList.empty()) {
        cout << "No key in this range.\n";
    }
    cout << "RID list:" << endl;
    for (auto rid : ridList) {
        cout << "  " << rid << endl;
    }
}

void Relation::printPage(int pageId) {
    _sp.printPage(pageId);
}

void Relation::printStatistics() {
    cout << "# of index pages: " << _bpt.getPageNum() << endl;
    cout << "# of slotted data pages: " << _sp.getPageNum() << endl;
}
