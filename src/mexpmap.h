#ifndef MEXPMAP_H
#define MEXPMAP_H
// mexpmap.h
// Defines an object for manipulating a MExp map provided in a Calc8XvFile.
// Also defines helper types for common constructs in MExp.

#include <string>
#include <vector>

#include "calc_file_lib/calcfile.h"

struct MExpEntity {
public:
    int type;
    int x;
    int y;
    int islandNum;
    int entityNum;
    int z;
    int extraByte1;
    int extraByte2;
};

struct MExpIsland {
public:
    int islandNum;
    int respawnX;
    int respawnY;
    int respawnZ;
    bool isFirstIsland;
    int prevIslandNum;
    int nextIslandNum;

    std::vector<MExpEntity> entities;
};

struct MExpTileProps {
public:
    bool isWater;
    bool isRock;
    bool isStump;
    bool isLadder;
    int textureIndex;
};

class MExpMap {
public:
    // constructor
    MExpMap(Calc8XvFile &file);

    // get various parts of the file
    std::vector<std::vector<int>> get_island_numbers() const;
    std::vector<MExpEntity> get_entities() const;
    std::vector<std::vector<int>> get_heights() const;
    std::vector<std::vector<MExpTileProps>> get_tile_other_props() const;

private:
    // file components
    std::string _imap_raw;
    std::vector<std::vector<int>> _island_numbers;

    std::string _idat_raw;
    std::vector<MExpIsland> _island_data;

    std::string _hmap_raw;
    std::vector<std::vector<int>> _heights;

    std::string _omap_raw;
    std::vector<std::vector<MExpTileProps>> _other_props;

    // parsing the file
    void _parse_file(Calc8XvFile &file);

    // (sub-routines for file parsing)
    std::string _get_raw_portion(std::string &file_data, int offset);
    void _parse_imap(std::string &imap_raw);
    void _parse_idat(std::string &idat_raw);
    void _parse_hmap(std::string &hmap_raw);
    void _parse_omap(std::string &omap_raw);
};

#endif // MEXPMAP_H
