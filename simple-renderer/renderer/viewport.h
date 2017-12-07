#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include "rectangle.h"
#include "vector.h"

#include "renderer.h"
#include "camera.h"

//! the viewport to show the scene
class viewport: public Fl_Widget {
public:
    //! constructor
    viewport(const Rectangle& __rec, renderer *__renderer, camera *__camera, vector<3> __bcolor);

    //! return camera
    camera* cam();

    //! return backgroud color
    vector<3>& backgroud_color();

    //! drawing function
    virtual void draw();

    //! the event handling function
    virtual int handle(int __msg);

protected:
    //! the last x mouse position
    int _mx;

    //! the last y mouse position
    int _my;

    //! if the mouse left button is down
    bool _mldown;

    //! if the mouse right button is down
    bool _mrdown;

    //! the renderer
    renderer *_renderer;

    //! the camera
    camera *_camera;

    //! the background color
    vector<3> _bcolor;

};

#endif
