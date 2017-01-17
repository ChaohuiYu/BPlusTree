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
        void print();
        int getRealRID(int key);

    private:
        const int pageSize = 512;
        string relationName;
        string keyType;
        int recordSize;
        int slotNum; // slot number per page
        map<int, string> key2record;
        map<int, int> key2RID;
        map<int, bool> RIDtable;
        int currentRID = 0;   //掃把指標
        int updatedRID = 0;   //指到目前未被分配出去的最小RID值，如已分配完0~4頁，則updatedRID值為500

        int getnextRID(int RID);
        int RIDToRealRID(int RID);
        int RIDToPageId(int RID);
        int RIDToSlotId(int RID);
};
