#include "renderer.h"
#include <iostream>
#include <cassert>

// constructor
renderer::renderer(object **__objects, unsigned long __num, dlight *__dlights,
        unsigned long __num_dlights, plight *__plights, unsigned long __num_plights,
        vector<3> __ambient) {
    // the objects
    _objects = __objects;
    _num = __num;

    // the directional lights
    _dlights = __dlights;
    _num_dlights = __num_dlights;

    // the positional light
    _plights = __plights;
    _num_plights = __num_plights;

    // the ambient light
    _ambient = __ambient;
}

// destructor
renderer::~renderer() {
    _objects = 0;
    _dlights = 0;
    _plights = 0;
}

// render
void renderer::render(const camera* __camera, unsigned short __w, unsigned short __h,
        float* __color) {
    camera* __mcamera = (camera*) __camera;

    // << TODO >> initialize color buffer to black
    for (register int __i = 0; __i < __w * __h * 4; __i++)
        __color[__i] = 0.f;

    // << TODO >> create and initialize depth buffer

    // << TODO >> for each object, create and initialize temporal
    //			  color and depth buffer and call its rasterize
    //			  function and perform the corresponding
    //			  operations on the result
    for (register unsigned int __i = 0; __i < _num; __i++) {
        float* __tcbuffer = 0;
        float* __tdbuffer = 0;

        _objects[__i]->rasterize(__mcamera, __w, __h, _ambient, _dlights, _num_dlights, _plights,
                _num_plights, __tcbuffer, __tdbuffer);

        for (register int __j = 0; __j < __w * __h * 4; __j++)
            __color[__j] = __tcbuffer[__j];

        delete[] __tcbuffer;
        delete[] __tdbuffer;
    }

}
