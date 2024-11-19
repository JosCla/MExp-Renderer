// mexpmap.cpp
// Implements mexpmap.h.

// C++ Standard Library
#include <string>
using std::string;
#include <vector>
using std::vector;

// Our files
#include "mexpmap.h"
#include "calc_file_lib/calcfile.h"

MExpMap::MExpMap(Calc8XvFile &file) {
    _parse_file(file);
}

vector<vector<int>> MExpMap::get_island_numbers() const {
    return _island_numbers;
}

vector<MExpEntity> MExpMap::get_entities() const {
    vector<MExpEntity> ents;

    for (MExpIsland island : _island_data) {
        for (MExpEntity entity : island.entities) {
            ents.push_back(entity);
        }
    }

    return ents;
}

vector<vector<int>> MExpMap::get_heights() const {
    return _heights;
}

vector<vector<MExpTileProps>> MExpMap::get_tile_other_props() const {
    return _other_props;
}

void MExpMap::_parse_file(Calc8XvFile &file) {
    // TODO
}
