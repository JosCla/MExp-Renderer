#ifndef SPRITE_H
#define SPRITE_H
// sprite.h
// Defines the Sprite object, used to draw MExp stuff.
// Also defines a sprite registry to hold all sprites.

#include <string>
#include <vector>

class Sprite {
public:
    // constructor
    Sprite(std::string &sprite_str);

    // getters
    std::vector<std::vector<int>> get_colors() const;
    static std::vector<int> get_rgb(int color);

private:
    // data
    std::vector<std::vector<int>> _colors;

    // other helpers
    int _hex_ascii_to_int(char hex);
};

class SpriteRegistry {
public:
    static void initialize();

    static std::vector<Sprite> entity_sprites;
    static std::vector<Sprite> ground_sprites;
    static std::vector<Sprite> wall_sprites;

    static Sprite water_sprite;
    static Sprite rock_sprite;
    static Sprite stump_sprite;

    static Sprite left_edge_sprite;
    static Sprite up_edge_sprite;
    static Sprite right_edge_sprite;
    static Sprite down_edge_sprite;

    static std::vector<int> entity_upward_displacements;
};

#endif // SPRITE_H
