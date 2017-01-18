#include <iostream>
#include <string>
#include "BPlusTreeSimulator.h"
#include "SlottedPageStructure.h"
using namespace std;

/*
Notes:
1. the 'T' (key type) is determined outside.
    so the "keyType" data memter won't do anything here.
2. BPlusTree handle key -> rid. It should know nothing about record.
3. SlottedPage handle rid <-> record. It should know nothing about key.
*/

#ifndef RELATION_H
#define RELATION_H

template <class T>
class Relation{
    public:
        Relation(const string& relationName, const string& keyType, int recordLength);
        void insertRecord(T key, string record);
        void deleteRecord(T key);
        void scanIndex();  // scan b+ tree
        void queryRid(T key);
        // void rangeQueryRid(T key1, T key2);
        void printPage(int pageId);
        void printStatistics();

    private:
        const int _pageSize = 512;
        const int _ridSize = 4;
        string _relationName;
        string _keyType;
        int _recordLength;
        BPlusTreeSimulator<T> _bpt;
        SlottedPageStructure _sp;
};

#endif
