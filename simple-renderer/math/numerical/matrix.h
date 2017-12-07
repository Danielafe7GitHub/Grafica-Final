#ifndef _THOTH_MATRIX_H_
#define _THOTH_MATRIX_H_

// stl includes
#include <iostream>
#include <cmath>

// thoth includes
#include "vector.h"

// the thoth namespace
//namespace thoth
//{

//! the matrix class
template<unsigned short _rows_, unsigned short _cols_, typename _type_ = float>
class matrix {
protected:
    //! the matrix
    vector<_cols_, _type_> _v[_rows_];

public:
    //! constructor
    matrix();

    //! constructor
    matrix(const vector<_cols_, _type_> v[_rows_]);

    //! constructor
    matrix(const matrix<_rows_, _cols_, _type_> &v);

    //! contructor
    // matrix(const _type_,...);

    //! this is ugly
    //! this is ugly
    //! this is ugly
    matrix(const _type_ m00, const _type_ m01, const _type_ m02, const _type_ m10, const _type_ m11,
            const _type_ m12, const _type_ m20, const _type_ m21, const _type_ m22);
    matrix(const _type_ m00, const _type_ m01, const _type_ m02, const _type_ m03, const _type_ m10,
            const _type_ m11, const _type_ m12, const _type_ m13, const _type_ m20,
            const _type_ m21, const _type_ m22, const _type_ m23, const _type_ m30,
            const _type_ m31, const _type_ m32, const _type_ m33);

    //! contructor
    matrix(const _type_* v);

    //! returns a row
    vector<_cols_, _type_>& operator[](const unsigned short r);

    //! returns a row
    vector<_cols_, _type_> operator[](const unsigned short r) const;

    //! assignment
    matrix<_rows_, _cols_, _type_>& operator=(const matrix<_rows_, _cols_, _type_> &v);

    //! returns the negative matrix
    matrix<_rows_, _cols_, _type_> operator-();

    //! addition
    matrix<_rows_, _cols_, _type_>& operator+=(const matrix<_rows_, _cols_, _type_> &v);

    //! substraction
    matrix<_rows_, _cols_, _type_>& operator-=(const matrix<_rows_, _cols_, _type_> &v);

    //! multiplication with a scalar
    matrix<_rows_, _cols_, _type_>& operator*=(const _type_ s);

    //! transpose
    matrix<_cols_, _rows_, _type_> transpose();

    //! multiplication with a scalar
    matrix<_rows_, _cols_, _type_> operator*(const _type_ b);

    //! multiplication with a vector
    vector<_rows_, _type_> operator*(const vector<_cols_, _type_> &b);

    //! addition with a matrix
    matrix<_rows_, _cols_, _type_> operator+(const matrix<_rows_, _cols_, _type_> &b);

    //! substraction with a matrix
    matrix<_rows_, _cols_, _type_> operator-(const matrix<_rows_, _cols_, _type_> &b);

    //! with transpose
    vector<_cols_, _type_> multiply_by_its_transpose(vector<_rows_, _type_> &b);
};

//! multiplication with a matrix
template<unsigned short _rowsa_, unsigned short _colsa_, unsigned short _colsb_, typename _type_>
matrix<_rowsa_, _colsb_, _type_> operator*(const matrix<_rowsa_, _colsa_, _type_> &a,
        const matrix<_colsa_, _colsb_, _type_> &b);

//! multiplication of a vector with a matrix
template<unsigned short _rowsa_, unsigned short _colsa_, typename _type_>
vector<_colsa_, _type_> operator*(const vector<_rowsa_, _type_> &v,
        const matrix<_rowsa_, _colsa_, _type_> &m);

//! multiplication of two vectors (transposed)
template<unsigned short _dima_, unsigned short _dimb_, typename _type_>
matrix<_dima_, _dimb_, _type_> operator^(const vector<_dima_, _type_> &a,
        const vector<_dimb_, _type_> &b);

// implementation
#include "matrix.hxx"

// end of namespace
//};

#endif 
