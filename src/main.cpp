#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "calc_file_lib/calcfile.h"
#include "mexpmap.h"
#include "sprite.h"
#include "image.h"

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
    Image img(255, 255, 255);

    img.queue_sprite(SpriteRegistry::water_sprite, 0, 0);
    img.queue_sprite(SpriteRegistry::rock_sprite, -8, 8);
    img.queue_sprite(SpriteRegistry::rock_sprite, 0, 8);
    img.queue_sprite(SpriteRegistry::rock_sprite, 8, 8);
    img.queue_sprite(SpriteRegistry::entity_sprites.at(0), 8, 16);
    img.run_sprite_queue();
    string out_path = "hello.ppm";
    img.export_ppm(out_path);

    return 0;
}
