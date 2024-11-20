// image.cpp
// Implements image.h.

#include <iostream>
using std::cout; using std::cerr; using std::endl;
#include <fstream>
using std::ofstream;
#include <vector>
using std::vector;
#include <string>
using std::string;

#include "image.h"

Image::Image(int r, int g, int b) {
    _bg_r = r;
    _bg_g = g;
    _bg_b = b;
}

void Image::queue_sprite(Sprite &sprite, int x, int y) {
    _queue_sprites.push_back(sprite);
    _queue_x.push_back(x);
    _queue_y.push_back(y);
}

void Image::run_sprite_queue() {
    if (_queue_sprites.size() == 0) return;

    // first, finding the size of the image
    int minX = _queue_x.at(0);
    int maxX = _queue_x.at(0) + 8;
    for (int x : _queue_x) {
        if (x < minX) minX = x;
        if ((x + 8) > maxX) maxX = x + 8;
    }
    int minY = _queue_y.at(0);
    int maxY = _queue_y.at(0) + 8;
    for (int y : _queue_y) {
        if (y < minY) minY = y;
        if ((y + 8) > maxY) maxY = y + 8;
    }

    int sizeX = maxX - minX;
    int sizeY = maxY - minY;
    _initialize_image(sizeX, sizeY);

    // then drawing all the sprites in the queue!
    for (unsigned int i = 0; i < _queue_sprites.size(); i++) {
        _draw_sprite(
            _queue_sprites.at(i)
            , _queue_x.at(i) - minX
            , _queue_y.at(i) - minY
        );
    }

    _queue_sprites.clear();
    _queue_x.clear();
    _queue_y.clear();
}

void Image::export_ppm(string &path) {
    if (_r.size() == 0) return;

    // opening file
    ofstream fout;
    fout.open(path);
    if (!fout) {
        cerr << "Failed to write to file: " << path << endl;
        return;
    }

    // writing image contents
    unsigned int height = _r.size();
    unsigned int width = _r.at(0).size();
    fout << "P6" << '\t';
    fout << width << '\t';
    fout << height << '\t';
    fout << "255" << '\n';

    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            fout << (char)_r.at(row).at(col);
            fout << (char)_g.at(row).at(col);
            fout << (char)_b.at(row).at(col);
        }
    }

    fout << endl;

    // closing file
    fout.close();
}

void Image::_initialize_image(int width, int height) {
    for (int i = 0; i < height; i++) {
        vector<int> row_r;
        vector<int> row_g;
        vector<int> row_b;

        for (int j = 0; j < width; j++) {
            row_r.push_back(_bg_r);
            row_g.push_back(_bg_g);
            row_b.push_back(_bg_b);
        }

        _r.push_back(row_r);
        _g.push_back(row_g);
        _b.push_back(row_b);
    }
}

void Image::_draw_sprite(Sprite &sprite, int x, int y) {
    vector<vector<int>> colors = sprite.get_colors();

    for (unsigned int row = 0; row < colors.size(); row++) {
        for (unsigned int col = 0; col < colors.at(row).size(); col++) {
            int color = colors.at(row).at(col);
            if (color == 0) continue;

            vector<int> rgb = sprite.get_rgb(color);
            _r.at(row + y).at(col + x) = rgb.at(0);
            _g.at(row + y).at(col + x) = rgb.at(1);
            _b.at(row + y).at(col + x) = rgb.at(2);
        }
    }
}
