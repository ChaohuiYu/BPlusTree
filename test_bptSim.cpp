#include <string>
#include "BPlusTreeSimulator.h"

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

int main() {
    // auto bpt = BPlusTreeSimulator<int>();
    // bpt.insertRid(2, 3);
    // bpt.insertRid(4, 65537);
    // bpt.print();

    auto bpt = BPlusTreeSimulator<string>();
    bpt.insertRid("dsifuhj", 3);
    bpt.insertRid("348iruek", 65537);
    bpt.print();
    return 0;
}
