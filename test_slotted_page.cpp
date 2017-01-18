#include "SlottedPageStructure.h"

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

int main() {
    SlottedPageStructure sp = SlottedPageStructure(100);
    cout << "pageNum: " << sp.getPageNum() << endl;
    FOR(i, 0, 12) {
        sp.insertRecord("d" + to_string(i));
    }
    cout << "pageNum: " << sp.getPageNum() << endl;
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
    // FOR(i, 20, 28) {
    //     sp.insertRecord("d" + to_string(i));
    // }
    // sp.print();
    sp.printPage(0);
    sp.printPage(1);
    sp.printPage(2);
    sp.printPage(3);
    sp.printPage(4);
    sp.printPage(5);

    // system("pause");
    return 0;
}
