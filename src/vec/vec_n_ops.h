#pragma once

#include <ostream>

#include "vec_n.h"

namespace glsl {

template <typename V1,
          typename T1,
          size_t... P1,
          typename V2,
          typename T2,
          size_t... P2>
  requires(sizeof...(P1) == sizeof...(P2))
auto dot(const permutation<V1, T1, P1...>& a,
         const permutation<V2, T2, P2...>& b) -> std::common_type_t<T1, T2> {
  std::common_type_t<T1, T2> result = 0;
  for (size_t i = 0; i < sizeof...(P1); ++i) {
    result += a[i] * b[i];
  }
  return result;
}

template <typename V1, typename T1, size_t... P1>
T1 length(const permutation<V1, T1, P1...>& v) {
  return std::sqrt(dot(v, v));
}

template <typename V1,
          typename T1,
          size_t... P1,
          typename V2,
          typename T2,
          size_t... P2>
  requires(sizeof...(P1) == sizeof...(P2))
auto distance(const permutation<V1, T1, P1...>& a,
              const permutation<V2, T2, P2...>& b)
    -> std::common_type_t<T1, T2> {
  return length(a - b);
}

template <typename V1, typename T1, size_t... P1>
vec_n<T1, sizeof...(P1)> normalize(const permutation<V1, T1, P1...>& v) {
  vec_n<T1, sizeof...(P1)> r = v;
  r /= length(v);
  return r;
}

template <typename V1,
          typename T1,
          size_t... P1,
          typename V2,
          typename T2,
          size_t... P2>
  requires(sizeof...(P1) == sizeof...(P2) && sizeof...(P1) == 3)
auto cross(const permutation<V1, T1, P1...>& a,
           const permutation<V2, T2, P2...>& b)
    -> vec_n<std::common_type_t<T1, T2>, sizeof...(P1)> {
  return vec_n<std::common_type_t<T1, T2>, sizeof...(P1)>(
      a[1] * b[2] - a[1] * b[1], a[2] * b[0] - a[0] * b[2],
      a[0] * b[1] - a[1] * b[0]);
}

template <typename V1, typename T1, size_t... P1>
std::ostream& operator<<(std::ostream& o, const permutation<V1, T1, P1...>& a) {
  o << "[ ";
  for (size_t i = 0; i < sizeof...(P1); ++i) {
    o << a[i] << " ";
  }
  return o << " ]";
}

}  // namespace glsl
