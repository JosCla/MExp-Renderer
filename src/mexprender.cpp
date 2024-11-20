// mexprender.cpp
// Implements mexprender.h.

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "mexprender.h"
#include "mexpmap.h"
#include "image.h"
#include "sprite.h"

MExpRender::MExpRender(MExpMap &map) : _map(map), _image(160, 176, 160) {}

void MExpRender::export_render(string &path) {
    _render_screen();

    _image.export_ppm(path);
}

void MExpRender::_render_screen() {
    // time to render the screen!
    // very reminiscent of MEDRAW
    for (int y = 0; y < _map.get_height(); y++) {
        for (int x = 0; x < _map.get_width(); x++) {
            int screenX = x * 8;
            int screenY = y * 8;
            _render_tile(x, y, screenX, screenY);
        }
    }

    // running sprite queue
    _image.run_sprite_queue();
}

void MExpRender::_render_tile(int x, int y, int screenX, int screenY) {
    // getting tile props
    MExpTileProps curr_props = _map.get_other_at(x, y);

    // getting tile heights 
    int curr_height = _map.get_height_at(x, y, true);
    int front_height = _map.get_height_at(x, y + 1, true);

    // rendering wall beneath tile
    int wall_type = (curr_props.isWater ? 1 : 0)
        + ((curr_props.isLadder ? 1 : 0) * 2);
    while (front_height < curr_height) {
        int wall_draw_y = screenY - (front_height * 2);
        _image.queue_sprite(
                SpriteRegistry::wall_sprites.at(wall_type)
                , screenX, wall_draw_y);
        front_height += 4;
    }

    // rendering tile
    int tile_draw_y = screenY - (curr_height * 2);
    if (curr_props.isWater) {
        _image.queue_sprite(
                SpriteRegistry::water_sprite
                , screenX, tile_draw_y);
    } else {
        _image.queue_sprite(
                SpriteRegistry::ground_sprites.at(curr_props.textureIndex)
                , screenX, tile_draw_y);

        // (borders)
        int left_height = _map.get_height_at(x - 1, y, true);
        if (left_height < curr_height) {
            _image.queue_sprite(
                    SpriteRegistry::left_edge_sprite
                    , screenX, tile_draw_y);
        }

        int up_height = _map.get_height_at(x, y - 1, true);
        if (up_height < curr_height) {
            _image.queue_sprite(
                    SpriteRegistry::up_edge_sprite
                    , screenX, tile_draw_y);
        }

        int right_height = _map.get_height_at(x + 1, y, true);
        if (right_height < curr_height) {
            _image.queue_sprite(
                    SpriteRegistry::right_edge_sprite
                    , screenX, tile_draw_y);
        }

        int down_height = _map.get_height_at(x, y + 1, true);
        if (down_height < curr_height) {
            _image.queue_sprite(
                    SpriteRegistry::down_edge_sprite
                    , screenX, tile_draw_y);
        }
    }

    // rendering stumps and rocks
    if (curr_props.isStump) {
        _image.queue_sprite(
                SpriteRegistry::stump_sprite
                , screenX, tile_draw_y);
    } else if (curr_props.isRock) {
        _image.queue_sprite(
                SpriteRegistry::rock_sprite
                , screenX, tile_draw_y - 2);
    }

    // rendering entities
    vector<MExpEntity> entities = _map.get_sorted_entities_at(x, y);
    for (MExpEntity ent : entities) {
        int ent_draw_y = screenY - (ent.z * 2);
        ent_draw_y -= SpriteRegistry::entity_upward_displacements.at(ent.type);
        ent_draw_y += 2;

        _image.queue_sprite(
                SpriteRegistry::entity_sprites.at(ent.type)
                , screenX, ent_draw_y);
    }
}
