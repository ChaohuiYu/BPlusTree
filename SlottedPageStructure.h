#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class SlottedPageStructure {
    public:
        SlottedPageStructure(int recordLength);
        int insertRecord(string record);
        void deleteRecord(int rid);
        string queryRecord(int rid);
        void print();

    private:
        const int _pageSize = 512;
        const int _pageIdSize = 2;
        const int _slotIdSize = 2;
        const int _ridSize = _pageIdSize + _slotIdSize;
        const int _pointerSize = 2; // space for free space pointer
        const int _slotNumSize = 2; // space for storing the number of filled slots
        const int _offsetSize = 2; // space for storing the offset of a slot
        const int _recLenSize = 2; // space for storing the length of a slot
        int _recordLength;
        int _slotNum;
        // int _lastFreeSpaceId;
        // int _middleFreeSpaceId;
        vector<string> _records; // spaceId to record
        vector<bool> _recordsExist;
        vector<int> _freeSpaces;

        int insertRecordAtEnd(const string& record);
        int insertRecordAtMiddle(const string& record);
        int spaceId2rid(int spaceId);
        int spaceId2pageId(int spaceId);
        int spaceId2slotId(int spaceId);
        int rid2spaceId(int rid);
        int rid2pageId(int rid);
        int rid2slotId(int rid);
        bool isCurrentPageFull();
        bool hasFreeSpaceInMiddle();
};
