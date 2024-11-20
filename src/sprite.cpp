// sprite.cpp
// Implements sprite.h.

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "sprite.h"

Sprite::Sprite(string &sprite_str) {
    string first_half = sprite_str.substr(0, 16);
    string second_half = sprite_str.substr(16, 16);

    for (int row = 0; row < 8; row++) {
        char first_left = first_half[row * 2];
        char first_right = first_half[row * 2 + 1];
        int first = _hex_ascii_to_int(first_left) * 16
            + _hex_ascii_to_int(first_right);

        char second_left = second_half[row * 2];
        char second_right = second_half[row * 2 + 1];
        int second = _hex_ascii_to_int(second_left) * 16
            + _hex_ascii_to_int(second_right);

        vector<int> curr_row;
        for (int col = 0; col < 8; col++) {
            int first_bit = (first >> (7 - col)) & 1;
            int second_bit = (second >> (7 - col)) & 1;

            curr_row.push_back(first_bit * 2 + second_bit);
        }
    }
}

vector<vector<int>> Sprite::get_colors() const {
    return _colors;
}

vector<int> Sprite::get_rgb(int color) {
    switch (color) {
    case 1:
        return {255, 255, 255};
    case 2:
        return {127, 127, 127};
    case 3:
    default:
        return {0, 0, 0};
    }
}

int Sprite::_hex_ascii_to_int(char hex) {
    if (hex >= '0' && hex <= '9') {
        return (int)hex - (int)'0';
    } else if (hex >= 'A' && hex <= 'F') {
        return (int)hex - (int)'A';
    } else if (hex >= 'a' && hex <= 'a') {
        return (int)hex - (int)'a';
    }

    return 0;
}

vector<Sprite> SpriteRegistry::entity_sprites = {};
vector<Sprite> SpriteRegistry::ground_sprites = {};
vector<Sprite> SpriteRegistry::wall_sprites = {};

string zero_str = "00000000000000000000000000000000";
Sprite SpriteRegistry::water_sprite = Sprite(zero_str);
Sprite SpriteRegistry::rock_sprite = Sprite(zero_str);
Sprite SpriteRegistry::stump_sprite = Sprite(zero_str);

void SpriteRegistry::initialize() {
    // initializing entities
    vector<string> ent_strs = {
        "1824183C66243C24183C183C7E3C3C24"
        , "0018243C3C3C180000183C3C24241800"
        , "18183C3C7E7E3C001818242442423C00"
        , "00007EFDFD7E000000007E87877E0000"
        , "183C3C3C3C3C241818242424243C3C18"
        , "7EFDFD7E7EFDFD7E7EA7A77E7EA7A77E"
        , "66FFFFFFFFFF99666699FF9999FFFF66"
        , "00182418A542423C00183C18BD7E7E3C"
        , "00FF81B581FF181800FFFFFFFFFF1818"
    };
    for (string str : ent_strs) {
        Sprite s(str);
        entity_sprites.push_back(s);
    }

    // initializing ground sprites
    vector<string> ground_strs = {
        "FF818385A5C1C1FF007E7C7A5A3E3E00"
        , "FF858B85A1D1A1FF007A747A5E2E5E00"
        , "FF818981A18581FF007E767E5E7A7E00"
        , "FF85A9C18395A1FF007A563E7C6A5E00"
    };
    for (string str : ground_strs) {
        Sprite s(str);
        ground_sprites.push_back(s);
    }

    // initializing wall sprites
    vector<string> wall_strs = {
        "FFFFFFFFFFFFFFFFCFFF9FFFF3FFF9FF"
        , "AAAA5555AAAA55555555AAAA5555AAAA"
        , "FFC3FFC3FFC3FFC3FFFFFFFFFFFFFFFF"
        , "AABE557DAABE557D557DAABE557DAABE"
    };
    for (string str : wall_strs) {
        Sprite s(str);
        wall_sprites.push_back(s);
    }

    // initializing everything else
    string water_str = "FFDFAFFFFFFBF5FF0020500000040A00";
    water_sprite = Sprite(water_str);
    string rock_str = "183C7E7EFFFFFF7E1824524681A1817E";
    rock_sprite = Sprite(rock_str);
    string stump_str = "0018243C7E3C000000183C3C423C0000";
    stump_sprite = Sprite(stump_str);
}
