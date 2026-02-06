#pragma once

#include "math/vec4.hpp"

namespace cu::math {

struct mat4 {
	float m[4][4];

	mat4(float diag = 0.0f)
	{
		m[0][0] = diag; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = diag; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = diag; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = diag;
	}

	static inline mat4 identity() { return mat4(1.0f); }

	// mat4 * mat4
	inline mat4 operator*(const mat4& o) const
	{
		mat4 r(0.0f);

		const float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], a03 = m[0][3];
		const float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3];
		const float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3];
		const float a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3];

		const float b00 = o.m[0][0], b01 = o.m[0][1], b02 = o.m[0][2], b03 = o.m[0][3];
		const float b10 = o.m[1][0], b11 = o.m[1][1], b12 = o.m[1][2], b13 = o.m[1][3];
		const float b20 = o.m[2][0], b21 = o.m[2][1], b22 = o.m[2][2], b23 = o.m[2][3];
		const float b30 = o.m[3][0], b31 = o.m[3][1], b32 = o.m[3][2], b33 = o.m[3][3];

		r.m[0][0] = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
		r.m[0][1] = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
		r.m[0][2] = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
		r.m[0][3] = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;

		r.m[1][0] = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
		r.m[1][1] = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
		r.m[1][2] = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
		r.m[1][3] = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;

		r.m[2][0] = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
		r.m[2][1] = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
		r.m[2][2] = a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32;
		r.m[2][3] = a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33;

		r.m[3][0] = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;
		r.m[3][1] = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;
		r.m[3][2] = a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32;
		r.m[3][3] = a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33;

		return r;
	}

	// mat4 * vec4
	inline vec4 operator*(const vec4& v) const
	{
		vec4 r;
		r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
		r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
		r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
		r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
		return r;
	}

	inline mat4 operator*(const float scalar) const
	{
		mat4 r;

		r.m[0][0] = m[0][0] * scalar; r.m[0][1] = m[0][1] * scalar; r.m[0][2] = m[0][2] * scalar; r.m[0][3] = m[0][3] * scalar;
		r.m[1][0] = m[1][0] * scalar; r.m[1][1] = m[1][1] * scalar; r.m[1][2] = m[1][2] * scalar; r.m[1][3] = m[1][3] * scalar;
		r.m[2][0] = m[2][0] * scalar; r.m[2][1] = m[2][1] * scalar; r.m[2][2] = m[2][2] * scalar; r.m[2][3] = m[2][3] * scalar;
		r.m[3][0] = m[3][0] * scalar; r.m[3][1] = m[3][1] * scalar; r.m[3][2] = m[3][2] * scalar; r.m[3][3] = m[3][3] * scalar;

		return r;
	}

};

}