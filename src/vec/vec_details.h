#pragma once

#include <utility>

namespace glsl {
namespace details {

template <typename T1, typename T2>
constexpr void copy_permutaion(const T1& src, T2& dst) {
  typename T1::data_type tmp[T1::size];
  for (size_t i = 0; i < T1::size; ++i) {
    tmp[i] = src[i];
  }
  for (size_t i = 0; i < T1::size; ++i) {
    dst[i] = tmp[i];
  }
}

}  // namespace details
}  // namespace glsl
