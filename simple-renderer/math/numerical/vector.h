#ifndef _THOTH_VECTOR_H_
#define _THOTH_VECTOR_H_

// stl includes
#include <cmath>
#include <iostream>
#include <string>

// c includes
#include <stdarg.h>
#include <stdio.h>
#include <typeinfo> 

// check if min and max were defined
#ifdef min 
#undef min
#undef max
#endif

// the thoth namespace
//namespace thoth
//{

//! the n-dimensional vector class
template<unsigned short _dimension_, typename _type_ = float>
class vector {
protected:
    //! the vector
    _type_ _v[_dimension_];

public:
    //! typedef the type
    typedef _type_ type;

    //! contructor
    vector();

    //! contructor
    vector(const _type_ v[_dimension_]);

    //! contructor
    // vector(const _type_,...);

    //! this is ugly!
    //! this is ugly!
    //! this is ugly!
    vector(const _type_ v1, const _type_ v2);
    vector(const _type_ v1, const _type_ v2, const _type_ v3);
    vector(const _type_ v1, const _type_ v2, const _type_ v3, const _type_ v4);

    //! contructor
    vector(const vector<_dimension_, _type_>& v);

    //! contructor
    template<unsigned short _dimensionb_, typename _typeb_>
    vector(const vector<_dimensionb_, _typeb_>& v);

    //! returns an element
    _type_& operator[](const unsigned short i);

    //! returns an element
    _type_ operator[](const unsigned short i) const;

    //! assign operator
    vector<_dimension_, _type_>& operator=(const vector<_dimension_, _type_> & v);

    //! returns the negative of this vector
    vector<_dimension_, _type_> operator-();

    //! multiplication with a scalar
    vector<_dimension_, _type_> operator*(const _type_ s);

    //! multiplication with a scalar
    vector<_dimension_, _type_>& operator*=(const _type_ s);

    //! addition with a scalar
    vector<_dimension_, _type_>& operator+=(const vector<_dimension_, _type_> &v);

    //! substraction with a scalar
    vector<_dimension_, _type_>& operator-=(const vector<_dimension_, _type_> &v);

    //! addition with a vector
    vector<_dimension_, _type_> operator+(const vector<_dimension_, _type_> &b);

    //! substraction with a vector
    vector<_dimension_, _type_> operator-(const vector<_dimension_, _type_> &b);

    //! dot product
    _type_ operator*(const vector<_dimension_, _type_> &b);

    //! cast operator to a vector of another dimension
    template<unsigned short _dimensionb_, typename _typeb_>
    operator vector<_dimensionb_,_typeb_>();

    //! cast operator to an array
    // template <typename _typeb_>
    // operator _typeb_*();

    //! minimum
    _type_ min();

    //! maximum
    _type_ max();

    //! norm L2
    _type_ norm();

    //! normalize
    void normalize();

    //! normalized vector
    vector<_dimension_, _type_> normalized();

    //! norm Linf
    _type_ normlinf();
};

// implementation
#include "vector.hxx"

// end of namespace
//};

#endif

