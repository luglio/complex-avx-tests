#ifndef __00_UTIL_HPP__
#define __00_UTIL_HPP__

#include <immintrin.h>
#include <complex>
#include <cmath>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>

using cd = std::complex<double>;

template <typename T>
T *ALLOC(const int len)
{
  return reinterpret_cast<T *>(_mm_malloc(len * sizeof(T), 32));
}

template <typename T>
void FREE(T *p)
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

using CLOCK = std::chrono::high_resolution_clock;
using TIMEPOINT = std::chrono::time_point<CLOCK, std::chrono::nanoseconds>;
/* Usage:
 * auto t0 = CLOCK::now();
 * // do something
 * auto t1 = CLOCK::now();
 * auto elp = ELAPSED(t1, t0);
 * result is in nanoseconds (which doesn't mean accuracy in nanoseconds)
 */
int64_t ELAPSED(TIMEPOINT t1, TIMEPOINT t0)
{
  return std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
}

inline void SLEEP(const int len)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(len));
}

void PRINT(__m256d r)
{
  auto tmp = ALLOC<double>(4);
  _mm256_store_pd(tmp, r);
  for (auto j = 0; j < 4; ++j) std::cout << tmp[j];
  std::cout << std::endl;
  FREE(tmp);
}

void PRINT(__m128d r)
{
  auto tmp = ALLOC<double>(2);
  _mm_store_pd(tmp, r);
  for (auto j = 0; j < 2; ++j) std::cout << tmp[j];
  std::cout << std::endl;
  FREE(tmp);
}

#endif // #ifndef __00_UTIL_HPP__
