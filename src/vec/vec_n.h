#pragma once

#include "vec_data.h"

namespace glsl {

template <typename T, size_t N>
struct vec_n : permutation_n<vec_data<T, N>, T, N>, public vec_data<T, N> {
  using type = T;
  static constexpr const size_t size = N;

  vec_n() = default;

  explicit vec_n(T v) noexcept {
    for (size_t i = 0; i < size; ++i) {
      this->data[i] = v;
    }
  }

  vec_n(const vec_n& o) noexcept { details::copy_permutaion(o, *this); }

  template <typename V1, typename T1, size_t... P1>
    requires(sizeof...(P1) == N)
  vec_n(const permutation<V1, T1, P1...>& p) noexcept {
    details::copy_permutaion(p, *this);
  }

  template <typename V1, typename T1, size_t... P1>
    requires(sizeof...(P1) == N)
  vec_n& operator=(const permutation<V1, T1, P1...>& p) noexcept {
    details::copy_permutaion(p, *this);
    return *this;
  }

  vec_n& operator=(const vec_n& o) noexcept {
    details::copy_permutaion(o, *this);
    return *this;
  }

  template <typename... Args>
    requires(sizeof...(Args) == N && (std::convertible_to<Args, T> && ...))
  explicit vec_n(Args&&... args) noexcept
      : vec_data<T, N>(std::forward<Args>(args)...) {}
};

}  // namespace glsl
