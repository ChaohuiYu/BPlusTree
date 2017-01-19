#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class BPlusTree {
    public:
        BPlusTree();
        bool insertValue(T key, int value);
        bool deleteValue(T key);
        int queryValue(T key);
        void printTree();
        // vector<int> rangeQueryValue(T key1, T key2);
        // int getLeafPageNum();
        // int getNonLeafPageNum();
        // int getPageNum();
    private:
        class BPlusTreeNode {
            public:
                BPlusTreeNode(bool isLeaf, bool isRoot, int maxKeyCount);
                void printNode();
                int _maxKeyCount;
                int _keyCount;
                bool _isLeaf;
                bool _isRoot;
                T* _keys;
                void** _pointers;
                void* _father;
            private:
        };
    private:
        BPlusTreeNode* _root;
        int _maxKeyCount;
        int _nodeCount;
        int _leafCount;
        // int _nonLeafCount;
        BPlusTreeNode* findLeaf(T key);
        void insertInNode(BPlusTreeNode* node, T key, void* value);
        void splitNode(BPlusTreeNode* node);
        void deleteInNode(BPlusTreeNode* node, T key);
};
