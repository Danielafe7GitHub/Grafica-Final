// contructor
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>::vector() {
    // initialize to 0
    for (register unsigned r = 0; r < _dimension_; r++)
        _v[r] = 0;
}

/*
 // contructor
 template <unsigned short _dimension_, typename _type_>
 vector<_dimension_,_type_>::vector(const _type_ v1, ... )
 {
 std::cerr<<"vector:hxx it is unsafe to use the varparam constructor"<<std::endl;

 // the list
 va_list list;

 //initialize the va_list i.e char*
 // variable 'list' by the address
 // of first unknown variable argument
 // by a call of va_start() macro
 va_start(list,v1);

 // the first position
 _v[0] = v1;

 // initialize to v
 for (register unsigned r=1;r<_dimension_;r++)
 {
 // in loop, retrieve each argument
 // Second argument to va_arg is datatype
 // of expected argument
 _type_ p;
 p = (_type_)va_arg(list,double);
 _v[r] = p;
 }

 // cleanup , set 'lsit' to NULL
 va_end(list);
 }
 */

//! this is ugly!
//! this is ugly!
//! this is ugly!
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>::vector(const _type_ v1, const _type_ v2) {
    _v[0] = v1;
    _v[1] = v2;
}

template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>::vector(const _type_ v1, const _type_ v2, const _type_ v3) {
    _v[0] = v1;
    _v[1] = v2;
    _v[2] = v3;
}

template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>::vector(const _type_ v1, const _type_ v2, const _type_ v3,
        const _type_ v4) {
    _v[0] = v1;
    _v[1] = v2;
    _v[2] = v3;
    _v[3] = v4;
}

// contructor
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>::vector(const _type_ v[_dimension_]) {
    // initialize to v
    for (register unsigned r = 0; r < _dimension_; r++)
        _v[r] = v[r];
}

// contructor
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>::vector(const vector<_dimension_, _type_>& v) {
    // initialize to v
    for (register unsigned r = 0; r < _dimension_; r++)
        _v[r] = v._v[r];
}

// contructor
template<unsigned short _dimension_, typename _type_>
template<unsigned short _dimensionb_, typename _typeb_>
vector<_dimension_, _type_>::vector(const vector<_dimensionb_, _typeb_>& v) {
    // the min
    unsigned short mindim = _dimension_ < _dimensionb_ ? _dimension_ : _dimensionb_;

    // copy
    vector<_dimensionb_, _typeb_> vt = v;

    // initialize to v
    for (register unsigned r = 0; r < mindim; r++)
        _v[r] = vt[r];

    // if remaining fill with 0
    for (register unsigned r = mindim; r < _dimension_; r++)
        _v[r] = 0;
}

// cast operator to a vector of another dimension
template<unsigned short _dimension_, typename _type_>
template<unsigned short _dimensionb_, typename _typeb_>
vector<_dimension_, _type_>::operator vector<_dimensionb_,_typeb_>() {
    return vector<_dimension_, _typeb_>(*this);
}

// cast operator to an array
/*template <unsigned short _dimension_, typename _type_>
 template <typename _typeb_>
 vector<_dimension_,_type_>::operator _typeb_*()
 {
 // the vector
 _typeb_ *rv=new _typeb_[_dimension_];

 // fill
 for (register unsigned r=0;r<_dimension_;r++)
 rv[r]=_v[r];

 // return result
 return rv;
 }*/

// returns an element
template<unsigned short _dimension_, typename _type_>
_type_& vector<_dimension_, _type_>::operator[](const unsigned short i) {
    return _v[i];
}

// returns an element
template<unsigned short _dimension_, typename _type_>
_type_ vector<_dimension_, _type_>::operator[](const unsigned short i) const {
    return _v[i];
}

// assign operator
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>& vector<_dimension_, _type_>::operator=(const vector& v) {
    // initialize to v
    for (register unsigned r = 0; r < _dimension_; r++)
        _v[r] = v._v[r];

    return (*this);
}

