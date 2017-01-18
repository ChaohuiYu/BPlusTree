#include "SlottedPageStructure.h"

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

int main() {
    SlottedPageStructure sp = SlottedPageStructure(100);
    FOR(i, 0, 12) {
        cout << "rid: " << sp.insertRecord("d" + to_string(i)) << endl;
    }
    cout << "delete 0 3 9\n";
    sp.deleteRecord(0);
    sp.deleteRecord(3);
    sp.deleteRecord(9);
    FOR(i, 12, 20) {
        sp.insertRecord("d" + to_string(i));
    }
    sp.insertRecord("_d3");
    cout << "delete 0 1 3 4 9\n";
    sp.deleteRecord(0);
    sp.deleteRecord(1);
    sp.deleteRecord(3);
    sp.deleteRecord(4);
    sp.deleteRecord(9);
    FOR(i, 20, 28) {
        sp.insertRecord("d" + to_string(i));
    }
    sp.print();

    // system("pause");
    return 0;
}
