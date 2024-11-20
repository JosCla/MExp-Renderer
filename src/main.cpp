#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "calc_file_lib/calcfile.h"
#include "mexpmap.h"
#include "mexprender.h"
#include "sprite.h"

int main() {
    SpriteRegistry::initialize();

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

    MExpMap map(calcfile);
    MExpRender render(map);

    string out_path = "hello.ppm";
    render.export_render(out_path);

    return 0;
}
