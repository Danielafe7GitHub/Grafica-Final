#include "euclidean.h"

// cofactor
float cofactor(matrix<4, 4> &__r, int __p, int __q) {
    // temp
    unsigned int __m[3];
    unsigned int __n[3];

    // assert
    // assert(/*(0 <= p) &&*/ (p < 4) && /*(0 <= q) &&*/ (q < 4));

    // the index
    for (int __i = 0, __j = 0; __i < 4; ++__i)
        if (__i != __p)
            __m[__j++] = __i;
    for (int __i = 0, __j = 0; __i < 4; ++__i)
        if (__i != __q)
            __n[__j++] = __i;

    return ((__p + __q) % 2 ? -1 : 1)
            * (__r[__m[0]][__n[0]]
            * (__r[__m[1]][__n[1]] * __r[__m[2]][__n[2]]
            - __r[__m[1]][__n[2]] * __r[__m[2]][__n[1]])
            - __r[__m[0]][__n[1]]
            * (__r[__m[1]][__n[0]] * __r[__m[2]][__n[2]]
            - __r[__m[1]][__n[2]] * __r[__m[2]][__n[0]])
            + __r[__m[0]][__n[2]]
            * (__r[__m[1]][__n[0]] * __r[__m[2]][__n[1]]
            - __r[__m[1]][__n[1]] * __r[__m[2]][__n[0]]));
}

// inverts a 4x4 matrix
void invert(matrix<4, 4> &__m) {
    matrix<4, 4> __cofft;

    // This method can potentially overflow, but is more stable than a
    // Gaussian inversion.  A workarround would be to multiply the
    // entire matrix by 1/det^(1/12) but that means I'd need to compute
    // the determinant /before/ computing the cofactors.  This wouldn't
    // be terribly difficult using levi-civita symbols, but this will
    // have to do for now because the intended use for this class is
    // mainly affine transformations which should pose such problems
    // only in degenerate cases.

    for (int __i = 0; __i < 4; ++__i)
        for (int __j = 0; __j < 4; ++__j)
            __cofft[__j][__i] = cofactor(__m, __i, __j);

    float __det = __m[0][0] * __cofft[0][0] + __m[0][1] * __cofft[1][0]
            + __m[0][2] * __cofft[2][0] + __m[0][3] * __cofft[3][0];

    // FIXME: DANGER WILL ROBINSON! This doesn't care if the matrix is
    // singular or not! (It probably doesn't do a terribly good job
    // with integers or complex numbers either)

    __m = __cofft * (1.f / __det);
}

// returns the cross product of two 3d vectors
void cross(vector<3> &__a, vector<3> &__b, vector<3> &__c) {
    __c[0] = __a[1] * __b[2] - __a[2] * __b[1];
    __c[1] = __a[2] * __b[0] - __a[0] * __b[2];
    __c[2] = __a[0] * __b[1] - __a[1] * __b[0];
}

// returns the cross product of two 3d vectors in homogeneus coordinates
void crossh(vector<4> &__a, vector<4> &__b, vector<4> &__c) {
    __c[0] = __a[1] * __b[2] - __a[2] * __b[1];
    __c[1] = __a[2] * __b[0] - __a[0] * __b[2];
    __c[2] = __a[0] * __b[1] - __a[1] * __b[0];
    __c[3] = 0.f;
}
