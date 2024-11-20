#ifndef IMAGE_H
#define IMAGE_H
// image.h
// Defines the Image class, for building PPM images

#include <vector>
#include <string>

#include "sprite.h"

class Image {
public:
    // constructor
    Image(int r, int g, int b);

    // draw a sprite
    void queue_sprite(Sprite &sprite, int x, int y);
    void run_sprite_queue();

    // export function
    void export_ppm(std::string &path);

private:
    // sprite draw queue
    std::vector<Sprite> _queue_sprites;
    std::vector<int> _queue_x;
    std::vector<int> _queue_y;

    // color channels
    std::vector<std::vector<int>> _r;
    std::vector<std::vector<int>> _g;
    std::vector<std::vector<int>> _b;

    // (background)
    int _bg_r;
    int _bg_g;
    int _bg_b;

    // other helpers
    void _initialize_image(int width, int height);
    void _draw_sprite(Sprite &sprite, int x, int y);
};

#endif // IMAGE_H
