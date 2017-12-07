#ifndef _EUCLIDEAN_H_
#define _EUCLIDEAN_H_

#include "matrix.h"

//! cofactor
float cofactor(matrix<4, 4> &__r, int __p, int __q);

//! inverts a 4x4 matrix
void invert(matrix<4, 4> &__m);

//! returns the cross product of two 3d vectors
void cross(vector<3> &__a, vector<3> &__b, vector<3> &__c);

//! returns the cross product of two 3d vectors in homogeneus coordinates
void crossh(vector<4> &__a, vector<4> &__b, vector<4> &__c);

#endif
