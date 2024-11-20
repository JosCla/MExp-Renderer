// mexpmap.cpp
// Implements mexpmap.h.

// C++ Standard Library
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;

// #include <iostream>
// using namespace std;

// Our files
#include "mexpmap.h"
#include "calc_file_lib/calcfile.h"
#include "calc_file_lib/fileutils.h"

bool MExpEntity::operator < (const MExpEntity &other) {
    return z < other.z;
}

MExpMap::MExpMap(Calc8XvFile &file) {
    _parse_file(file);
}

int MExpMap::get_width() const {
    return _width;
}

int MExpMap::get_height() const {
    return _height;
}

vector<vector<int>> MExpMap::get_island_numbers() const {
    return _island_numbers;
}

vector<MExpEntity> MExpMap::get_entities(bool include_player) const {
    vector<MExpEntity> ents;

    for (MExpIsland island : _island_data) {
        if (include_player && island.isFirstIsland) {
            ents.push_back(_get_player_respawned(island));
        }
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

MExpTileProps MExpMap::get_other_at(int x, int y) const {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        return _other_props.at(y).at(x);
    }

    MExpTileProps default_props;
    default_props.isWater = true;
    default_props.isRock = false;
    default_props.isStump = false;
    default_props.isLadder = false;
    default_props.textureIndex = 0;
    return default_props;
}

int MExpMap::get_height_at(int x, int y, bool with_stumps) const {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        int res = _heights.at(y).at(x);
        if (with_stumps) {
            MExpTileProps curr_props = get_other_at(x, y);
            if (curr_props.isStump) {res--;}
        }
        return res;
    }
    return 0;
}

vector<MExpEntity> MExpMap::get_sorted_entities_at(int x, int y) const {
    vector<MExpEntity> res;
    for (MExpEntity ent : get_entities()) {
        if (ent.x == x && ent.y == y) res.push_back(ent);
    }

    sort(res.begin(), res.end());

    return res;
}

void MExpMap::_parse_file(Calc8XvFile &file) {
    // getting file offsets
    string file_data = file.get_data();
    int imap_offset = hexCharsToInt(file_data.substr(0, 2));
    int idat_offset = hexCharsToInt(file_data.substr(2, 2));
    int hmap_offset = hexCharsToInt(file_data.substr(4, 2));
    int omap_offset = hexCharsToInt(file_data.substr(6, 2));

    // getting and parsing raw portions
    string imap_raw = _get_raw_portion(file_data, imap_offset);
    _width = hexCharsToInt(imap_raw.substr(0, 1));
    _height = hexCharsToInt(imap_raw.substr(1, 1));
    _parse_imap(imap_raw);
    string idat_raw = _get_raw_portion(file_data, idat_offset);
    _parse_idat(idat_raw);
    string hmap_raw = _get_raw_portion(file_data, hmap_offset);
    _parse_hmap(hmap_raw);
    string omap_raw = _get_raw_portion(file_data, omap_offset);
    _parse_omap(omap_raw);
}

string MExpMap::_get_raw_portion(string &file_data, int offset) const {
    int size = hexCharsToInt(file_data.substr(offset - 2, 2));
    return file_data.substr(offset, size);
}

void MExpMap::_parse_imap(string &imap_raw) {
    _imap_raw = imap_raw;

    for (int i = 0; i < _height; i++) {
        vector<int> row;
        for (int j = 0; j < _width; j++) {
            int offset = (i * _width) + j + 2;
            int col = hexCharsToInt(imap_raw.substr(offset, 1));
            row.push_back(col);
        }
        _island_numbers.push_back(row);
    }
}

void MExpMap::_parse_idat(string &idat_raw) {
    _idat_raw = idat_raw;

    int num_islands = hexCharsToInt(idat_raw.substr(0, 2));
    for (int i = 1; i <= num_islands; i++) {
        int island_offset = hexCharsToInt(idat_raw.substr(i * 2, 2));

        MExpIsland island;
        island.islandNum = i;
        island.respawnX = hexCharsToInt(idat_raw.substr(island_offset + 1, 1));
        island.respawnY = hexCharsToInt(idat_raw.substr(island_offset + 2, 1));
        island.respawnZ = hexCharsToInt(idat_raw.substr(island_offset + 3, 1));
        island.isFirstIsland
            = hexCharsToInt(idat_raw.substr(island_offset + 4, 1)) == 1;
        island.prevIslandNum
            = hexCharsToInt(idat_raw.substr(island_offset + 5, 1));
        island.nextIslandNum
            = hexCharsToInt(idat_raw.substr(island_offset + 6, 1));

        int num_ents = hexCharsToInt(idat_raw.substr(island_offset, 1));
        for (int j = 1; j <= num_ents; j++) {
            int entity_offset = island_offset + (j * 8);

            MExpEntity entity;
            entity.type = hexCharsToInt(idat_raw.substr(entity_offset, 1));
            entity.x = hexCharsToInt(idat_raw.substr(entity_offset + 1, 1));
            entity.y = hexCharsToInt(idat_raw.substr(entity_offset + 2, 1));
            entity.islandNum
                = hexCharsToInt(idat_raw.substr(entity_offset + 3, 1));
            entity.entityNum
                = hexCharsToInt(idat_raw.substr(entity_offset + 4, 1));
            entity.z = hexCharsToInt(idat_raw.substr(entity_offset + 5, 1));
            entity.extraByte1
                = hexCharsToInt(idat_raw.substr(entity_offset + 6, 1));
            entity.extraByte2
                = hexCharsToInt(idat_raw.substr(entity_offset + 7, 1));

            island.entities.push_back(entity);
        }

        _island_data.push_back(island);
    }
}

void MExpMap::_parse_hmap(string &hmap_raw) {
    _hmap_raw = hmap_raw;

    for (int i = 0; i < _height; i++) {
        vector<int> row;
        for (int j = 0; j < _width; j++) {
            int offset = (i * _width) + j + 2;
            int col = hexCharsToInt(hmap_raw.substr(offset, 1));
            row.push_back(col);
        }
        _heights.push_back(row);
    }
}

void MExpMap::_parse_omap(string &omap_raw) {
    _omap_raw = omap_raw;

    for (int i = 0; i < _height; i++) {
        vector<MExpTileProps> row;
        for (int j = 0; j < _width; j++) {
            int offset = (i * _width) + j + 2;
            int col = hexCharsToInt(omap_raw.substr(offset, 1));

            MExpTileProps tileProps;
            tileProps.isLadder = ((col & 1) == 1);
            tileProps.isWater = (((col >> 1) & 1) == 1);
            tileProps.isStump = (((col >> 2) & 1) == 1);
            tileProps.isRock = (((col >> 3) & 1) == 1);
            tileProps.textureIndex = ((col >> 4) & 15);

            row.push_back(tileProps);
        }
        _other_props.push_back(row);
    }
}

MExpEntity MExpMap::_get_player_respawned(MExpIsland island) const {
    MExpEntity player;
    player.type = 0;
    player.x = island.respawnX;
    player.y = island.respawnY;
    player.islandNum = 0;
    player.entityNum = 0;
    player.z = island.respawnZ;
    player.extraByte1 = 0;
    player.extraByte2 = 0;

    return player;
}
