#include "00-util_avx.hpp"
#include "01-dot.hpp"

void test_c_c(int len, int nloop)
{
  // init
  auto vec1 = ALLOC<cd>(len);
  auto vec2 = ALLOC<cd>(len);
  for (auto j = 0; j < len; ++j)
  {
    vec1[j] = cd{0.01 * j, j - 1.0};
    vec2[j] = cd{j - 1.0, 0.01 * j};
  }
  cd res;
  std::cout << "complex-complex vector dot" << std::endl;
  SLEEP(1000);
  auto t0 = CLOCK::now();
  for (auto r = 0; r < nloop; ++r)
  {
    res = dot_avx(vec1, vec2, len);
  }
  auto t1 = CLOCK::now();
  auto el1 = ELAPSED(t1, t0);
  std::cout << "AVX:     " << el1 << std::endl;
  SLEEP(1000);
  auto t2 = CLOCK::now();
  for (auto r = 0; r < nloop; ++r)
  {
    res = dot(vec1, vec2, len);
  }
  auto t3 = CLOCK::now();
  auto el2 = ELAPSED(t3, t2);
  std::cout << "non-AVX: " << el2 << std::endl;
  FREE(vec1);
  FREE(vec2);
}

void test_c_d(int len, int nloop)
{
  // init
  auto vec1 = ALLOC<cd>(len);
  auto vec2 = ALLOC<double>(len);
  for (auto j = 0; j < len; ++j)
  {
    vec1[j] = cd{0.01 * j, 0.1 * j};
    vec2[j] = -0.1 * j;
  }
  cd res;
  std::cout << "complex-double vector dot" << std::endl;
  SLEEP(1000);
  auto t0 = CLOCK::now();
  for (auto r = 0; r < nloop; ++r)
  {
    res = dot_avx(vec1, vec2, len);
  }
  auto t1 = CLOCK::now();
  auto el1 = ELAPSED(t1, t0);
  std::cout << "AVX:     " << el1 << std::endl;
  SLEEP(1000);
  auto t2 = CLOCK::now();
  for (auto r = 0; r < nloop; ++r)
  {
    res = dot(vec1, vec2, len);
  }
  auto t3 = CLOCK::now();
  auto el2 = ELAPSED(t3, t2);
  std::cout << "non-AVX: " << el2 << std::endl;
  FREE(vec1);
  FREE(vec2);
}

int main()
{
  std::cout << std::setprecision(16);
  test_c_c(1000000, 1000);
  test_c_d(1000000, 1000);
  return 0;
}