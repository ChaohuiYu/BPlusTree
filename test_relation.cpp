#include <string>
#include "Relation.h"
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

int main() {
    auto rel = Relation<int>("student", "integer", 100);
    FOR(i, 0, 100) {
        rel.insertRecord(i, to_string(i));
    }
    FOR(i, 10, 20) {
        rel.deleteRecord(i);
    }
    // rel.insertRecord(3, "ashuf");
    // rel.insertRecord(5, "fwejoilskd");
    rel.scanIndex();
    rel.queryRid(5);
    rel.rangeQueryRid(5, 10);
    rel.printPage(0);
    rel.printStatistics();
    return 0;
}
