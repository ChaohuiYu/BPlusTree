#include "SlottedPage.h"

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

int main() {
    SlottedPage sp = SlottedPage("student", "integer", 100);
    FOR(i, 0, 12) {
        sp.insert(i, "d" + to_string(i));
    }
    cout << "delete 0 3 9\n";
    sp.deleteRecord(0);
    sp.deleteRecord(3);
    sp.deleteRecord(9);
    FOR(i, 12, 20) {
        sp.insert(i, "d" + to_string(i));
    }
    sp.insert(3, "_d3");
    // cout << "delete 0 1 3 4 9\n";
    // sp.deleteRecord(0);
    // sp.deleteRecord(1);
    // sp.deleteRecord(3);
    // sp.deleteRecord(4);
    // sp.deleteRecord(9);
    // FOR(i, 20, 28) {
    //     sp.insert(i, "d" + to_string(i));
    // }
    // sp.print();
    cout << sp.getRealRID(3) << endl;

    // system("pause");
    return 0;
}
