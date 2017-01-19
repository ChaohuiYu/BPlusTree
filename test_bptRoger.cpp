#include <string>
#include "BPlusTreeRoger.h"

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

int main() {
    // auto bpt = BPlusTreeSimulator<int>();
    // bpt.insertRid(2, 3);
    // bpt.insertRid(4, 65537);
    // bpt.print();

    auto bpt = BPlusTreeRoger<int>();

    bpt.insertValue(1, 1);
    bpt.insertValue(2, 2);
    bpt.insertValue(4, 4);
    bpt.insertValue(237, 237);
    bpt.insertValue(34, 34);
    bpt.insertValue(454, 454);
    bpt.insertValue(23, 23);
    bpt.insertValue(5, 5);
    bpt.insertValue(87, 87);
    bpt.insertValue(987, 987);
    bpt.insertValue(9487, 9487);
    bpt.insertValue(13, 10);
    bpt.insertValue(12, 10);
    bpt.insertValue(11, 10);
    bpt.insertValue(10, 10);
    bpt.insertValue(-1, -1);

    cout << "query 237:" << bpt.queryValue(237) << endl;
    cout << "query 9487:" << bpt.queryValue(9487) << endl;

    bpt.printTree();

    bpt.deleteValue(10);
    bpt.deleteValue(1);
    bpt.deleteValue(2);
    bpt.deleteValue(4);
    bpt.deleteValue(12);
    bpt.deleteValue(9487);

    bpt.printTree();

    //
    //
    // auto bpt2 = BPlusTreeRoger<string>();
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
