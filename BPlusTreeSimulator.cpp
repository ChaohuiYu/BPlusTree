#include <iostream>
#include <string>
#include <map>
#include "BPlusTreeSimulator.h"
using namespace std;

template <class T>
BPlusTreeSimulator<T>::BPlusTreeSimulator() {
    key2rid = map<T, int>();
}

template <class T>
void BPlusTreeSimulator<T>::insertRid(T key, int rid) {
    if (keyExists(key)) {
        cout << "error: key " << key << " already exists.\n";
        return;
    }
    key2rid[key] = rid;
}

template <class T>
void BPlusTreeSimulator<T>::deleteRid(T key) {
    if (!keyExists(key)) {
        cout << "error: key " << key << " doesn't exist.\n";
        return;
    }
    key2rid.erase(key);
}

template <class T>
int BPlusTreeSimulator<T>::queryRid(T key) {
    if (!keyExists(key)) {
        cout << "error: key " << key << " doesn't exist.\n";
        return -1;
    }
    return key2rid[key];
}

template <class T>
int BPlusTreeSimulator<T>::getLeafPageNum() {
    return 10;
}

template <class T>
int BPlusTreeSimulator<T>::getNonLeafPageNum() {
    return 5;
}

template <class T>
int BPlusTreeSimulator<T>::getPageNum() {
    return 15;
}

template <class T>
bool BPlusTreeSimulator<T>::keyExists(T key) {
    return key2rid.find(key) != key2rid.end();
}

template <class T>
void BPlusTreeSimulator<T>::print() {
    for (auto& iter : key2rid) {
        cout << iter.first << " " << iter.second << endl;
    }
}

template class BPlusTreeSimulator<int>;
template class BPlusTreeSimulator<string>;
