#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "SlottedPage.h"
using namespace std;

SlottedPage::SlottedPage(string name, string _keyType, int recLen) {
    // pageSize = 512;
    //計算slotNum，算法暫定 neglect book keeping
    // slot directory spaces
    int fspSize = 2; // free space pointer
    int slotNumSize = 2;
    int offsetAndRecLenSize = 4;
    slotNum = (pageSize - fspSize - slotNumSize) / (recLen + offsetAndRecLenSize);
    //
    // //計算slotNum為幾位數字
    // int count = 1;
    // while (slotNum >= 10) {
    //     count++;
    //     slotNum = slotNum / 10;
    // }
    // pageID_base = pow(10, count);
    pageID_base = slotNum;

        //initialize name
    relationName = name;
    keyType = _keyType;

    cout << "slotNum: " << slotNum << endl;
}

void SlottedPage::print() {
    cout << "relationName: " << relationName << endl;
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
    if(updatedRID % pageID_base != 0 || updatedRID == 0) {//要配出去的RID是中間值或0，直接分配
        key2record.insert(pair<int, string>(key, record));
        key2RID.insert(pair<int, int>(key, updatedRID));
		RIDtable.insert(pair<int, bool>(updatedRID , true));
        updatedRID ++; //增加RID時要做處理
    }
    else if(updatedRID % pageID_base == 0) { //要配出去的RID是page的開頭
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
// //
// int SlottedPage::getnextRID(int RID) {
//
// }
// //
// void SlottedPage::insert(int key, string record)
// {
//     if (updatedRID % pageID_base != 0 || updatedRID == 0) { //要配出去的RID是中間值或0，直接分配
//         key2record.insert(pair<int, string>(key, record));
//         key2RID.insert(pair<int, int>(key, updatedRID));
//         RIDtable.insert(pair<int, bool>(updatedRID, true));
//         updatedRID++; //增加RID時要做處理
//     }
//     else if (updatedRID % pageID_base == 0) { //要配出去的RID是page的開頭
//         if (checkFun()) { //前面都填滿的狀況
//             key2record.insert(pair<int, string>(key, record));
//             key2RID.insert(pair<int, int>(key, updatedRID));
//             RIDtable.insert(pair<int, bool>(updatedRID, true));
//             updatedRID++;
//         }
//         else { //前面未填滿的狀況
//             if (currentRID == updatedRID) { //已掃完的狀況->再掃
//                 currentRID = 0;
//                 currentRID = getnextRID(currentRID);
//                 key2record.insert(pair<int, string>(key, record));
//                 key2RID.insert(pair<int, int>(key, currentRID));
//                 RIDtable.insert(pair<int, bool>(currentRID, true));
//             }
//             else { //繼續掃完
//                 currentRID = getnextRID(currentRID);
//                 key2record.insert(pair<int, string>(key, record));
//                 key2RID.insert(pair<int, int>(key, currentRID));
//                 RIDtable.insert(pair<int, bool>(currentRID, true));
//                 if (getnextRID(currentRID) == updatedRID) {
//                     currentRID = updatedRID;
//                 }
//             }
//         }
//     }
// }


// void main()
// {
//     /*
// //slotNum為單一page中slot個數
//  int count=1;
//  cout<<"輸入數字";
//  int slotNum;
//  cin >>slotNum;
//
//  //計算slotNum為幾位數字
//  while(slotNum>=10)
//  {
//   count++;
//   slotNum=slotNum/10;
//  }
//  //cout<<"位數"<<count<<endl;
//
// pageID_base = pow(10,count)
//  //RID = page_id*pageID_base + slot_id
// int currenRID = 0;
// */
//     if (function為I) {
//         //check currentRID是否為page的頭
//         if (currentRID % pageID_base == 0) {
//             //若是頭，則pop vector的內容，currentRID不增加
//             //若vector不是空的，則pop出vector的內容
//             if (vetor不為empty) {
//                 tempRID = pop vector;
//                 insert(key, record) to record_map;
//                 insert(key, tempRID) to RID_map;
//             }
//             else { //vector is empty
//                 insert(key, record) to record_map;
//                 insert(key, currentRID) to RID_map;
//                 increaseRID(); //RID的增加法寫成function
//             }
//         }
//         else {
//             //否則直接給currentRID
//             insert(key, record) to record_map;
//             insert(key, currentRID) to RID_map;
//             increaseRID(); //RID的增加法寫成function
//         }
//     }
//
//     if (function為D) {
//         //push到vector中，並對vector作sort
//         push vector;
//         sort vector
//     }
//
//     system("pause");
// }
