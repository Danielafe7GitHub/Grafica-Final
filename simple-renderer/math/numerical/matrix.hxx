// constructor
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>::matrix() {
}

// constructor
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>::matrix(const vector<_cols_, _type_> v[_rows_]) {
    for (register unsigned short i = 0; i < _rows_; i++)
        _v[i] = v[i];
}

// constructor
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>::matrix(const matrix &v) {
    for (register unsigned short i = 0; i < _rows_; i++)
        _v[i] = v._v[i];
}

// contructor
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>::matrix(const _type_* v) {
    for (register unsigned r = 0; r < _rows_; r++)
        for (register unsigned c = 0; c < _cols_; c++)
            _v[r][c] = v[_cols_ * r + c];

}

//! this is ugly
//! this is ugly
//! this is ugly
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>::matrix(const _type_ m00, const _type_ m01, const _type_ m02,
        const _type_ m10, const _type_ m11, const _type_ m12, const _type_ m20, const _type_ m21,
        const _type_ m22) {
    _v[0][0] = m00;
    _v[0][1] = m01;
    _v[0][2] = m02;
    _v[1][0] = m10;
    _v[1][1] = m11;
    _v[1][2] = m12;
    _v[2][0] = m20;
    _v[2][1] = m21;
    _v[2][2] = m22;
}

template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>::matrix(const _type_ m00, const _type_ m01, const _type_ m02,
        const _type_ m03, const _type_ m10, const _type_ m11, const _type_ m12, const _type_ m13,
        const _type_ m20, const _type_ m21, const _type_ m22, const _type_ m23, const _type_ m30,
        const _type_ m31, const _type_ m32, const _type_ m33) {
    _v[0][0] = m00;
    _v[0][1] = m01;
    _v[0][2] = m02;
    _v[0][3] = m03;
    _v[1][0] = m10;
    _v[1][1] = m11;
    _v[1][2] = m12;
    _v[1][3] = m13;
    _v[2][0] = m20;
    _v[2][1] = m21;
    _v[2][2] = m22;
    _v[2][3] = m23;
    _v[3][0] = m30;
    _v[3][1] = m31;
    _v[3][2] = m32;
    _v[3][3] = m33;
}

/*
 // contructor
 template <unsigned short _rows_, unsigned short _cols_, typename _type_>
 matrix<_rows_,_cols_,_type_>::matrix(const _type_ v1, ... )
 {
 std::cerr<<"matrix:hxx it is unsafe to use the varparam constructor"<<std::endl;

 // the list
 va_list list;

 //initialize the va_list i.e char*
 // variable 'list' by the address
 // of first unknown variable argument
 // by a call of va_start() macro
 va_start(list,v1);

 // the first position
 _v[0][0]=v1;

 // initialize to v
 for (register unsigned c=1;c<_cols_;c++)
 {
 // in loop, retrieve each argument
 // Second argument to va_arg is datatype
 // of expected argument
 _type_ p;
 p=(_type_)va_arg(list,double);
 _v[0][c]=p;
 }

 for (register unsigned r=1;r<_rows_;r++)
 for (register unsigned c=0;c<_cols_;c++)
 {
 // in loop, retrieve each argument
 // Second argument to va_arg is datatype
 // of expected argument
 _type_ p;
 p=(_type_)va_arg(list,double);
 _v[r][c]=p;
 }

 // cleanup , set 'lsit' to NULL
 va_end(list);
 }
 */

// returns a row
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
vector<_cols_, _type_>& matrix<_rows_, _cols_, _type_>::operator[](const unsigned short r) {
    return _v[r];
}

// returns a row
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
vector<_cols_, _type_> matrix<_rows_, _cols_, _type_>::operator[](const unsigned short r) const {
    return _v[r];
}

// assignment
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>& matrix<_rows_, _cols_, _type_>::operator=(const matrix &v) {
    for (register unsigned short i = 0; i < _rows_; i++)
        _v[i] = v._v[i];

    return (*this);
}

// multiply with transpose
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
vector<_cols_, _type_> matrix<_rows_, _cols_, _type_>::multiply_by_its_transpose(
        vector<_rows_, _type_> &b) {
    vector<_cols_, _type_> m;
    for (register unsigned short i = 0; i < _cols_; i++)
        for (register unsigned short j = 0; j < _rows_; j++)
            m[i] += _v[j][i] * b[j];
    return m;
}

// returns the negative matrix
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_> matrix<_rows_, _cols_, _type_>::operator-() {
    matrix<_rows_, _cols_, _type_> m;
    for (register unsigned short i = 0; i < _rows_; i++)
        m[i] = -_v[i];
    return m;
}

