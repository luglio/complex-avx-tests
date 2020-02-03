#ifndef __00_UTIL_HPP__
#define __00_UTIL_HPP__

#include <complex>
#include <cmath>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>

using cd = std::complex<double>;

using CLOCK = std::chrono::high_resolution_clock;
using TIMEPOINT = std::chrono::time_point<CLOCK, std::chrono::nanoseconds>;
/* Usage:
 * auto t0 = CLOCK::now();
 * // do something
 * auto t1 = CLOCK::now();
 * auto elp = ELAPSED(t1, t0);
 * result is in nanoseconds (which doesn't mean accuracy in nanoseconds)
 */
inline int64_t ELAPSED(TIMEPOINT t1, TIMEPOINT t0)
{
  return std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
}

inline void SLEEP(const int len)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(len));
}

#endif // #ifndef __00_UTIL_HPP__
