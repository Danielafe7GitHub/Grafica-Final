#include "engine.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include "parser.h"
#include <memory.h>

// constructor
engine::engine(std::string __scene_file, unsigned short __width, unsigned short __height) {
    // size of viewport
    _width = __width;
    _height = __height;

    // parse the file
    std::string __msg;
    if (!parser::parse(*this, __scene_file, __msg))
        fl_message("%s", __msg.c_str());
}

// destructor
engine::~engine() {
    for (register unsigned long __i = 0; __i < _objects.size(); __i++)
        delete _objects[__i];
    for (register unsigned long __i = 0; __i < _dlights.size(); __i++)
        delete _dlights[__i];
    for (register unsigned long __i = 0; __i < _plights.size(); __i++)
        delete _plights[__i];
}

// run
int engine::run() {
    // the window
    Fl_Window __main_win(_width, _height, "simple renderer");

    // start the window
    __main_win.begin();

    // the main window color
    __main_win.color(FL_BLACK);

    // the viewport size
    Rectangle __vsize(0, 0, _width, _height);

    // the list of objects
    object **__scene = new object*[_objects.size()];
    for (register unsigned long __i = 0; __i < _objects.size(); __i++)
        __scene[__i] = _objects[__i];

    // the list of point lights
    plight *__plights = new plight[_plights.size()];
    for (register unsigned long __i = 0; __i < _plights.size(); __i++)
    {
        __plights[__i] = *_plights[__i];
        /*std::cout<<"punto de luz "<<_plights[__i]->_pos[0]<<std::endl;
        std::cout<<"punto de luz "<<_plights[__i]->_pos[1]<<std::endl;
        std::cout<<"punto de luz "<<_plights[__i]->_pos[2]<<std::endl;
        std::cout<<"punto de luz "<<_plights[__i]->_pos[3]<<std::endl;

        std::cout<<"punto de _color "<<_plights[__i]->_color[0]<<std::endl;
        std::cout<<"punto de _color "<<_plights[__i]->_color[1]<<std::endl;
        std::cout<<"punto de _color "<<_plights[__i]->_color[2]<<std::endl;
        std::cout<<"punto de _color "<<_plights[__i]->_color[3]<<std::endl;*/
    }
       

    // the list of directional lights
    dlight *__dlights = new dlight[_dlights.size()];
    for (register unsigned long __i = 0; __i < _dlights.size(); __i++)
        __dlights[__i] = *_dlights[__i];

    // create the renderer
    renderer __renderer(__scene, (unsigned long) _objects.size(), __dlights,
            (unsigned long) _dlights.size(), __plights, (unsigned long) _plights.size(), _ambient);

    // the viewport
    viewport __viewport(__vsize, &__renderer, &_camera, _bcolor);

    // end the window
    __main_win.end();

    // show the window
    __main_win.show(0, 0);

    // run
    int __result = Fl::run();

    // delete objects
    delete[] __plights;
    delete[] __dlights;
    delete[] __scene;

    // return result code
    return __result;
}

// ambient light
vector<3>& engine::ambient() {
    return _ambient;
}

// add point light
void engine::add_point_light(plight *__light) {
    _plights.push_back(__light);
}

// add directional light
void engine::add_directional_light(dlight *__light) {
    _dlights.push_back(__light);
}

// add object
void engine::add_object(object *__object) {
    _objects.push_back(__object);
}

// set background color
vector<3>& engine::backgroud_color() {
    return _bcolor;
}

// camera
camera& engine::cam() {
    return _camera;
}
