//! conjugate gradients
template<typename _matrix_, typename _vector_>
bool conjugate_gradient(unsigned short __iterations, float __epsilon, _matrix_ &__m, _vector_ &__b,
        _vector_ &__x) {
    float __eps2 = __epsilon * __epsilon;                           // the error
    int __i = 0;                                                    // current iteration
    _vector_ __r = __b - __m * __x;                                 // rest
    _vector_ __d = __r;                                             // d
    float __ndelta = __r * __r;                                     // new delta
    float __fdelta = __ndelta;                                      // first delta
    while (__i < __iterations && __ndelta > (__eps2 * __fdelta))    // iterate
    {
        _vector_ __q = __m * __d;                                   // q
        float __tt = __d * __q;                                     // dot product
        if (__tt == 0)
            return false;                                           // check for division by 0
        float __alpha = __ndelta / __tt;                            // \alpha
        __x = __x + __d * __alpha;                                  // move the solution

        if (__i % 50 == 0)                                          // a correction (Shewchuk)
            __r = __b - __m * __x;
        else
            __r = __r - __q * __alpha;

        float __odelta = __ndelta;                                  // the old delta
        __ndelta = __r * __r;                                       // the new delta
        float __beta = __ndelta / __odelta;                         // beta
        __d = __r + __d * __beta;                                   // new d
        __i++;                                                      // next iteration
    }
    return true;
}
