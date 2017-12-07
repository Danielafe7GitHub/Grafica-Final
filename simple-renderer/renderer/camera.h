#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"

//! the camera
class camera {
public:
    //! constructor
    camera(float __fovy, vector<4> __pos, vector<4> __dir, vector<4> __up);

    //! constructor
    camera(float __fovy = 60);

    //! get direction
    vector<4>& dir();

    //! get origin
    vector<4>& pos();

    //! get up
    vector<4>& up();

    //! get right
    vector<4>& right();

    //! get fovy
    float& fovy();

    //! translate x (view plane)
    void translatex(float __d);

    //! translate y (view plane)
    void translatey(float __d);

    //! translate z (view plane)
    void translatez(float __d);

    //! rotate x (world)
    void rotatex(float __d);

    //! rotate y (world)
    void rotatey(float __d);

    //! rotate z (world)
    void rotatez(float __d);

    //! rotate
    void rotate(float __d, vector<4>& __axis);

    //! calculate right vector
    void calc_right();

protected:
    //! position
    vector<4> _pos;

    //! direction
    vector<4> _dir;

    //! up
    vector<4> _up;

    //! right
    vector<4> _right;

    //! fovy
    float _fovy;
};

#endif
