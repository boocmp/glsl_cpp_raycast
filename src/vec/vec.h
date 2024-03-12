#pragma once

#include "vec_n.h"
#include "vec_n_ops.h"

namespace glsl {

using vec2 = vec_n<float, 2>;
using vec3 = vec_n<float, 3>;
using vec4 = vec_n<float, 4>;
using int2 = vec_n<int, 2>;
using int3 = vec_n<int, 3>;
using int4 = vec_n<int, 4>;

static_assert(sizeof(vec2) == sizeof(float[2]));
static_assert(sizeof(vec3) == sizeof(float[3]));
static_assert(sizeof(vec4) == sizeof(float[4]));

static_assert(sizeof(int2) == sizeof(int[2]));
static_assert(sizeof(int3) == sizeof(int[3]));
static_assert(sizeof(int4) == sizeof(int[4]));

}  // namespace glsl
