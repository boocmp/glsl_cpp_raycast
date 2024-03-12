#pragma once

#include "vec_permutation.h"

namespace glsl {

template <typename T, size_t N>
  requires(N > 0)
struct vec_data {
  union {
    T data[N] = {T()};
    struct {
      T x;
      T y;
      T z;
      T w;
    };
    struct {
      T r;
      T g;
      T b;
      T a;
    };
    struct {
      T s;
      T t;
      T p;
      T q;
    };
    ALL_V4_PERMUTATIONS(vec_data, T);
  };

  vec_data() = default;

  template <typename... Args>
    requires(sizeof...(Args) == N && (std::convertible_to<Args, T> && ...))
  vec_data(Args&&... args) : data{static_cast<T>(args)...} {}
};

template <typename T>
struct vec_data<T, 1> {
  union {
    T data[1] = {T()};
    struct {
      T x;
    };
    ALL_V2_PERMUTATIONS(vec_data, T);
  };

  vec_data() = default;

  template <typename... Args>
    requires(sizeof...(Args) == 1 && (std::convertible_to<Args, T> && ...))
  vec_data(Args&&... args) : data{static_cast<T>(args)...} {}
};

template <typename T>
struct vec_data<T, 2> {
  union {
    T data[2] = {T()};
    struct {
      T x;
      T y;
    };
    struct {
      T r;
      T g;
    };
    struct {
      T s;
      T t;
    };

    ALL_V2_PERMUTATIONS(vec_data, T);
  };

  vec_data() = default;

  template <typename... Args>
    requires(sizeof...(Args) == 2 && (std::convertible_to<Args, T> && ...))
  vec_data(Args&&... args) : data{static_cast<T>(args)...} {}
};

template <typename T>
struct vec_data<T, 3> {
  union {
    T data[3] = {T()};
    struct {
      T x;
      T y;
      T z;
    };
    struct {
      T r;
      T g;
      T b;
    };
    struct {
      T s;
      T t;
      T p;
    };
    ALL_V3_PERMUTATIONS(vec_data, T)
  };

  vec_data() = default;

  template <typename... Args>
    requires(sizeof...(Args) == 3 && (std::convertible_to<Args, T> && ...))
  vec_data(Args&&... args) : data{static_cast<T>(args)...} {}
};

}  // namespace glsl
