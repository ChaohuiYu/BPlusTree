#include <iostream>
#include <string>
#include "BPlusTree.h"
#include "SlottedPageStructure.h"
#include "Relation.h"
using namespace std;

template <class T>
Relation<T>::Relation(const string& relationName, const string& keyType, int recordLength)
    : _bpt(62), _sp(recordLength)
{
    _relationName = relationName;
    _keyType = keyType;
    _recordLength = recordLength;

    // initialize BPlusTree
    // calculate the key num per node in B+ tree
    int bptKeySize;
    if (_keyType == "string" || _keyType == "String" || _keyType == "str") {
        bptKeySize = 10;
    }
    else {
        bptKeySize = 4;
    }
    int bptMaxKeyNum = (_pageSize - 12) / (bptKeySize + 4);
    _bpt = BPlusTree<T>(bptMaxKeyNum);

    // initialize SlottedPageStructure
    // _sp = SlottedPageStructure(recordLength);
}

template <class T>
void Relation<T>::insertRecord(T key, string record) {
    cout << "Insert into relation " << _relationName << " with key " << key << " and record " << record << ":\n";
    int rid = _sp.insertRecord(record);
    _bpt.insertValue(key, rid);
    cout << "    Record inserted.\n";
}

template <class T>
void Relation<T>::deleteRecord(T key) {
    cout << "Delete record in relation " << _relationName << " by key " << key << ":\n";
    if (!_bpt.checkKeyExist(key)) {
        cout << "    Key doesn't exist.\n";
    }
    else {
        int rid = _bpt.queryValue(key);
        _sp.deleteRecord(rid);
        _bpt.deleteValue(key);
        cout << "    Record deleted.\n";
    }
}

template <class T>
void Relation<T>::scanIndex() {
    // Output (# of leaf pages, # of total index pages)
    cout << "Scan index pages of relation " << _relationName << ":\n";
    cout << "    # of leaf pages: " << _bpt.getLeafPageNum() << endl;
    cout << "    # of total index pages: " << _bpt.getPageNum() << endl;
}

// string Relation<T>::queryRecord(T key) {
//     int rid = _bpt.queryValue(key);
//     string record = _sp.queryRecord(rid)
//     return record;
// }

template <class T>
void Relation<T>::queryRid(T key) {
    // Output (Key, size of rest of the record, RID)
    cout << "Query relation " << _relationName << " with key " << key << ":" << endl;
    if (!_bpt.checkKeyExist(key)) {
        cout << "    Key doesn't exist.\n";
    }
    else {
        cout << "    RID: " << _bpt.queryValue(key) << endl;
    }
}

template <class T>
void Relation<T>::rangeQueryRid(T key1, T key2) {
    cout << "Range query relation " << _relationName << " between " << key1 << " and " << key2 << ":\n";
    vector<int> ridList = _bpt.rangeQueryValue(key1, key2);
    if (ridList.empty()) {
        cout << "    No key in this range.\n";
    }
    cout << "    RID list:" << endl;
    for (auto rid : ridList) {
        cout << "    " << rid << endl;
    }
}

template <class T>
void Relation<T>::printPage(int pageId) {
    _sp.printPage(pageId);
}

template <class T>
void Relation<T>::printStatistics() {
    cout << "Statistics of relation " << _relationName << ":\n";
    cout << "    # of index pages: " << _bpt.getPageNum() << endl;
    cout << "    # of slotted data pages: " << _sp.getPageNum() << endl;
}

template class Relation<int>;
template class Relation<string>;
