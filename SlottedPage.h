#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <map>
#include <vector>
using namespace std;

class SlottedPage {
    public:
        SlottedPage(string name, string _keyType, int reclen);
        void insert(int key, string record);   //回傳RID
        void deleteRecord(int key);   //回傳Delete 那筆record 的RID
        bool hasDeletedRecord();  //check RIDtable中前面的值是否都填滿
        int getnextRID(int RID);
        void print();

    private:
        const int pageSize = 512;
        int slotNum; // slot number per page
        int pageID_base;
        map<int, string> key2record;
        map<int, int> key2RID;
        map<int, bool> RIDtable;
        int currentRID = 0;   //掃把指標
        int updatedRID = 0;   //指到目前未被分配出去的最小RID值，如已分配完0~4頁，則updatedRID值為500
        string relationName;
        string keyType;
};
