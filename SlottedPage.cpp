#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <SlottedPage.h>
using namespace std;

SlottedPage::SlottedPage(string name,string datatype,int reclen){

	//計算slot_num，算法暫定 neglect book keeping
	
	slot_num = (508/(reclen+4)) //check是否為整數
	
	 //計算slot_num為幾位數字
	int count=1;
	 while(slot_num>=10){
		count++;
		slot_num=slot_num/10;
	}
	pageID_base = pow(10,count)
	
	//initialize name
	R_name = name;
	R_datatype = datatype;
}

void Relation::delete(int key){
	
// Error handling 
  iter3 = key2record.find(key);
if(iter3 == key2record.end()){	
   cout<<"Do not Find this record"<<endl;
   return;
} 


 //map當中要刪掉	
	
  iter1= key2record.find(key);
  map2record.erase(iter1);
  iter2=key2RID.find(key);
  key2RID.erase(iter2);
  
 //更新RIDtable 
  RIDtable[key]= false;


}

bool SlottedPage::checkFun(){
	for(iter = RIDtable.begin(); iter != RIDtable.end(); iter++){
        if(iter->second == false){
			return false; //這個for loop會不會漏掉iter == RIDtable.end()，且iter->second == false的狀況？
		}
	}
    if(iter == RIDtable.end() && iter->second == false){
        return false;
    }
	return true;
}


int SlottedPage::getnextRID(int RID){
    
}

void SlottedPage::insert(int key, string record){
    if(updatedRID % pageID_base != 0 || updatedRID == 0){//要配出去的RID是中間值或0，直接分配
        key2record.insert(pair<int, string>(key, record));
        key2RID.insert(pair<int, int>(key, updatedRID));
		RIDtable.insert(pair<int, bool>(updatedRID , true));
        updatedRID++;//增加RID時要做處理
    }
    else if(updatedRID % pageID_base == 0){//要配出去的RID是page的開頭
        if(checkFun()){//前面都填滿的狀況
            key2record.insert(pair<int, string>(key, record));
            key2RID.insert(pair<int, int>(key, updatedRID));
            RIDtable.insert(pair<int, bool>(updatedRID , true));
            updatedRID++;
        }
        else{//前面未填滿的狀況
            if(currentRID==updatedRID){ //已掃完的狀況->再掃
                currentRID=0;
                currentRID=getnextRID(currentRID);
                key2record.insert(pair<int, string>(key, record));
                key2RID.insert(pair<int, int>(key, currentRID));
                RIDtable.insert(pair<int, bool>(currentRID , true));
            }
            else{//繼續掃完
                currentRID=getnextRID(currentRID);
                key2record.insert(pair<int, string>(key, record));
                key2RID.insert(pair<int, int>(key, currentRID));
                RIDtable.insert(pair<int, bool>(currentRID , true));
                if(getnextRID(currentRID)==updatedRID){
                    currentRID=updatedRID;
                }
            }
        }
    }
    
}

void main()
{	
/*
//slot_num為單一page中slot個數
 int count=1;
 cout<<"輸入數字";
 int slot_num;
 cin >>slot_num;

 //計算slot_num為幾位數字
 while(slot_num>=10)
 {
  count++;
  slot_num=slot_num/10;
 }
 //cout<<"位數"<<count<<endl;

pageID_base = pow(10,count)
 //RID = page_id*pageID_base + slot_id
int currenRID = 0;
*/
 if(function為I){
	//check currentRID是否為page的頭
	if( currentRID%pageID_base == 0 ){
		//若是頭，則pop vector的內容，currentRID不增加
		//若vector不是空的，則pop出vector的內容
		if(vetor不為empty){
			tempRID = pop vector;
			insert (key, record) to record_map;
			insert (key, tempRID) to RID_map;
		}
		else{//vector is empty
			insert (key, record) to record_map;
			insert (key, currentRID) to RID_map;
			increaseRID(); //RID的增加法寫成function
		}
		
	}
	else{
		//否則直接給currentRID
		insert (key, record) to record_map;
		insert (key, currentRID) to RID_map;
		increaseRID(); //RID的增加法寫成function
	}
 }
 
 if(function為D){
	 //push到vector中，並對vector作sort
	 push vector;
	 sort vector
 }

 system("pause");
}

