#ifndef MEXPRENDER_H
#define MEXPRENDER_H
// mexprender.h
// Provides utilities for rendering a MExp map to a PPM image

#include <string>

#include "mexpmap.h"
#include "image.h"

class MExpRender {
public:
    // constructor
    MExpRender(MExpMap &map);

    // export render
    void export_render(std::string &path);

private:
    // data
    MExpMap _map;
    Image _image;

    // screen render functions
    void _render_screen();
    void _render_tile(int x, int y, int screenX, int screenY);
};

#endif // MEXPRENDER_H
