#pragma once

#include <cmath>

namespace cu::math {

struct vec3
{
	float x, y, z;

	vec3() : x(0), y(0), z(0) {}
	vec3(float n) : x(n), y(n), z(n) {}
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	inline vec3 operator+(const vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
	inline vec3 operator-(const vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
	inline vec3 operator-() const { return vec3{-x, -y, -z}; }
	inline vec3 operator*(const vec3& v) const { return {x * v.x, y * v.y, z * v.z}; }
	inline vec3 operator/(const vec3& v) const { return {x / v.x, y / v.y, z / v.z}; }
	inline vec3 operator*(float s) const { return {x * s, y * s, z * s}; }
	inline vec3 operator/(float s) const { return {x / s, y / s, z / s}; }

	inline vec3& operator+=(const vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline vec3& operator-=(const vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }

	inline bool operator==(const vec3& v) const { return x == v.x && y == v.y && z == v.z; }

	static inline float dot(const vec3& a, const vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

	static inline vec3 cross(const vec3& a, const vec3& b) {
		return {
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
	}

	static inline vec3 normalize(const vec3& v)
	{
		float l = v.length();
		return l > 0 ? v / l : v;
	}

	inline float length() const { return std::sqrt(x * x + y * y + z * z); }
	inline vec3 normalized() const { float l = length(); return l > 0 ? *this / l : *this; }
};

}
