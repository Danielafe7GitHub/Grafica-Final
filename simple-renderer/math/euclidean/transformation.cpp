#include "transformation.h"

// constructor 
transformation::transformation() {
    _matrix[0][0] = _matrix[1][1] = _matrix[2][2] = _matrix[3][3] = 1.0;
}

// translate 
void transformation::translate(vector<3> &__d) {
    matrix<4, 4> __translation;
    __translation[0][0] = __translation[1][1] = __translation[2][2] = 1.f;
    __translation[0][3] = __d[0];
    __translation[1][3] = __d[1];
    __translation[2][3] = __d[2];
    __translation[3][3] = 1.f;

    _matrix = __translation * _matrix;
}

// return the transformation
matrix<4, 4> transformation::t() {
    return _matrix;
}

// rotate 
void transformation::rotate(float __d, vector<3> &__axis) {
    __d *= 0.01745f;
    matrix<4, 4> __rotation;
    __rotation[3][3] = 1;
    __rotation[0][0] = cosf(__d) + (1.f - cosf(__d)) * __axis[0] * __axis[0];
    __rotation[0][1] = (1 - cosf(__d)) * __axis[0] * __axis[1] - sinf(__d) * __axis[2];
    __rotation[0][2] = (1 - cosf(__d)) * __axis[0] * __axis[2] + sinf(__d) * __axis[1];

    __rotation[1][0] = (1 - cosf(__d)) * __axis[0] * __axis[1] + sinf(__d) * __axis[2];
    __rotation[1][1] = cosf(__d) + (1.f - cosf(__d)) * __axis[1] * __axis[1];
    __rotation[1][2] = (1 - cosf(__d)) * __axis[1] * __axis[2] - sinf(__d) * __axis[0];

    __rotation[2][0] = (1 - cosf(__d)) * __axis[0] * __axis[2] - sinf(__d) * __axis[1];
    __rotation[2][1] = (1 - cosf(__d)) * __axis[1] * __axis[2] + sinf(__d) * __axis[0];
    __rotation[2][2] = cosf(__d) + (1.f - cosf(__d)) * __axis[2] * __axis[2];

    _matrix = __rotation * _matrix;
}

// translate 
void transformation::scale(vector<3> &__d) {
    matrix<4, 4> __translation;
    __translation[0][0] = __d[0];
    __translation[1][1] = __d[1];
    __translation[2][2] = __d[2];
    __translation[3][3] = 1.f;

    _matrix = __translation * _matrix;
}

// apply 
void transformation::apply(vector<4> &__d) {
    __d = _matrix * __d;
}

// multiply with transformation matrix
void transformation::transform(transformation &__trans) {
    _matrix = __trans.t() * _matrix;
}

// multiply with transformation matrix
void transformation::transform(matrix<4, 4> &__trans) {
    _matrix = __trans * _matrix;
}
