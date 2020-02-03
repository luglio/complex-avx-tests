#ifndef __01_DOT_HPP__
#define __01_DOT_HPP__
#include "00-util.hpp"

// AVX
cd dot_avx(const cd *vec1, const cd *vec2, const int len);
cd dot_avx(const cd *vec1, const double *vec2, const int len);

// non-AVX
cd dot(const cd *vec1, const cd *vec2, const int len);
cd dot(const cd *vec1, const double *vec2, const int len);

#endif // #ifndef __01_DOT_HPP__
