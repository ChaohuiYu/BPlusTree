#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <map>
#include <vector>
using namespace std;

class Relation{
	public:
		Relation(string name,string datatype,int reclen);
		void insert(int key, string record); //回傳RID		
		void delete(int key); //回傳Delelte 那筆record 的RID	
	
	
	private:
	  int slot_num;
	  int pageID_base;
	  map<int, string> key2record;
	  map<int, int> key2RID;
	  vector<int> delete_list;
	  int currenRID=0;
	  string R_name;
	  string R_datatype;
}	  
