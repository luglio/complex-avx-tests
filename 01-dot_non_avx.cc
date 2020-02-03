#include "00-util.hpp"
#include "01-dot.hpp"

cd dot(const cd *vec1, const cd *vec2, const int len)
{
  cd res{0.0, 0.0};
  for (auto j = 0; j < len; ++j) res += vec1[j] * vec2[j];
  return res;
}

cd dot(const cd *vec1, const double *vec2, const int len)
{
  cd res{0.0, 0.0};
  for (auto j = 0; j < len; ++j) res += vec1[j] * vec2[j];
  return res;
}
