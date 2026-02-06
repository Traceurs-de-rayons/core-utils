#pragma once

#include <cmath>

namespace cu::math {

struct vec2
{
	float x, y;

	vec2() : x(0), y(0) {}
	vec2(float n) : x(n), y(n) {}
	vec2(float x, float y) : x(x), y(y) {}

	inline vec2 operator+(const vec2& v) const { return {x + v.x, y + v.y}; }
	inline vec2 operator-(const vec2& v) const { return {x - v.x, y - v.y}; }
	inline vec2 operator*(const vec2& v) const { return {x * v.x, y * v.y}; }
	inline vec2 operator/(const vec2& v) const { return {x / v.x, y / v.y}; }
	inline vec2 operator*(float s) const { return {x * s, y * s}; }
	inline vec2 operator/(float s) const { return {x / s, y / s}; }

	inline vec2& operator+=(const vec2& v) { x += v.x; y += v.y; return *this; }
	inline vec2& operator-=(const vec2& v) { x -= v.x; y -= v.y; return *this; }

	static inline float dot(const vec2& a, const vec2& b) { return a.x * b.x + a.y * b.y; }

	inline float length() const { return std::sqrt(x * x + y * y); }
	inline vec2 normalized() const { float l = length(); return l > 0 ? *this / l : *this; }
};

}
