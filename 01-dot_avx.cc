#include "00-util_avx.hpp"
#include "01-dot.hpp"

cd dot_avx(const cd *vec1, const cd *vec2, const int len)
{
  auto dv1 = reinterpret_cast<const double *>(vec1);
  auto dv2 = reinterpret_cast<const double *>(vec2);
  auto rr = _mm256_setzero_pd();
  auto ri = _mm256_setzero_pd();
  for (auto j = 0; j < len / 2; ++j)
  {
    auto r1 = _mm256_load_pd(dv1 + j * 4); // [a0 b0 a1 b1]
    auto r2 = _mm256_load_pd(dv2 + j * 4); // [c0 d0 c1 d1]
    auto r2r = _mm256_permute_pd(r2, 5);   // [d0 c0 d1 c1]
    rr = _mm256_fmadd_pd(r1, r2, rr);
    ri = _mm256_fmadd_pd(r1, r2r, ri);
  }
  auto r = REDUCE(rr, true);
  auto i = REDUCE(ri, false);
  cd res{r, i};
  if (len % 2 == 1)
  {
    res += vec1[len - 1] * vec2[len - 1];
  }
  return res;
}

cd dot_avx(const cd *vec1, const double *vec2, const int len)
{
  auto dv1 = reinterpret_cast<const double *>(vec1);
  auto res1 = _mm256_setzero_pd();
  auto res2 = _mm256_setzero_pd();
  for (auto j = 0; j < len / 4; ++j)
  {
    auto r1 = _mm256_load_pd(dv1 + j * 8);     // [a0 b0 a1 b1]
    auto r2 = _mm256_load_pd(dv1 + j * 8 + 4); // [a2 b2 a3 b3]
    auto rd = _mm256_load_pd(vec2 + j * 4);    // [x0 x1 x2 x3]
    auto rdp = _mm256_permute4x64_pd(rd, 216); // [x0 x2 x1 x3]
    auto rdq = _mm256_permute_pd(rdp, 5);      // [x2 x0 x3 x1]
    auto rd1 = _mm256_movedup_pd(rdp);         // [x0 x0 x1 x1]
    auto rd2 = _mm256_movedup_pd(rdq);         // [x2 x2 x3 x3]
    res1 = _mm256_fmadd_pd(r1, rd1, res1);
    res2 = _mm256_fmadd_pd(r2, rd2, res2);
  }
  auto res = _mm256_add_pd(res1, res2);
  auto rhi = _mm256_extractf128_pd(res, 1);
  auto rlo = _mm256_castpd256_pd128(res);
  auto rsm = _mm_add_pd(rhi, rlo);
  auto cres = REDUCE(rsm);
  for (auto j = len - len % 4; j < len; ++j)
  {
    cres += vec1[j] * vec2[j];
  }
  return cres;
}
