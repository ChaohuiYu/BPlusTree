#include <string>
using namespace std;


class BPlusTree (T key, int RID)  {
public: 
	BPlusTree(T key, int RID)
	void insertRid(T key, int RID);
	void deleteRid(T key);
	int queryRid(T key);



private:
	BPlusTreeNode* root;
	
	int key_num;
	int key[MAX_CHILD_NUMBER];
	int pos[MAX_CHILD_NUMBER];
	void* child[MAX_CHILD_NUMBER];
	 BPlusTreeNode* father;
	 BPlusTreeNode* next;
	 BPlusTreeNode* last;
} ;