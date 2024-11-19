#include <iostream>
#include <string>
using namespace std;

#include "calc_file_lib/calcfile.h"
#include "mexpmap.h"

int main() {
    string filename;
    cout << "Enter file to read: ";
    cin >> filename;

    Calc8XvFile calcfile;
    int res = calcfile.read(filename);

    if (res) {
        cerr << "Bad file read! Aborting..." << endl;
        return 1;
    }

    if (!calcfile.checksum_valid()) {
        cerr << "Calc file has invalid checksum! Aborting..." << endl;
        return 1;
    }

    calcfile.print();

    MExpMap map(calcfile);

    return 0;
}
