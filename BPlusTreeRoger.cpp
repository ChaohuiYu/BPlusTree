#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "BPlusTreeRoger.h"
using namespace std;

#define BPT BPlusTreeRoger
#define BPT_NODE BPlusTreeRoger<T>::BPlusTreeNode
#define FOR(i,a,b) for(int i=(a);i<(b);i++)

// public functions

template <class T>
BPT<T>::BPT() {
    _maxKeyCount = 4;
    _root = new BPT_NODE(true, true, _maxKeyCount);
    _nodeCount = 1;
    _leafCount = 1;
}

template <class T>
bool BPT<T>::insertValue(T key, int value) {
    // find the leaf page that the key may be in.
    BPT_NODE* leaf = findLeaf(key);

    // if key in leaf->_keys, don't insert
    FOR(i, 0, leaf->_keyCount)
        if (key == leaf->_keys[i])
            return false;

    insertInNode(leaf, key, (void *)value);
    return true;
}

template <class T>
bool BPT<T>::deleteValue(T key) {
    // find the leaf page that the key may be in.
    BPT_NODE* leaf = findLeaf(key);

    // if key in leaf->_keys, delete it
    FOR(i, 0, leaf->_keyCount) {
        if (key == leaf->_keys[i]) {
            deleteInNode(leaf, key);
            return true;
        }
    }

    // if key doesn't exist
    cout << "error: key " << key << " doesn't exist.\n";
    return false;
}

template <class T>
int BPT<T>::queryValue(T key) {
    // find the leaf page that the key may be in.
    BPT_NODE* leaf = findLeaf(key);

    // if key in leaf->_keys, return it
    FOR(i, 0, leaf->_keyCount)
        if (key == leaf->_keys[i])
            return (int)(long long)(leaf->_pointers[i+1]);

    // if key doesn't exist
    cout << "error: key " << key << " doesn't exist.\n";
    return -1;
}

// private functions

template <class T>
typename BPT_NODE* BPT<T>::findLeaf(T key) {
    BPT_NODE* node = _root;
    while (!node->_isLeaf) {
        FOR(i, 0, node->_keyCount + 1) {
            if (i == node->_keyCount || key < node->_keys[i]) {
                node = (BPT_NODE*)node->_pointers[i];
                break;
            }
        }
    }
    return node;
}

template <class T>
void BPT<T>::insertInNode(BPT_NODE* node, T key, void* value) {
    // find position to insert
    int insertIdx = 0;
    while (insertIdx < node->_keyCount && node->_keys[insertIdx] < key) insertIdx++;

    // move the key and values after the position right
    for (int i = node->_keyCount; i > insertIdx; i--)
        node->_keys[i] = node->_keys[i-1];
    for (int i = node->_keyCount + 1; i > insertIdx + 1; i--)
        node->_pointers[i] = node->_pointers[i-1];

    // insert key and value
    node->_keys[insertIdx] = key;
    node->_pointers[insertIdx + 1] = value;
    node->_keyCount++;

    if (node->_keyCount == _maxKeyCount) // need to split
        splitNode(node);
}

template <class T>
void BPT<T>::deleteInNode(BPT_NODE* node, T key) {
    int deleteIdx = 0 ;
    while (key != node->_keys[deleteIdx]) deleteIdx++ ;
    for (int i = deleteIdx; i < node->_keyCount - 1; i++)
        node->_keys[i] = node->_keys[i+1];
    for (int i = deleteIdx + 1; i < node->_keyCount; i++)
        node->_pointers[i] = node->_pointers[i+1];
    node->_keyCount--;
}

template <class T>
void BPT<T>::splitNode(BPT_NODE* node) {
    // create a new node, it will be the sibling in the right
    // move rightmost (_maxKeyCount - _maxKeyCount / 2) elements to new node

    BPT_NODE* newNode = new BPT_NODE(false, false, _maxKeyCount);
    _nodeCount++;

    int midIdx = _maxKeyCount / 2;
    T midKey = node->_keys[midIdx];

    newNode->_keyCount = _maxKeyCount - midIdx;
    FOR(i, 0, newNode->_keyCount) {
        newNode->_keys[i] = node->_keys[ i + midIdx ];
        newNode->_pointers[i] = node->_pointers[ i + midIdx ];
    }
    newNode->_pointers[ newNode->_keyCount ] = node->_pointers[ node->_keyCount ];
    node->_keyCount = midIdx;

    if (node->_isLeaf) {
        // node->_keyCount++;
        // newNode->_pointers[0] = node->_pointers[0];
        // node->_pointers[0] = newNode;
        newNode->_isLeaf = true;
        // midKey = node->_keys[ _maxKeyCount / 2 + 1 ] ;
    }

    if (node->_isRoot) {
        // create a new root
        node -> _isRoot = false ;

        _root = new BPT_NODE(false, false, _maxKeyCount);
        _nodeCount++;

        _root->_isRoot = true;
        _root->_keys[0] = midKey;
        _root->_pointers[0] = node;
        _root->_pointers[1] = newNode;
        _root->_keyCount = 1;

        node->_father = _root;
        newNode->_father = _root;
    }
    else {
        newNode->_father = node->_father;
        insertInNode( (BPT_NODE *)node->_father, midKey, (void *)newNode ) ;
    }

    // cout << "after split: _root, node, newNode\n";
    // _root->printNode();
    // node->printNode();
    // newNode->printNode();
    // cout << "node == _root->_pointers[0] : " << (node == _root->_pointers[0]) << endl;
    // cout << "newNode == _root->_pointers[1] : " << (newNode == _root->_pointers[1]) << endl;
}

template <class T>
void BPT<T>::printTree() {
    int level = 0;
    BPT_NODE* node;
    vector<BPT_NODE*> nodeStack {_root};
    vector<int> levelStack {0};

    while(!nodeStack.empty()) {
        node = nodeStack.back();
        nodeStack.pop_back();
        level = levelStack.back();
        levelStack.pop_back();

        FOR(i, 0, level) {
            cout << "  ";
        }
        node->printNode();

        if (!node->_isLeaf) {
            for (int i = node->_keyCount; i >= 0; i--) {
                if (node->_pointers[i] != NULL) {
                    nodeStack.push_back((BPT_NODE*)node->_pointers[i]);
                    levelStack.push_back(level+1);
                }
            }
        }
    }
}



template <class T>
BPT_NODE::BPlusTreeNode(bool isLeaf, bool isRoot, int maxKeyCount) {
    _maxKeyCount = maxKeyCount;
    _keyCount = 0;
    _isLeaf = isLeaf;
    _isRoot = isRoot;
    // _keys = vector<T>();
    // _pointers = vector<void*>();
    _keys = new T[_maxKeyCount];
    _pointers = new void*[_maxKeyCount+1];
    _pointers[0] = NULL;
    _father = NULL;
}

template <class T>
void BPT_NODE::printNode() {
    if (_isLeaf) {
        FOR(i, 0, _keyCount) {
            cout << _keys[i] << ":" << (int)(long long)_pointers[i+1] << " | ";
        }
        cout << endl;
    }
    else {
        FOR(i, 0, _keyCount) {
            cout << _pointers[i] << " | ";
            cout << _keys[i] << ":";
        }
        cout << _pointers[_keyCount] << endl;
    }
}

template class BPlusTreeRoger<int>;
template class BPlusTreeRoger<string>;
