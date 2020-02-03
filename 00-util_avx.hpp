#ifndef __00_UTIL_AVX_HPP__
#define __00_UTIL_AVX_HPP__

#include <immintrin.h>
#include "00-util.hpp"

template <typename T>
inline T *ALLOC(const int len)
{
  return reinterpret_cast<T *>(_mm_malloc(len * sizeof(T), 32));
}

template <typename T>
inline void FREE(T *p)
{
  if (p != nullptr) _mm_free(p);
}

inline double REDUCE(__m256d rv, bool alt)
{
  auto rvr = _mm256_permute_pd(rv, 5);
  auto red1 = alt ? _mm256_sub_pd(rv, rvr) : _mm256_add_pd(rv, rvr);
  auto hi = _mm256_extractf128_pd(red1, 1);
  auto lo = _mm256_castpd256_pd128(red1);
  auto res = _mm_add_pd(hi, lo);
  return (reinterpret_cast<double *>(&res))[0];
}

inline cd REDUCE(__m128d rv)
{
  return (reinterpret_cast<cd *>(&rv))[0];
}

inline void PRINT(__m256d r)
{
  auto tmp = ALLOC<double>(4);
  _mm256_store_pd(tmp, r);
  for (auto j = 0; j < 4; ++j) std::cout << tmp[j];
  std::cout << std::endl;
  FREE(tmp);
}

inline void PRINT(__m128d r)
{
  auto tmp = ALLOC<double>(2);
  _mm_store_pd(tmp, r);
  for (auto j = 0; j < 2; ++j) std::cout << tmp[j];
  std::cout << std::endl;
  FREE(tmp);
}

#endif // #ifndef __00_UTIL_AVX_HPP__
