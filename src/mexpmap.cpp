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
#include "calc_file_lib/fileutils.h"

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
    // getting file offsets
    string file_data = file.get_data();
    int imap_offset = hexCharsToInt(file_data.substr(0, 2));
    int idat_offset = hexCharsToInt(file_data.substr(2, 2));
    int hmap_offset = hexCharsToInt(file_data.substr(4, 2));
    int omap_offset = hexCharsToInt(file_data.substr(6, 2));

    // getting and parsing raw portions
    string imap_raw = _get_raw_portion(file_data, imap_offset);
    _parse_imap(imap_raw);
    string idat_raw = _get_raw_portion(file_data, idat_offset);
    _parse_idat(idat_raw);
    string hmap_raw = _get_raw_portion(file_data, hmap_offset);
    _parse_hmap(hmap_raw);
    string omap_raw = _get_raw_portion(file_data, omap_offset);
    _parse_omap(omap_raw);
}

string MExpMap::_get_raw_portion(string &file_data, int offset) {
    int size = hexCharsToInt(file_data.substr(offset - 2, 2));
    return file_data.substr(offset, size);
}

void MExpMap::_parse_imap(string &imap_raw) {
    _imap_raw = imap_raw;
    // TODO
}

void MExpMap::_parse_idat(string &idat_raw) {
    _idat_raw = idat_raw;
    // TODO
}

void MExpMap::_parse_hmap(string &hmap_raw) {
    _hmap_raw = hmap_raw;
    // TODO
}

void MExpMap::_parse_omap(string &omap_raw) {
    _omap_raw = omap_raw;
    // TODO
}
