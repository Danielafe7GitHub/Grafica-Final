#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

#include "matrix.h"

//! the transformation
class transformation {
public:
    //! constructor
    transformation();

    //! translate
    void translate(vector<3> &__d);

    //! rotate
    void rotate(float __d, vector<3> &__axis);

    //! scale
    void scale(vector<3> &__d);

    //! multiply with transformation matrix
    void transform(transformation &__trans);

    //! multiply with transformation matrix
    void transform(matrix<4, 4> &__trans);

    //! apply
    void apply(vector<4> &__x);

    //! return the transformation
    matrix<4, 4> t();

protected:
    //! position
    matrix<4, 4> _matrix;
};

#endif
