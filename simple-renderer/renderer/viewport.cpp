#include "viewport.h"
#include <FL/fl_draw.H>
#include <FL/Fl.H>

#include <iostream>
#include <memory.h>
#include <time.h>

//! after this date, you can't use this code
#define DAY   1
#define MONTH 4
#define YEAR  9

// constructor
viewport::viewport(const Rectangle& __rec, renderer *__renderer, camera *__camera,
        vector<3> __bcolor) :
        Fl_Widget(__rec.x(), __rec.y(), __rec.w(), __rec.h(), "raylite"), _renderer(__renderer), _camera(
                __camera) {
    _bcolor = __bcolor;
    _mldown = _mrdown = false;
    _mx = _my = 0;
}

// return camera
camera* viewport::cam() {
    return _camera;
}

// return backgroud color
vector<3>& viewport::backgroud_color() {
    return _bcolor;
}

// the drawing function
void viewport::draw() {
    // render scene
    unsigned char *__scene = new unsigned char[w() * h() * 3];
    memset(__scene, 0, w() * h() * 3 * sizeof(unsigned char));

    // the color buffer
    float *__color = new float[h() * w() * 4];

    // render the scene
    _renderer->render(_camera, w(), h(), __color);

    // for each pixel
    for (register unsigned short __j = 0; __j < h(); __j++) {
        for (register unsigned short __i = 0; __i < w(); __i++) {
            // the resulting color
            vector<3> __tcolor;
            __tcolor[0] = __color[(__j * w() + __i) * 4 + 0]
                    + _bcolor[0] * (1.f - __color[(__j * w() + __i) * 4 + 3]);
            if (__tcolor[0] > 1.f)
                __tcolor[0] = 1.f;
            __tcolor[1] = __color[(__j * w() + __i) * 4 + 1]
                    + _bcolor[1] * (1.f - __color[(__j * w() + __i) * 4 + 3]);
            if (__tcolor[1] > 1.f)
                __tcolor[1] = 1.f;
            __tcolor[2] = __color[(__j * w() + __i) * 4 + 2]
                    + _bcolor[2] * (1.f - __color[(__j * w() + __i) * 4 + 3]);
            if (__tcolor[2] > 1.f)
                __tcolor[2] = 1.f;

            // writing the result
            __scene[(__j * w() + __i) * 3 + 0] = (unsigned char) (__tcolor[0] * 255);
            __scene[(__j * w() + __i) * 3 + 1] = (unsigned char) (__tcolor[1] * 255);
            __scene[(__j * w() + __i) * 3 + 2] = (unsigned char) (__tcolor[2] * 255);
        }
    }

    // delete the color buffer
    delete[] __color;

    // the viewport rect
    Rectangle __rect(0, 0, w(), h());

    // draw the scene
    fl_draw_image(__scene, x(), y(), w(), h());

    // free memory
    delete[] __scene;
}

//! the event handling function
int viewport::handle(int __msg) {
    switch (__msg) {
    case FL_PUSH:
        // update the mouse position
        _mx = Fl::event_x();
        _my = Fl::event_y();

        return 1;
    case FL_DRAG:
        // handle mouse move
        if (Fl::event_button() == FL_LEFT_MOUSE) {
            _camera->rotatey(-(float) Fl::event_x() + (float) _mx);
            _camera->rotatex(-(float) Fl::event_y() + (float) _my);
        } else if (Fl::event_button() == FL_RIGHT_MOUSE) {
            _camera->translatez((float) Fl::event_y() - (float) _my);
        }

        // update the mouse position
        _mx = Fl::event_x();
        _my = Fl::event_y();

        //redraw
        redraw();

        return 1;
    default:
        return Fl_Widget::handle(__msg);
    }
    return 0;
}
