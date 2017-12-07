#include "object.h"
#include "euclidean.h"
#include <iostream>

// constructor
object::object(matrix<4, 4>& __t, material &__material) {
    _material = __material;
    _t = __t;
    _tinv = _t;
    invert(_tinv);
    _ttransinv = _tinv.transpose();
}