// returns the negative of this vector
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_> vector<_dimension_, _type_>::operator-() {
    vector<_dimension_, _type_> v;
    for (register unsigned r = 0; r < _dimension_; r++)
        v[r] = -_v[r];

    return v;
}

// multiplication with a scalar 
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_> vector<_dimension_, _type_>::operator*(const _type_ s) {
    vector<_dimension_, _type_> ve;
    for (register unsigned r = 0; r < _dimension_; r++)
        ve[r] = _v[r] * s;

    return ve;
}

// multiplication with a scalar
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>& vector<_dimension_, _type_>::operator*=(const _type_ s) {
    for (register unsigned r = 0; r < _dimension_; r++)
        _v[r] *= s;

    return (*this);
}

// addition with a scalar
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>& vector<_dimension_, _type_>::operator+=(
        const vector<_dimension_, _type_> &v) {
    for (register unsigned r = 0; r < _dimension_; r++)
        _v[r] += v._v[r];

    return (*this);
}

// substraction with a scalar
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_>& vector<_dimension_, _type_>::operator-=(
        const vector<_dimension_, _type_> &v) {
    for (register unsigned r = 0; r < _dimension_; r++)
        _v[r] -= v._v[r];

    return (*this);
}

// addition with a vector
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_> vector<_dimension_, _type_>::operator+(
        const vector<_dimension_, _type_> &b) {
    vector<_dimension_, _type_> ve;
    for (register unsigned r = 0; r < _dimension_; r++)
        ve[r] = _v[r] + b._v[r];

    return ve;
}

// substraction with a vector
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_> vector<_dimension_, _type_>::operator-(
        const vector<_dimension_, _type_> &b) {
    vector<_dimension_, _type_> ve;
    for (register unsigned r = 0; r < _dimension_; r++)
        ve[r] = _v[r] - b._v[r];

    return ve;
}

// dot product
template<unsigned short _dimension_, typename _type_>
_type_ vector<_dimension_, _type_>::operator*(const vector<_dimension_, _type_> &b) {
    _type_ ve = 0;
    for (register unsigned r = 0; r < _dimension_; r++)
        ve += _v[r] * b._v[r];

    return ve;
}

// minimum
template<unsigned short _dimension_, typename _type_>
_type_ vector<_dimension_, _type_>::min() {
    unsigned short ve = 0;
    for (register unsigned r = 1; r < _dimension_; r++)
        if (_v[r] < _v[ve])
            ve = r;

    return _v[ve];
}

// maximum
template<unsigned short _dimension_, typename _type_>
_type_ vector<_dimension_, _type_>::max() {
    unsigned short ve = 0;
    for (register unsigned r = 1; r < _dimension_; r++)
        if (_v[r] > _v[ve])
            ve = r;

    return _v[ve];
}

// norm L2
template<unsigned short _dimension_, typename _type_>
_type_ vector<_dimension_, _type_>::norm() {
    _type_ ve = 0;
    for (register unsigned r = 0; r < _dimension_; r++)
        ve += _v[r] * _v[r];

    return sqrt(ve);
}

// norm
template<unsigned short _dimension_, typename _type_>
void vector<_dimension_, _type_>::normalize() {
    _type_ nrm = norm();
    for (register unsigned r = 0; r < _dimension_; r++)
        _v[r] /= nrm;
}

// normalized vector 
template<unsigned short _dimension_, typename _type_>
vector<_dimension_, _type_> vector<_dimension_, _type_>::normalized() {
    vector<_dimension_, _type_> nv = (*this);
    nv.normalize();

    return nv;
}

// norm Linf
template<unsigned short _dimension_, typename _type_>
_type_ vector<_dimension_, _type_>::normlinf() {
    _type_ ve = 0;
    for (register unsigned r = 0; r < _dimension_; r++)
        ve += _v[r];

    return ve;
}

