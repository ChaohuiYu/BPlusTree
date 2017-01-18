#include <iostream>
#include <string>
using namespace std;

/*
Notes:
1. the 'T' (key type) is determined outside.
    so the "keyType" data memter won't do anything here.
2. BPlusTree handle key -> rid. It should know nothing about record.
3. SlottedPage handle rid <-> record. It should know nothing about key.
*/

template <class T>
class Relation {
    public:
        Relation(const string& _relationName, const string& _keyType, int _recordLength);
        void insertRecord(T key, string record);
        void deleteRecord(T key);
        int queryRid(T key);
        vector<int> rangeQueryRid(T key1, T key2);
        void displayPage(int pageId);

    private:
        const int pageSize = 512;
        const int ridSize = 4;
        string relationName;
        string keyType;
        int recordLength;
        BPlusTree<T> bpt;
        SlottedPageStructure sp;
};
