#pragma once

#include "math/vec3.hpp"
#include "math/mat4.hpp"

namespace cu::math {

mat4 rotate(mat4 model, float angle, const vec3& axis);
mat4 getRotationMatrix(float angle, const vec3& axis);
mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up);
mat4 perspective(float fov_y, float aspect, float near, float far);

mat4 translate(const mat4& m, const vec3& v);
mat4 translate(const mat4& m, const vec4& v);
mat4 scale(const mat4& m, const vec3& v);
mat4 scale(const mat4& m, const vec4& v);

}