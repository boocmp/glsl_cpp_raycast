#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/vec/vec.h"

#include <utility>

using namespace testing;

using namespace glsl;

namespace glsl {
template <typename T, size_t N>
bool operator==(const vec_n<T, N>& l, const vec_n<T, N>& r) {
  for (size_t i = 0; i < N; ++i) {
    if (l[i] != r[i]) {
      return false;
    }
  }
  return true;
}
}  // namespace glsl

TEST(Vec3Tests, ttt) {
  vec3 v3 = vec3(1,2,3);

  std::cout << sizeof(vec3) << std::endl;

  std::cout << v3.zyx << std::endl;
}

TEST(Vec3Tests, Construct) {
  {
    vec_n<float, 1> vf1;
    vec_n<int, 2> vi2;
    vec_n<double, 3> vd3;

    EXPECT_EQ(vf1, (vec_n<float, 1>(0)));
    EXPECT_EQ(vi2, (vec_n<int, 2>(0)));
    EXPECT_EQ(vd3, (vec_n<double, 3>(0)));
  }
  {
    vec_n<float, 1> vf1(1);
    vec_n<int, 2> vi2(1);
    vec_n<double, 3> vd3(1);

    EXPECT_EQ(vf1, (vec_n<float, 1>(1)));
    EXPECT_EQ(vi2, (vec_n<int, 2>(1, 1)));
    EXPECT_EQ(vd3, (vec_n<double, 3>(1, 1, 1)));
  }
  {
    vec_n<float, 1> vf1(1);
    vec_n<int, 2> vi2(1, 2);
    vec_n<double, 3> vd3(1, 2, 3);

    EXPECT_EQ(vf1, (vec_n<float, 1>(1)));
    EXPECT_EQ(vi2, (vec_n<int, 2>(1, 2)));
    EXPECT_EQ(vd3, (vec_n<double, 3>(1, 2, 3)));
  }
}

TEST(Vec3Tests, Add) {
  {
    vec_n<float, 3> a{1, 2, 3};
    vec_n<float, 3> b{-1, -2, -3};
    a += b;
    EXPECT_EQ(vec3(0, 0, 0), a);
  }
  {
    vec_n<int, 3> a{1, 2, 3};
    vec_n<int, 3> b{-1, -2, -3};
    a += b;
    EXPECT_EQ(int3(0, 0, 0), a);
  }
}

TEST(Vec3Tests, Mul) {
  {
    vec3 a{1, 2, 3};
    a *= 2;
    EXPECT_EQ(vec3(2, 4, 6), a);
  }
  {
    int3 a{1, 2, 3};
    a *= 2;
    EXPECT_EQ(int3(2, 4, 6), a);
  }
}
