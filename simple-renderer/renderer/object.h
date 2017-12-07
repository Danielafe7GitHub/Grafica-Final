#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "matrix.h"
#include "camera.h"
#include "light.h"

//! the material 
struct material {
    vector<4> _color;
    float _shininness;
    float _reflective;
    float _refractive;
    float _ior;
};

//! the virtual class for the objects in the scene
class object {
protected:
    //! the transformation matrix
    matrix<4, 4> _t;

    //! the inverse of the transformation matrix
    matrix<4, 4> _tinv;

    //! the transpose of the inverse of the transformation matrix
    matrix<4, 4> _ttransinv;

    //! the material
    material _material;

public:
    //! constructor
    object(matrix<4, 4>& __t, material &__material);

    //! desconstructor
    virtual ~object() {
    }

    //! rasterize
    virtual bool rasterize(camera* __camera, unsigned short __w, unsigned short __h,
            vector<3> __ambient, dlight *__dlights, unsigned long __num_dlights, plight *__plights,
            unsigned long __num_plights, float*& __color_buffer, float*& __depth_buffer)=0;
};

#endif
