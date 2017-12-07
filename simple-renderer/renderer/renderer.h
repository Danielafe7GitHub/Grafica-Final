#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "vector.h"
#include "object.h"
#include "light.h"
#include "camera.h"

//! the renderer
class renderer {
public:
    //! constructor
    renderer(object **__objects, unsigned long __num, dlight *__dlights,
            unsigned long __num_dlights, plight *__plights, unsigned long __num_plights,
            vector<3> __ambient);

    //! destructor
    ~renderer();

    //! render
    void render(const camera* __camera, unsigned short __w, unsigned short __h, float* __color);

protected:

    //! the scene
    object **_objects;

    //! the number of objects
    unsigned long _num;

    //! ambient light
    vector<3> _ambient;

    //! directional lights
    dlight *_dlights;

    //! the number of directional lights
    unsigned long _num_dlights;

    //! point lights
    plight *_plights;

    //! the number of point lights
    unsigned long _num_plights;

};

#endif
