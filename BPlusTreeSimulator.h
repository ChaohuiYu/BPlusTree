#include <string>
#include <map>
using namespace std;

#ifndef BPT_H
#define BPT_H

template <class T>
class BPlusTreeSimulator {
    public:
        BPlusTreeSimulator();
        void insertRid(T key, int rid);
        void deleteRid(T key);
        int queryRid(T key);
        // vector<int> rangeQueryRid(T key1, T key2);
        int getLeafPageNum();
        int getNonLeafPageNum();
        int getPageNum();

        void print();

    private:
        map<T, int> key2rid;
        bool keyExists(T key);
};

#endif
