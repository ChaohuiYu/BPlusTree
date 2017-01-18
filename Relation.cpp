#include <iostream>
#include <string>
#include "BPlusTreeSimulator.h"
#include "SlottedPageStructure.h"
#include "Relation.h"
using namespace std;

template <class T>
Relation<T>::Relation(const string& relationName, const string& keyType, int recordLength)
    : _bpt(), _sp(recordLength)
{
    _relationName = relationName;
    _keyType = keyType;
    _recordLength = recordLength;

    // _bpt = BPlusTreeSimulator<T>(); // pageSize, ridSize
    // _sp = SlottedPageStructure(recordLength);
}

template <class T>
void Relation<T>::insertRecord(T key, string record) {
    int rid = _sp.insertRecord(record);
    _bpt.insertRid(key, rid);
}

template <class T>
void Relation<T>::deleteRecord(T key) {
    int rid = _bpt.queryRid(key);
    _sp.deleteRecord(rid);
    _bpt.deleteRid(key);
}

template <class T>
void Relation<T>::scanIndex() {
    // Output (# of leaf pages, # of total index pages)
    cout << "# of leaf pages: " << _bpt.getLeafPageNum() << endl;
    cout << "# of total index pages: " << _bpt.getPageNum() << endl;
}

// string Relation<T>::queryRecord(T key) {
//     int rid = _bpt.queryRid(key);
//     string record = _sp.queryRecord(rid)
//     return record;
// }

template <class T>
void Relation<T>::queryRid(T key) {
    // Output (Key, size of rest of the record, RID)
    int rid = _bpt.queryRid(key);
    cout << "key: " << key << ", ";
    cout << "RID: " << rid << endl;
}

// template <class T>
// void Relation<T>::rangeQueryRid(T key1, T key2) {
//     vector<int> ridList = _bpt.rangeQueryRid(key1, key2);
//     if (ridList.empty()) {
//         cout << "No key in this range.\n";
//     }
//     cout << "RID list:" << endl;
//     for (auto rid : ridList) {
//         cout << "  " << rid << endl;
//     }
// }

template <class T>
void Relation<T>::printPage(int pageId) {
    _sp.printPage(pageId);
}

template <class T>
void Relation<T>::printStatistics() {
    cout << "# of index pages: " << _bpt.getPageNum() << endl;
    cout << "# of slotted data pages: " << _sp.getPageNum() << endl;
}

template class Relation<int>;
template class Relation<string>;
