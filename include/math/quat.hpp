#pragma once

#include <cmath>
#include "vec3.hpp"
#include "mat4.hpp"

namespace cu::math {

/**
 * https://fr.wikipedia.org/wiki/Quaternion
 * 
 * A really complex wikipedia page, but in our case we can just see the quaternion
 * as a normalized vector with a rotation on itself
 * 
 * https://i.redd.it/rq2uboj5sdi21.png
 * https://www.3dgep.com/understanding-quaternions/
 * 
 */
struct quat
{
	union {
		struct {
			float w, x, y, z;
		};
		vec4 v;
	};

	quat() : w(1), x(0), y(0), z(0) {}
	quat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
	quat(float w, const vec3& v) : w(w), x(v.x), y(v.y), z(v.z) {}
	quat(const vec4& v) : w(v.x), x(v.y), y(v.z), z(v.w) {}

	inline quat operator+(const quat& q) const {
		return {v + q.v};
	}

	inline quat operator-(const quat& q) const {
		return {v - q.v};
	}

	inline quat operator*(const quat& q) const {
		return {
			w * q.w - x * q.x - y * q.y - z * q.z,
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y - x * q.z + y * q.w + z * q.x,
			w * q.z + x * q.y - y * q.x + z * q.w
		};
	}

	inline quat operator*(float s) const {
		return {v * s};
	}

	inline quat operator/(float s) const {
		return {v / s};
	}

	inline quat& operator*=(const quat& q) {
		*this = *this * q;
		return *this;
	}

	inline quat& operator+=(const quat& q) {
		v += q.v;
		return *this;
	}

	inline quat conjugate() const {
		return {w, -x, -y, -z};
	}

	inline float length() const {
		return v.length();
	}

	inline float magnitude() const {
		return length();
	}

	inline quat normalized() const {
		float l = length();
		return l > 0 ? *this / l : quat();
	}

	inline quat& normalize() {
		float l = length();
		if (l > 0) {
			w /= l; x /= l; y /= l; z /= l;
		}
		return *this;
	}

	inline quat inverse() const {
		float len_sq = v.length_sq();
		if (len_sq == 0) return quat();
		return conjugate() / len_sq;
	}

	static inline float dot(const quat& a, const quat& b) {
		return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	}

	static inline quat lerp(const quat& a, const quat& b, float t) {
		quat result = a + (b - a) * t;
		return result.normalized();
	}

	static inline quat slerp(const quat& a, const quat& b, float t) {
		quat qa = a.normalized();
		quat qb = b.normalized();

		float d = dot(qa, qb);

		if (d < 0.0f) {
			qb = {-qb.w, -qb.x, -qb.y, -qb.z};
			d = -d;
		}

		d = d < -1.0f ? -1.0f : (d > 1.0f ? 1.0f : d);

		float theta = std::acos(d);
		float sin_theta = std::sin(theta);

		if (sin_theta < 0.001f) {
			return lerp(qa, qb, t);
		}

		float w1 = std::sin((1.0f - t) * theta) / sin_theta;
		float w2 = std::sin(t * theta) / sin_theta;

		return ((qa * w1) + (qb * w2)).normalized();
	}

	static inline quat fromAxisAngle(const vec3& axis, float angle) {
		vec3 normalized_axis = vec3::normalize(axis);
		float half_angle = angle * 0.5f;
		float sin_half = std::sin(half_angle);
		return {
			std::cos(half_angle),
			normalized_axis.x * sin_half,
			normalized_axis.y * sin_half,
			normalized_axis.z * sin_half
		};
	}

	static inline void toAxisAngle(const quat& q, vec3& axis, float& angle) {
		quat normalized = q.normalized();
		angle = 2.0f * std::acos(std::max(-1.0f, std::min(1.0f, normalized.w)));
		
		float sin_half_angle = std::sin(angle * 0.5f);
		if (sin_half_angle < 0.001f) {
			axis = {0, 0, 1};
		} else {
			axis = {
				normalized.x / sin_half_angle,
				normalized.y / sin_half_angle,
				normalized.z / sin_half_angle
			};
		}
	}

	// roll (X), pitch (Y), yaw (Z)
	static inline quat fromEuler(float roll, float pitch, float yaw) {
		float cy = std::cos(yaw * 0.5f);
		float sy = std::sin(yaw * 0.5f);
		float cp = std::cos(pitch * 0.5f);
		float sp = std::sin(pitch * 0.5f);
		float cr = std::cos(roll * 0.5f);
		float sr = std::sin(roll * 0.5f);

		return {
			cy * cp * cr + sy * sp * sr,
			cy * cp * sr - sy * sp * cr,
			sy * cp * sr + cy * sp * cr,
			sy * cp * cr - cy * sp * sr
		};
	}

	static inline vec3 toEuler(const quat& q) {
		quat normalized = q.normalized();
		float w = normalized.w;
		float x = normalized.x;
		float y = normalized.y;
		float z = normalized.z;

		// Roll (X)
		float sinr_cosp = 2 * (w * x + y * z);
		float cosr_cosp = 1 - 2 * (x * x + y * y);
		float roll = std::atan2(sinr_cosp, cosr_cosp);

		// Pitch (Y)
		float sinp = 2 * (w * y - z * x);
		sinp = sinp > 1.0f ? 1.0f : (sinp < -1.0f ? -1.0f : sinp);
		float pitch = std::asin(sinp);

		// Yaw (Z)
		float siny_cosp = 2 * (w * z + x * y);
		float cosy_cosp = 1 - 2 * (y * y + z * z);
		float yaw = std::atan2(siny_cosp, cosy_cosp);

		return {roll, pitch, yaw};
	}

	inline vec3 rotate(const vec3& v) const {
		quat q = normalized();
		quat p(0, v.x, v.y, v.z);
		quat result = q * p * q.conjugate();
		return {result.x, result.y, result.z};
	}

	inline mat4 toMatrix() const {
		quat q = normalized();
		float w = q.w, x = q.x, y = q.y, z = q.z;

		float xx = x * x, yy = y * y, zz = z * z;
		float xy = x * y, xz = x * z, yz = y * z;
		float wx = w * x, wy = w * y, wz = w * z;

		mat4 result(0.0f);
		result.m[0][0] = 1 - 2 * (yy + zz);	result.m[0][1] = 2 * (xy - wz);		result.m[0][2] = 2 * (xz + wy);		result.m[0][3] = 0;
		result.m[1][0] = 2 * (xy + wz);		result.m[1][1] = 1 - 2 * (xx + zz);	result.m[1][2] = 2 * (yz - wx);		result.m[1][3] = 0;
		result.m[2][0] = 2 * (xz - wy);		result.m[2][1] = 2 * (yz + wx);		result.m[2][2] = 1 - 2 * (xx + yy);	result.m[2][3] = 0;
		result.m[3][0] = 0;					result.m[3][1] = 0;					result.m[3][2] = 0;					result.m[3][3] = 1;
		return result;
	}

};

inline quat operator*(float s, const quat& q) {
	return q * s;
}

}
