#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "calc_file_lib/calcfile.h"
#include "mexpmap.h"
#include "sprite.h"

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
    vector<vector<int>> island_rows = map.get_heights();

    for (MExpEntity entity : map.get_entities()) {
        island_rows.at(entity.y).at(entity.x) = 99;
    }

    for (vector<int> row : island_rows) {
        for (int col : row) {
            cout << (char)((int)'a' + col);
        }
        cout << endl;
    }

    SpriteRegistry::initialize();

    return 0;
}
