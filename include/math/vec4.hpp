#pragma once

#include <cmath>

#if defined(__SSE__)
#include <immintrin.h>
#endif

namespace cu::math {

/**
 * vec4 struct using SIMD
 * https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=SSE_ALL
 * 
 */
struct alignas(16) vec4
{
#if defined(__SSE__)
	union {
		__m128 v;
		struct { float x, y, z, w; };
	};

	vec4() { v = _mm_setzero_ps(); }
	vec4(float n) { v = _mm_set1_ps(n); }
	vec4(float x, float y, float z, float w) { v = _mm_set_ps(w, z, y, x); }

	inline vec4 operator+(const vec4& o) const { vec4 r; r.v = _mm_add_ps(v, o.v); return r; }
	inline vec4 operator-(const vec4& o) const { vec4 r; r.v = _mm_sub_ps(v, o.v); return r; }
	inline vec4 operator*(const vec4& o) const { vec4 r; r.v = _mm_mul_ps(v, o.v); return r; }
	inline vec4 operator/(const vec4& o) const { vec4 r; r.v = _mm_div_ps(v, o.v); return r; }
	inline vec4 operator*(float s) const { vec4 r; r.v = _mm_mul_ps(v, _mm_set1_ps(s)); return r; }
	inline vec4 operator/(float s) const { vec4 r; r.v = _mm_div_ps(v, _mm_set1_ps(s)); return r; }

	inline vec4& operator+=(const vec4& o) { v = _mm_add_ps(v, o.v); return *this; }
	inline vec4& operator-=(const vec4& o) { v = _mm_sub_ps(v, o.v); return *this; }

	static inline float dot(const vec4& a, const vec4& b)
	{
		__m128 t = _mm_mul_ps(a.v, b.v);
	#if defined(__SSE3__)
		t = _mm_hadd_ps(t, t);
		t = _mm_hadd_ps(t, t);
		return _mm_cvtss_f32(t);
	#else
		float tmp[4]; _mm_storeu_ps(tmp, t);
		return tmp[0] + tmp[1] + tmp[2] + tmp[3];
	#endif
	}

	inline float length() const { return std::sqrt(dot(*this, *this)); }
	inline vec4 normalized() const { float l = length(); return l > 0 ? *this / l : *this; }

	#else
	float x, y, z, w;

	vec4() : x(0), y(0), z(0), w(0) {}
	vec4(float n) : x(n), y(n), z(n), w(n) {}
	vec4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}

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

#endif
};

}
