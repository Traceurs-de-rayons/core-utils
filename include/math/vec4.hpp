#pragma once

#include <cmath>

namespace cu::math {

struct vec4
{
	float x, y, z, w;

	vec4() : x(0), y(0), z(0), w(0) {}
	vec4(float n) : x(n), y(n), z(n), w(n) {}
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	inline vec4 operator+(const vec4& v) const { return {x + v.x, y + v.y, z + v.z, w + v.w}; }
	inline vec4 operator-(const vec4& v) const { return {x - v.x, y - v.y, z - v.z, w - v.w}; }
	inline vec4 operator*(const vec4& v) const { return {x * v.x, y * v.y, z * v.z, w * v.w}; }
	inline vec4 operator/(const vec4& v) const { return {x / v.x, y / v.y, z / v.z, w / v.w}; }
	inline vec4 operator*(float s) const { return {x * s, y * s, z * s, w * s}; }
	inline vec4 operator/(float s) const { return {x / s, y / s, z / s, w / s}; }

	inline vec4& operator+=(const vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	inline vec4& operator-=(const vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }

	static inline float dot(const vec4& a, const vec4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

	inline float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }
	inline vec4 normalized() const { float l = length(); return l > 0 ? *this / l : *this; }
};

}
