#include <string>
#include "Relation.h"

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

int main() {
    auto rel = Relation<int>("student", "integer", 100);
    rel.insertRecord(3, "ashuf");
    rel.insertRecord(5, "fwejoilskd");
    rel.queryRid(5);
    rel.printPage(0);
    return 0;
}
