#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <map>
#include <vector>
using namespace std;

class Relation{
	public:
		Relation(string name,string datatype,int reclen);
	
	
	
	
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