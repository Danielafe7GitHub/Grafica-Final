#include "camera.h"
#include "matrix.h"
#include <iostream>
#include "euclidean.h"

// constructor 
camera::camera(float __fovy) :
        _fovy(__fovy) {
    _pos[0] = 0.0;
    _pos[1] = 0.0;
    _pos[2] = 20.0;
    _pos[3] = 1.0;
    _dir[0] = 0.0;
    _dir[1] = 0.0;
    _dir[2] = -1.0;
    _dir[3] = 0.0;
    _up[0] = 0.0;
    _up[1] = 1.0;
    _up[2] = 0.0;
    _up[3] = 0.0;
    _right[0] = 1.0;
    _right[1] = 0.0;
    _right[2] = 0.0;
    _right[3] = 0.0;
}

// constructor 
camera::camera(float __fovy, vector<4> __pos, vector<4> __dir, vector<4> __up) :
        _fovy(__fovy) {
    _pos = __pos;
    _dir = __dir;
    _up = __up;
    crossh(_dir, _up, _right);
    _right.normalize();
    crossh(_right, _dir, _up);
    _up.normalize();
}

// get direction
vector<4>& camera::dir() {
    return _dir;
}

// get origin
vector<4>& camera::pos() {
    return _pos;
}

// get up
vector<4>& camera::up() {
    return _up;
}

// get right
vector<4>& camera::right() {
    return _right;
}

// translate x (view plane)
void camera::translatex(float __d) {
    _pos += _right * __d;
}

// translate y (view plane)
void camera::translatey(float __d) {
    _pos += _up * __d;
}

// translate z (view plane)
void camera::translatez(float __d) {
    _pos += _dir * __d;
}

// rotate 
void camera::rotate(float __d, vector<4>& __axis) {
    matrix<4, 4> __rotation;
    __d *= 0.01745f;

    __rotation[0][0] = cosf(__d) + (1.f - cosf(__d)) * __axis[0] * __axis[0];
    __rotation[0][1] = (1 - cosf(__d)) * __axis[0] * __axis[1] - sinf(__d) * __axis[2];
    __rotation[0][2] = (1 - cosf(__d)) * __axis[0] * __axis[2] + sinf(__d) * __axis[1];

    __rotation[1][0] = (1 - cosf(__d)) * __axis[0] * __axis[1] + sinf(__d) * __axis[2];
    __rotation[1][1] = cosf(__d) + (1.f - cosf(__d)) * __axis[1] * __axis[1];
    __rotation[1][2] = (1 - cosf(__d)) * __axis[1] * __axis[2] - sinf(__d) * __axis[0];

    __rotation[2][0] = (1 - cosf(__d)) * __axis[0] * __axis[2] - sinf(__d) * __axis[1];
    __rotation[2][1] = (1 - cosf(__d)) * __axis[1] * __axis[2] + sinf(__d) * __axis[0];
    __rotation[2][2] = cosf(__d) + (1.f - cosf(__d)) * __axis[2] * __axis[2];

    __rotation[3][3] = 1.0;

    _pos = __rotation * _pos;
    _dir = __rotation * _dir;
    _up = __rotation * _up;
    crossh(_dir, _up, _right);
    _right.normalize();
    _dir.normalize();
    _up.normalize();
}

// rotate x (world)
void camera::rotatex(float __d) {
    rotate(__d, _right);
}

// rotate y (world)
void camera::rotatey(float __d) {
    rotate(__d, _up);
}

// rotate z (world)
void camera::rotatez(float __d) {
    rotate(__d, _dir);
}

// get fovy
float& camera::fovy() {
    return _fovy;
}

// calculate right vector
void camera::calc_right() {
    crossh(_dir, _up, _right);
    _right.normalize();
    crossh(_right, _dir, _up);
    _up.normalize();
}
