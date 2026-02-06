#include "math/transform.hpp"

namespace cu::math {

/**
 * https://fr.wikipedia.org/wiki/Matrice_de_rotation
 */
mat4 getRotationMatrix(float angle, const vec3& axis)
{
	vec3 a = axis.normalized();
	float c = cos(angle);
	float s = sin(angle);
	float x = a.x, y = a.y, z = a.z;

	mat4 r;
	r.m[0][0] = c + x*x*(1-c);
	r.m[1][0] = x*y*(1-c) - z*s;
	r.m[2][0] = x*z*(1-c) + y*s;
	r.m[3][0] = 0;

	r.m[0][1] = y*x*(1-c) + z*s;
	r.m[1][1] = c + y*y*(1-c);
	r.m[2][1] = y*z*(1-c) - x*s;
	r.m[3][1] = 0;

	r.m[0][2] = z*x*(1-c) - y*s;
	r.m[1][2] = z*y*(1-c) + x*s;
	r.m[2][2] = c + z*z*(1-c);
	r.m[3][2] = 0;

	r.m[0][3] = 0;
	r.m[1][3] = 0;
	r.m[2][3] = 0;
	r.m[3][3] = 1;
	return r;
}

mat4 rotate(mat4 model, float angle, const vec3& axis)
{
	return model * getRotationMatrix(angle, axis);
}

mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up)
{
	vec3 const f(vec3::normalize(center - eye));
	vec3 const s(vec3::normalize(vec3::cross(f, up)));
	vec3 const u(vec3::cross(s, f));

	mat4 res(1.0f);

	res.m[0][0] = s.x;
	res.m[1][0] = s.y;
	res.m[2][0] = s.z;

	res.m[0][1] = u.x;
	res.m[1][1] = u.y;
	res.m[2][1] = u.z;

	res.m[0][2] = -f.x;
	res.m[1][2] = -f.y;
	res.m[2][2] = -f.z;

	res.m[3][0] = -vec3::dot(s, eye);
	res.m[3][1] = -vec3::dot(u, eye);
	res.m[3][2] =  vec3::dot(f, eye);

	return res;
}

/**
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix.html
 * + y inversion to match vulkan perspective
*/
mat4 perspective(float fov_y, float aspect, float near, float far)
{
	const float f = 1.0f / tan(fov_y / 2.0f);

	mat4 m(0.0f);
	m.m[0][0] = f / aspect;
	m.m[1][1] = -f;
	m.m[2][2] = -(far + near) / (far - near);
	m.m[2][3] = -1.0f;
	m.m[3][2] = -(2.0f * far * near) / (far - near);
	return m;
}

}