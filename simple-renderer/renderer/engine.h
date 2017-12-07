#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "viewport.h"
#include "renderer.h"
#include "object.h"
#include "triangle.h"
#include "matrix.h"
#include "camera.h"
#include "light.h"
#include <string>
#include <deque>

//! the size of the viewport
#define WIDTH	600
#define HEIGHT	400

//! the ray-tracer
class engine {
public:
    //! constructor
    engine(std::string __scene_file, unsigned short __width = WIDTH, unsigned short __height =
            HEIGHT);

    //! destructor
    ~engine();

    //! add point light
    void add_point_light(plight *__light);

    //! add directional light
    void add_directional_light(dlight *__light);

    //! add object
    void add_object(object *__object);

    //! set background color
    vector<3>& backgroud_color();

    //! ambient light
    vector<3>& ambient();

    //! camera
    camera& cam();

    //! run ray-tracer
    int run();

protected:
    //! the list of objects
    std::deque<object*> _objects;

    //! the list of point lights
    std::deque<plight*> _plights;

    //! the list of directional lights
    std::deque<dlight*> _dlights;

    //! ambient light
    vector<3> _ambient;

    //! the viewport width
    unsigned short _width;

    //! the viewport height
    unsigned short _height;

    //! the camera
    camera _camera;

    //! the background color
    vector<3> _bcolor;
};

#endif
