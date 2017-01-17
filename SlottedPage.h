#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <map>
#include <vector>
using namespace std;

class SlottedPage{
	public:
		SlottedPage(string name,string datatype,int reclen);
		void insert(int key, string record); //回傳RID
		void delete(int key); //回傳Delelte 那筆record 的RID
		bool checkFun();//check RIDtable中前面的值是否都填滿
		int getnextRID(int RID);

	private:
		int slot_num;
		int pageID_base;
		map<int, string> key2record;
		map<int, int> key2RID;
		map<int, bool> RIDtable;
		int currentRID=0; //掃把指標
		int updatedRID=0; //指到目前未被分配出去的最小RID值，如已分配完0~4頁，則updatedRID值為500
		string R_name;
		string R_datatype;
};
