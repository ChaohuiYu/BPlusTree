#include <string>
#include <vector>
#include "BPlusTree.h"

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

using namespace std;

int main() {
    // auto bpt = BPlusTreeSimulator<int>();
    // bpt.insertRid(2, 3);
    // bpt.insertRid(4, 65537);
    // bpt.print();

    auto bpt = BPlusTree<int>(62);
    vector<int> toInsert {34,567,23,56,645,3,452,245,563,56,542,2987,23489,35489,328};

    for (auto& i : toInsert) {
        bpt.insertValue(i, i);
    }
    bpt.printTree();
    cout << "page num: " << bpt.getPageNum() << endl;

    bpt.deleteValue(35489);
    bpt.deleteValue(23489);

    bpt.printTree();
    cout << "page num: " << bpt.getPageNum() << endl;

    //
    // auto bpt = BPlusTree<int>();
    //
    // FOR(i, 0, 100) {
    //     bpt.insertValue(2*i, 2*i);
    // }
    //
    // bpt.printTree();
    //
    // FOR(i, 0, 100) {
    //     bpt.deleteValue(2*i);
    // }
    //
    // bpt.printTree();
    //
    // FOR(i, 0, 10) {
    //     bpt.insertValue(2*i, 2*i);
    // }
    //
    // bpt.printTree();
    //
    // cout << "page num: " << bpt.getPageNum() << endl;
    // cout << "leaf page num: " << bpt.getLeafPageNum() << endl;
    // cout << "non-leaf page num: " << bpt.getNonLeafPageNum() << endl;


    //
    // auto bpt2 = BPlusTree<string>();
    //
    // FOR(i, 0, 100) {
    //     bpt2.insertValue(to_string(2*i), i);
    // }
    //
    // bpt2.printTree();
    //
    // FOR(i, 0, 100) {
    //     bpt2.deleteValue(to_string(2*i));
    // }
    //
    // bpt2.printTree();
    //
    // FOR(i, 0, 10) {
    //     bpt2.insertValue(to_string(2*i), i);
    // }
    //
    // bpt2.printTree();
    //
    // cout << "page num: " << bpt2.getPageNum() << endl;
    // cout << "leaf page num: " << bpt2.getLeafPageNum() << endl;
    // cout << "non-leaf page num: " << bpt2.getNonLeafPageNum() << endl;

    // for (auto& i : bpt.rangeQueryValue(-1, 100)) {
    //     cout << i << ' ';
    // }
    // cout << endl;

    // cout << "query 237:" << bpt.queryValue(237) << endl;
    // cout << "query 9487:" << bpt.queryValue(9487) << endl;


    // bpt.deleteValue(10);
    // bpt.deleteValue(1);
    // bpt.deleteValue(2);
    // bpt.deleteValue(4);
    // bpt.deleteValue(12);
    // bpt.deleteValue(9487);

    // bpt.printTree();

    //
    //
    // auto bpt2 = BPlusTree<string>();
    //
    // bpt2.insertValue("dsifuhj", 3);
    // bpt2.insertValue("34uhijkr", 4);
    // bpt2.insertValue("23io", 24);
    // bpt2.insertValue("as0d", 54892);
    // bpt2.insertValue("3ip40qog", 3278);
    // bpt2.insertValue("efaiouw", 37);
    //
    // bpt2.printTree();
    // cout << "query 1:" << bpt.queryValue(1) << endl;

    // cout << "bpt2 query dsifuhj:" << bpt2.queryValue("dsifuhj") << endl;
    // cout << "bpt2 query 1:" << bpt2.queryValue("1") << endl;
    // bpt.insertRid("348iruek", 65537);
    // bpt.print();
    return 0;
}