// addition
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>& matrix<_rows_, _cols_, _type_>::operator+=(const matrix &v) {
    for (register unsigned short i = 0; i < _rows_; i++)
        _v[i] += v._v[i];
    return (*this);
}

// substraction
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>& matrix<_rows_, _cols_, _type_>::operator-=(const matrix &v) {
    for (register unsigned short i = 0; i < _rows_; i++)
        _v[i] -= v._v[i];
    return (*this);
}

// multiplication with a scalar
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_>& matrix<_rows_, _cols_, _type_>::operator*=(const _type_ s) {
    for (register unsigned short i = 0; i < _rows_; i++)
        _v[i] *= s;
    return (*this);
}

// transpose
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_cols_, _rows_, _type_> matrix<_rows_, _cols_, _type_>::transpose() {
    matrix<_cols_, _rows_, _type_> m;
    for (register unsigned short i = 0; i < _rows_; i++)
        for (register unsigned short j = 0; j < _cols_; j++)
            m[j][i] = _v[i][j];
    return m;
}

// multiplication with a scalar
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_> matrix<_rows_, _cols_, _type_>::operator*(const _type_ s) {
    matrix<_rows_, _cols_, _type_> m;
    for (register unsigned short i = 0; i < _rows_; i++)
        m[i] = _v[i] * s;
    return m;
}

// multiplication with a vector
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
vector<_rows_, _type_> matrix<_rows_, _cols_, _type_>::operator*(const vector<_cols_, _type_> &b) {
    vector<_rows_, _type_> m;
    for (register unsigned short i = 0; i < _rows_; i++)
        m[i] = _v[i] * b;
    return m;
}

// addition with a matrix
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_> matrix<_rows_, _cols_, _type_>::operator+(
        const matrix<_rows_, _cols_, _type_> &b) {
    matrix<_rows_, _cols_, _type_> m;
    for (register unsigned short i = 0; i < _rows_; i++)
        m[i] = _v[i] + b._v[i];
    return m;
}

// substraction with a matrix
template<unsigned short _rows_, unsigned short _cols_, typename _type_>
matrix<_rows_, _cols_, _type_> matrix<_rows_, _cols_, _type_>::operator-(
        const matrix<_rows_, _cols_, _type_> &b) {
    matrix<_rows_, _cols_, _type_> m;
    for (register unsigned short i = 0; i < _rows_; i++)
        m[i] = _v[i] - b._v[i];
    return m;
}

// multiplication with a matrix
template<unsigned short _rowsa_, unsigned short _colsa_, unsigned short _colsb_, typename _type_>
matrix<_rowsa_, _colsb_, _type_> operator*(const matrix<_rowsa_, _colsa_, _type_> &a,
        const matrix<_colsa_, _colsb_, _type_> &b) {
    matrix<_rowsa_, _colsa_, _type_> ta = a;
    matrix<_colsa_, _colsb_, _type_> ttb = b;
    matrix<_colsb_, _colsa_, _type_> tb = ttb.transpose();

    matrix<_rowsa_, _colsb_, _type_> m;
    for (register unsigned short i = 0; i < _rowsa_; i++)
        for (register unsigned short j = 0; j < _colsb_; j++)
            m[i][j] = ta[i] * tb[j];
    return m;
}

// multiplication of a vector with a matrix
template<unsigned short _rowsa_, unsigned short _colsa_, typename _type_>
vector<_colsa_, _type_> operator*(const vector<_rowsa_, _type_> &v,
        const matrix<_rowsa_, _colsa_, _type_> &m) {
    vector<_rowsa_, _type_> tv = v;
    matrix<_rowsa_, _colsa_, _type_> tm = m;

    vector<_colsa_, _type_> r;
    for (register unsigned short j = 0; j < _colsa_; j++)
        for (register unsigned short i = 0; i < _rowsa_; i++)
            r[j] += tv[i] * tm[i][j];

    return r;
}

// multiplication with of two vectors (transposed)
template<unsigned short _dima_, unsigned short _dimb_, typename _type_>
matrix<_dima_, _dimb_, _type_> operator^(const vector<_dima_, _type_> &a,
        const vector<_dimb_, _type_> &b) {
    vector<_dima_, _type_> ta = a;
    vector<_dima_, _type_> tb = b;

    matrix<_dima_, _dimb_, _type_> m;
    for (register unsigned short i = 0; i < _dima_; i++)
        for (register unsigned short j = 0; j < _dimb_; j++)
            m[i][j] = ta[i] * tb[j];
    return m;
}
