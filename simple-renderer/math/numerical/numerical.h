#ifndef _NUMERICAL_H_
#define _NUMERICAL_H_

//! conjugate gradients
template<typename _matrix_, typename _vector_>
bool conjugate_gradient(unsigned short __iterations, float __epsilon, _matrix_ &__m, _vector_ &__b,
        _vector_ &__x);

// implementation
#include "numerical.hxx"

#endif
