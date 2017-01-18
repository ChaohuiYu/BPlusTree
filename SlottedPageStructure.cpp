#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "SlottedPageStructure.h"
using namespace std;

SlottedPageStructure::SlottedPageStructure(int recordLength) {
    _recordLength = recordLength;
    _slotNum = (_pageSize - _pointerSize - _slotNumSize) / (recordLength + _offsetSize + _recLenSize);
}

int SlottedPageStructure::insertRecord(string record) {
    // return rid after the record is inserted
    int rid;

    // if the current page is not full
    // or there is no free space in the middle (no record deleted),
    // directly insert record in it
    if (!isCurrentPageFull() || !hasFreeSpaceInMiddle()) {
        rid = insertRecordAtEnd(record);
    }
    // if the current page is full
    // and there is any free space in the middle
    // insert record to the free space
    else {
        rid = insertRecordAtMiddle(record);
    }
    return rid;
}

void SlottedPageStructure::deleteRecord(int rid) {
    int spaceId = rid2spaceId(rid);
    if (spaceId >= _records.size()) {
        cerr << "error: in deleteRecord, spaceId out of range\n";
        return;
    }
    if (_recordsExist[spaceId] == false) {
        cerr << "error: in deleteRecord, record has been deleted\n";
        return;
    }
    _recordsExist[spaceId] = false;
    _freeSpaces.push_back(spaceId);
}

string SlottedPageStructure::queryRecord(int rid) {
    int spaceId = rid2spaceId(rid);
    if (spaceId >= _records.size()) {
        cerr << "error: in queryRecord, spaceId out of range\n";
        return "";
    }
    if (_recordsExist[spaceId] == false) {
        cerr << "error: in queryRecord, record has been deleted\n";
        return "";
    }
    return _records[spaceId];
}

void SlottedPageStructure::print() {
    cout << "slot num per page: " << _slotNum << endl;
    cout << "filled slot num: " << _records.size() - _freeSpaces.size() << endl;
    for (int spaceId = 0; spaceId < _records.size(); ++spaceId) {
        if (_recordsExist[spaceId]) {
            cout << "pageId: " << spaceId2pageId(spaceId);
            cout << ", slotId: " << spaceId2slotId(spaceId);
            // cout << ", rid: " << spaceId2rid(spaceId);
            cout << ", record: \"" << _records[spaceId] << "\"" << endl;
        }
    }
}

// Private Functions

int SlottedPageStructure::insertRecordAtEnd(const string& record) {
    int spaceId = _records.size();
    _records.push_back(record);
    _recordsExist.push_back(true);
    return spaceId2rid(spaceId);
}

int SlottedPageStructure::insertRecordAtMiddle(const string& record) {
    if (_freeSpaces.empty()) {
        cerr << "error: try to insertRecordAtMiddle but no free spaces\n";
        return -1;
    }
    std::sort(_freeSpaces.begin(), _freeSpaces.end(), std::greater<int>());
    int freeSpaceId = _freeSpaces.back();
    _records[freeSpaceId] = record;
    _recordsExist[freeSpaceId] = true;
    _freeSpaces.pop_back();
    return spaceId2rid(freeSpaceId);
}

int SlottedPageStructure::spaceId2rid(int spaceId) {
    return ((spaceId / _slotNum) << (_slotIdSize * 8)) + (spaceId % _slotNum);
}

int SlottedPageStructure::spaceId2pageId(int spaceId) {
    return (spaceId / _slotNum);
}

int SlottedPageStructure::spaceId2slotId(int spaceId) {
    return (spaceId % _slotNum);
}

int SlottedPageStructure::rid2spaceId(int rid) {
    return rid2pageId(rid) * _slotNum + rid2slotId(rid);
}

int SlottedPageStructure::rid2pageId(int rid) {
    return (rid >> (_slotIdSize * 8));
}

int SlottedPageStructure::rid2slotId(int rid) {
    return (rid % (1 << (_slotIdSize * 8)));
}

bool SlottedPageStructure::isCurrentPageFull() {
    int lastFreeSpaceId = _records.size();
    return (lastFreeSpaceId % _slotNum == 0) && (lastFreeSpaceId != 0);
}

bool SlottedPageStructure::hasFreeSpaceInMiddle() {
    return !_freeSpaces.empty();
}
