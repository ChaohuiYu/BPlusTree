#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "SlottedPage.h"
using namespace std;

// Public Function

SlottedPage::SlottedPage(string name, string _keyType, int recLen) {
    // pageSize = 512;

    relationName = name;
    keyType = _keyType;

    recordSize = recLen;

    // calculate slotNum. ignore book keeping here
    int pointerSize = 2; // free space pointer
    int slotNumSize = 2; // storing the number of filled slots
    int offsetSize = 2; // storing the offset of a slot
    int recLenSize = 2; // storing the length of a slot
    slotNum = (pageSize - pointerSize - slotNumSize) / (recLen + offsetSize + recLenSize);
}

void SlottedPage::print() {
    cout << "relationName: " << relationName << endl;
    cout << "recordSize: " << relationName << endl;
    cout << "slotNum: " << slotNum << endl;
    cout << "keyType: " << keyType << endl;
    cout << "key2record: \n";
    for (auto it = key2record.cbegin(); it != key2record.cend(); ++it) {
        cout << "    ";
        cout << it->first << " " << it->second << "\n";
    }
    // cout << "RIDtable: \n";
    // for (auto it = RIDtable.cbegin(); it != RIDtable.cend(); ++it) {
    //     cout << "    ";
    //     cout << it->first << " " << it->second << "\n";
    // }
    cout << "key2RID: \n";
    for (auto it = key2RID.cbegin(); it != key2RID.cend(); ++it) {
        cout << "    ";
        cout << it->first << " " << it->second << "\n";
    }

    cout << "RID to record:\n";
    for (auto it = key2record.cbegin(); it != key2record.cend(); ++it) {
        cout << "    ";
        cout << key2RID[it->first] << " " << it->second << "\n";
    }
}

void SlottedPage::insert(int key, string record) {
    if(updatedRID % slotNum != 0 || updatedRID == 0) {//要配出去的RID是中間值或0，直接分配
        key2record.insert(pair<int, string>(key, record));
        key2RID.insert(pair<int, int>(key, updatedRID));
		RIDtable.insert(pair<int, bool>(updatedRID , true));
        updatedRID ++; //增加RID時要做處理
    }
    else if(updatedRID % slotNum == 0) { //要配出去的RID是page的開頭
        // cout << "hasDeletedRecord: " << hasDeletedRecord() << endl;
        if(!hasDeletedRecord()) { //前面都填滿的狀況
            key2record.insert(pair<int, string>(key, record));
            key2RID.insert(pair<int, int>(key, updatedRID));
            RIDtable.insert(pair<int, bool>(updatedRID , true));
            updatedRID++;
        }
        else { //前面未填滿的狀況
            if(currentRID == updatedRID) { //已掃完的狀況->再掃
                currentRID = 0;
                currentRID = getnextRID(currentRID);
                key2record.insert(pair<int, string>(key, record));
                key2RID.insert(pair<int, int>(key, currentRID));
                RIDtable[currentRID] = true;
                // RIDtable.insert(pair<int, bool>(currentRID , true));
            }
            else { //繼續掃完
                currentRID = getnextRID(currentRID);
                key2record.insert(pair<int, string>(key, record));
                key2RID.insert(pair<int, int>(key, currentRID));
                RIDtable[currentRID] = true;
                // RIDtable.insert(pair<int, bool>(currentRID , true));
                if(getnextRID(currentRID) == updatedRID){
                    currentRID = updatedRID;
                }
            }
        }
    }
    // cout << "currentRID: " << currentRID << endl;
    // cout << "updatedRID: " << updatedRID << endl;
    // cout << endl;
}

void SlottedPage::deleteRecord(int key){
    auto iter1 = key2record.find(key);
    // Error handling
    if (iter1 == key2record.end()) {
        cout << "Can not Find this record" << endl;
        return;
    }

    //map當中要刪掉
    key2record.erase(iter1);

    auto iter2 = key2RID.find(key);
    key2RID.erase(iter2);

    //更新RIDtable
    RIDtable[iter2->second]= false;//[to be corrected]不是用key查，先把key對出，再用RID查
}

int SlottedPage::getnextRID(int RID){
    auto iter = RIDtable.find(RID);
    if (RID == 0 && iter->second == false) {
        return RID;
    }
    else {
        while(iter->second == true){
            if(iter->first == (updatedRID-1)){//到底了都還是true，則return updatedRID
                return updatedRID;
            }
            iter++;
        }
        return iter->first; //從while迴圈出來，iter->second應是false了
    }
}

int SlottedPage::getRealRID(int key) {
    auto iter = key2RID.find(key);
    if (iter == key2RID.end())
        return -1;
    return iter->second;
}

int SlottedPage::RIDToRealRID(int RID) {
    int pageId = RID / slotNum;
    int slotId = RID % slotNum;
    int realRID = (pageId << 16) + slotId;
    return realRID;
}

int SlottedPage::RIDToPageId(int RID) {
    return RID / slotNum;
}

int SlottedPage::RIDToSlotId(int RID) {
    return RID % slotNum;
}

//
// void Relation::delete (int key)
// {
//
//     // Error handling
//     iter3 = key2record.find(key);
//     if (iter3 == key2record.end()) {
//         cout << "Do not Find this record" << endl;
//         return;
//     }
//
//     //map當中要刪掉
//
//     iter1 = key2record.find(key);
//     map2record.erase(iter1);
//     iter2 = key2RID.find(key);
//     key2RID.erase(iter2);
//
//     //更新RIDtable
//     RIDtable[key] = false;
// }
//
bool SlottedPage::hasDeletedRecord() {
    // if there are no record deleted, return true
    for (auto iter = RIDtable.begin(); iter != RIDtable.end(); iter++) {
        if (iter->second == false) {
            return true; //這個for loop會不會漏掉iter == RIDtable.end()，且iter->second == false的狀況？
        }
    }
    return false;
}
