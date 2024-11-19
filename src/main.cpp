#include <iostream>
#include <string>
#include <vector>
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
    vector<vector<int>> island_nums = map.get_island_numbers();

    for (vector<int> row : island_nums) {
        for (int col : row) {
            if (col == 0) {
                cout << '0';
            } else {
                cout << (char)(col + (int)'a' - 1);
            }
        }
        cout << endl;
    }

    return 0;
}
