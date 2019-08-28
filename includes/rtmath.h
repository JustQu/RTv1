/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 01:16:45 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/08 01:16:45 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMATH_H
# define RTMATH_H
#include "time.h"
#include "stdint.h"
#include "math.h"

# define _E				2.71828182845904523536028747135266250
# define _LOG2E			1.44269504088896340735992468100189214
# define _LOG10E		0.434294481903251827651128918916605082
# define _LN2			0.693147180559945309417232121458176568
# define _LN10			2.30258509299404568401799145468436421
# define _PI			3.14159265358979323846264338327950288
# define _PI_2			1.57079632679489661923132169163975144
# define _PI_4			0.785398163397448309615660845819875721
# define _1_PI_			0.318309886183790671537767526745028724
# define _2_PI			0.636619772367581343075535053490057448
# define _2_SQRTPI 		1.12837916709551257389615890312154517
# define _SQRT2			1.41421356237309504880168872420969808
# define _SQRT1_2		0.707106781186547524400844362104849039

typedef float	t_vec2[2];
typedef float	t_vec3[3];
typedef float	t_vec4[4];
typedef float	t_mat3[3][3];
typedef float	t_mat4[4][4];
typedef t_vec4	t_versor;

enum
{
	ox, oy, oz, ok
};

/*
 __     __                _                      _  _
 \ \   / /   ___    ___  | |_    ___    _ __    | || |
  \ \ / /   / _ \  / __| | __|  / _ \  | '__|   | || |_
   \ V /   |  __/ | (__  | |_  | (_) | | |      |__   _|
    \_/     \___|  \___|  \__|  \___/  |_|         |_|
*/

#define VEC4_ONE_INIT   {1.0f, 1.0f, 1.0f, 1.0f}
#define VEC4_ZERO_INIT  {0.0f, 0.0f, 0.0f, 0.0f}
#define VEC4_ONE        ((t_vec4)VEC4_ONE_INIT)
#define VEC4_ZERO       ((t_vec4)VEC4_ZERO_INIT)

/*
** init vec4 using vec3
*/
void	vec3_to_vec4(t_vec3 v3, float last, t_vec4 dest)
{
	dest[0] = v3[0];
	dest[1] = v3[1];
	dest[2] = v3[2];
	dest[3] = last;
}

/*
**copy ferst 3 members of [a] to [dest]
*/
void	vec4_copy3(t_vec4 a, t_vec3 dest)
{
	dest[0] = a[0];
	dest[1] = a[1];
	dest[2] = a[2];
}

/*
**copy all members of [v] to dest
*/
void	vec4_copy(t_vec4 v, t_vec4 dest)
{
	dest[0] = v[0];
	dest[1] = v[1];
	dest[2] = v[2];
	dest[3] = v[3];
}

/*
**make vector zero
*/
void	vec4_zero(t_vec4 v)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;
}

/*
**make vector one
*/
void	vec4_one(t_vec4 v)
{
	v[0] = 1.0f;
	v[1] = 1.0f;
	v[2] = 1.0f;
	v[3] = 1.0f;
}

/*
**vec4 dot product
*/
float	vec4_dot(t_vec4 a, t_vec4 b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

/*
**norm * norm(magnitude) of vec
*/
float	vec4_norm2(t_vec4 v)
{
	return (vec4_dot(v, v));
}

/*
**norm(magnitude) of vec4
*/
float	vec4_norm(t_vec4 v)
{
	return (sqrtf(vec4_dot(v, v)));
}

/*
**add b vector to a vector store result in dest
*/
void	vec4_sum(t_vec4 a, t_vec4 b, t_vec4 dest)
{
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
	dest[3] = a[3] + b[3];
}

/*
**add scalar to v vector store result in dest (d = v + vec(s))
*/
void	vec4_adds(t_vec4 v, float s, t_vec4 dest)
{
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
	dest[3] = v[3] + s;
}

/*
**substract b vector from a vector store result in dest (d = a - b)
*/
void	vec4_sub(t_vec4 a, t_vec4 b, t_vec4 dest)
{
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
	dest[3] = a[3] - b[3];
}

/*
**substract scalar from v vector sore result in dest (d = v - vec(s))
*/
void	vec4_subs(t_vec4 v, float s, t_vec4 dest)
{
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
	dest[2] = v[2] - s;
	dest[3] = v[3] - s;
}

/*
**multiply two vector (component-wise multuplication)
*/
void	vec4_mul(t_vec4 a, t_vec4 b, t_vec4 dest)
{
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
	dest[2] = a[2] * b[2];
	dest[3] = a[3] * b[3];
}

/*
**multiply/scale vec4 vector with scalar: result = v * s
*/
void	vec4_scale(t_vec4 a, float s, t_vec4 dest)
{
	dest[0] = a[0] * s;
	dest[1] = a[1] * s;
	dest[2] = a[2] * s;
	dest[3] = a[3] * s;
}

/*
**make vec4 vector scale as specified: result = unit(v) * s
*/
void	vec4_scale_as(t_vec4 v, float s, t_vec4 dest)
{
	float	norm;

	norm = vec4_norm(v);
	if (norm == 0.0f)
	{
		vec4_zero(dest);
		return ;
	}
	vec4_scale(v, s / norm, dest);
}

/*
**negate vector components and store result in dest
*/
void	vec4_negate_to(t_vec4 v, t_vec4 dest)
{
	dest[0] = -v[0];
	dest[1] = -v[1];
	dest[2] = -v[2];
	dest[3] = -v[3];
}

/*
**flip sign of all vec4 members
*/
void 	vec4_negate(t_vec4 v)
{
	vec4_negate_to(v, v);
}

/*
**normalize vec4 to dest
*/
void	vec4_normalize_to(t_vec4 v, t_vec4 dest)
{
	float	norm;

	norm = vec4_norm(v);
	if (norm == 0.0f)
	{
		vec4_zero(dest);
		return ;
	}
	vec4_scale(v, 1.0f / norm, dest);
}

/*
**normalize vec4 and store result in same vec
*/
void	vec4_normalize(t_vec4 v)
{
	vec4_normalize_to(v, v);
}

/*
**multiply given parameter with itself = x * x or powf(x, 2)
*/
float	pow2(float x)
{
	return (x * x);
}

/*
**distance between two vectors
*/
float	vec4_distance(t_vec4 a, t_vec4 b)
{
	return (sqrtf(pow2(b[0] - a[0])
				+ pow2(b[1] - a[1])
				+ pow2(b[2] - a[2])
				+ pow2(b[3] - a[3])));
}

/*
**find minimum of given two values
*/
float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

/*
**find maximum of given two values
*/
float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
**clamp a number between min and max
*/
float	clamp(float val, float min_val, float max_val)
{
	return (min(max(val, min_val), max_val));
}

/*
**clamp a number to zero and one
*/
float	clamp_zo(float val)
{
	return (clamp(val, 0.0f, 1.0f));
}

/*
**fill a vectir with specified value
*/
void	vec4_broadcast(float val, t_vec4 d)
{
	d[0] = val;
	d[1] = val;
	d[2] = val;
	d[3] = val;
}

/*
**linear interpolation between two vector
**formula: from + s * (to - from)
**t - interpolant (amount) clamped between 0 and 1
*/
void	vec4_lerp(t_vec4 from, t_vec4 to, float t, t_vec4 dest)
{
	t_vec4 s;
	t_vec4 v;

	vec4_broadcast(clamp_zo(t), s);
	vec4_sub(to, from, v);
	vec4_mul(s, v, v);
	vec4_sum(from, v, dest);
}

/*
**mul vector with scalar and add result to sum
*/
void	vec4_muladds(t_vec4 a, float s, t_vec4 dest)
{
	dest[0] += a[0] * s;
	dest[1] += a[1] * s;
	dest[2] += a[2] * s;
	dest[3] += a[3] * s;
}

/*
 __     __                _                      _____
 \ \   / /   ___    ___  | |_    ___    _ __    |___ /
  \ \ / /   / _ \  / __| | __|  / _ \  | '__|     |_ \
   \ V /   |  __/ | (__  | |_  | (_) | | |       ___) |
    \_/     \___|  \___|  \__|  \___/  |_|      |____/
*/

#define VEC3_ONE_INIT	{1.0f, 1.0f, 1.0f}
#define VEC3_ZERO_INIT	{0.0f, 0.0f, 0.0f}
#define VEC3_ONE		((t_vec3)VEC3_ONE_INIT)
#define VEC3_ZERO		((t_vec3)VEC3_ZERO_INIT)
#define YUP				((t_vec3){0.0f, 1.0f, 0.0f})
#define ZUP				((t_vec3){0.0f, 0.0f, 1.0f})
#define XUP				((t_vec3){1.0f, 0.0f, 0.0f})

/*
**init vec3 using vec4
*/
void	vec4_to_vec3(t_vec4 v4, t_vec3 dest)
{
  dest[0] = v4[0];
  dest[1] = v4[1];
  dest[2] = v4[2];
}

/*
**copy all members of [a] to [dest]
*/
void	vec3_copy(t_vec3 a, t_vec3 dest)
{
  dest[0] = a[0];
  dest[1] = a[1];
  dest[2] = a[2];
}

/*
**make vector zero
*/
void	vec3_zero(t_vec3 v)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

/*
**make vector one
*/
void	vec3_one(t_vec3 v)
{
	v[0] = 1.0f;
	v[1] = 1.0f;
	v[2] = 1.0f;
}

/*
**vec3 dot product
*/
float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/*
**norm * norm (magnitude) of vec
*/
float	vec3_norm2(t_vec3 v)
{
  return (vec3_dot(v, v));
}

/*
**norm (magnitude of vec3)
*/
float	vec3_norm(t_vec3 v)
{
  return (sqrtf(vec3_norm2(v)));
}

/*
**add scalar to v vector store result in dest (d = v + s)
*/
void	vec3_adds(t_vec3 v, float s, t_vec3 dest)
{
  dest[0] = v[0] + s;
  dest[1] = v[1] + s;
  dest[2] = v[2] + s;
}

/*
**substract scalar from v vector store result in dest (d = v - s)
*/
void	vec3_subs(t_vec3 v, float s, t_vec3 dest)
{
  dest[0] = v[0] - s;
  dest[1] = v[1] - s;
  dest[2] = v[2] - s;
}

/*
**add a vector to b vector store result in dest
*/
void	vec3_sum(t_vec3 a, t_vec3 b, t_vec3 dest)
{
  dest[0] = a[0] + b[0];
  dest[1] = a[1] + b[1];
  dest[2] = a[2] + b[2];
}

/*
**substract b vector from a vector store result in dest
*/
void	vec3_sub(t_vec3 a, t_vec3 b, t_vec3 dest)
{
  dest[0] = a[0] - b[0];
  dest[1] = a[1] - b[1];
  dest[2] = a[2] - b[2];
}

/*
**multiply/scale vec4 vector with scalar: result = v * s
*/
void	vec3_scale(t_vec3 v, float s, t_vec3 dest)
{
  dest[0] = v[0] * s;
  dest[1] = v[1] * s;
  dest[2] = v[2] * s;
}

/*
**multiply two vector (component-wise multiplication)
*/
void	vec3_mul(t_vec3 a, t_vec3 b, t_vec3 dest)
{
  dest[0] = a[0] * b[0];
  dest[1] = a[1] * b[1];
  dest[2] = a[2] * b[2];
}

/*
**negate vector components and store result in dest
*/
void	vec3_negate_to(t_vec3 v, t_vec3 dest)
{
  dest[0] = -v[0];
  dest[1] = -v[1];
  dest[2] = -v[2];
}

/*
**negate vector components
*/
void	vec3_negate(t_vec3 v)
{
  vec3_negate_to(v, v);
}

/*
**normalize vec3 and store result in same vec
*/
void	vec3_normalize(t_vec3 v)
{
	float norm;

	norm = vec3_norm(v);
	if (norm == 0.0f)
	{
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		return;
	}
	vec3_scale(v, 1.0f / norm, v);
}

void	vec3_normalize_to(t_vec3 v, t_vec3 dest)
{
	float norm;

	norm = vec3_norm(v);
	if (norm == 0.0f)
	{
		vec3_zero(dest);
		return;
	}
	vec3_scale(v, 1.0f / norm, dest);
}

/*
**cross product of two vector
**(u2.v3 - u3.v2, u3.v1 - u1.v3, u1.v2 - u2.v1)
*/

void	vec3_cross(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[1] * b[2] - a[2] * b[1];
	dest[1] = a[2] * b[0] - a[0] * b[2];
	dest[2] = a[0] * b[1] - a[1] * b[0];
}

/*
** angle between two vector
*/

float	vec3_angle(t_vec3 a, t_vec3 b)
{
	float	norm;
	float	dot;

	/* maybe compiler generate approximation instruction (rcp) */
	norm = 1.0f / (vec3_norm(a) * vec3_norm(b));
	dot  = vec3_dot(a, b) * norm;
	if (dot > 1.0f)
		return 0.0f;
	else if (dot < -1.0f)
		return _PI;
	return acosf(dot);
}

/*
** rotate vec3 around axis by angle using Rodrigues' rotation formula
*/
void	vec3_rotate(t_vec3 v, float angle, t_vec3 axis)
{
	t_vec3	v1;
	t_vec3	v2;
	t_vec3	k;
	float	c;
	float	s;

	c = cosf(angle);
	s = sinf(angle);
	vec3_normalize_to(axis, k);
	/* Right Hand, Rodrigues' rotation formula:
        v = v*cos(t) + (kxv)sin(t) + k*(k.v)(1 - cos(t))*/
	vec3_scale(v, c, v1);
	vec3_cross(k, v, v2);
	vec3_scale(v2, s, v2);
	vec3_sum(v1, v2, v1);
	vec3_scale(k, vec3_dot(k, v) * (1.0f - c), v2);
	vec3_sum(v1, v2, v);
}

/*
** apply rotation matrix to vector
*/
void	vec3_rotate_m4(t_mat4 m, t_vec3 v, t_vec3 dest)
{
	t_vec4	x;
	t_vec4	y;
	t_vec4	z;
	t_vec4	res;

	vec4_normalize_to(m[0], x);
	vec4_normalize_to(m[1], y);
	vec4_normalize_to(m[2], z);

	vec4_scale(x, v[0], res);
	vec4_muladds(y, v[1], res);
	vec4_muladds(z, v[2], res);

	vec4_to_vec3(res, dest);
}

void	vec3_rotate_m3(t_mat3 m, t_vec3 v, t_vec3 dest)
{
	t_vec4	res;
	t_vec4	x;
	t_vec4	y;
	t_vec4	z;

	vec3_to_vec4(m[0], 0.0f, x);
	vec3_to_vec4(m[1], 0.0f, y);
	vec3_to_vec4(m[2], 0.0f, z);
	vec4_normalize(x);
	vec4_normalize(y);
	vec4_normalize(z);
	vec4_scale(x, v[0], res);
	vec4_muladds(y, v[1], res);
	vec4_muladds(z, v[2], res);
	vec4_to_vec3(res, dest);
}

/*
**project a vector onto b vector
*/
void	vec3_proj(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	vec3_scale(b, vec3_dot(a, b) / vec3_norm2(b), dest);
}

/*
**find center point fo two vector
*/
void	vec3_center(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	vec3_sum(a, b, dest);
	vec3_scale(dest, 0.5f, dest);
}

/*
**squared distance between two vectors
*/
float	t_vec3_distance2(t_vec3 a, t_vec3 b)
{
	return (pow2(b[0] - a[0])
			+ pow2(b[1] - a[1])
			+ pow2(b[2] - a[2]));
}

/*
**distance beween two vector
*/
float vec3_distance(t_vec3 a, t_vec3 b)
{
	return (sqrtf(t_vec3_distance2(a, b)));
}

/*
**fill a vector with specified value
*/
void	vec3_broadcast(float val, t_vec3 d)
{
	d[0] = val;
	d[1] = val;
	d[2] = val;
}

/*
**linear interpolation between two vector
**formula: from + s * (to - from)
**t	interpolant (amount) clamped between 0 and 1
*/
void	vec3_lerp(t_vec3 from, t_vec3 to, float t, t_vec3 dest)
{
	t_vec3 s;
	t_vec3 v;

	vec3_broadcast(clamp_zo(t), s);
	vec3_sub(to, from, v);
	vec3_mul(s, v, v);
	vec3_sum(from, v, dest);
}

/*
**vec3 cross product
**this is just convenient wrapper
*/
void	cross(t_vec3 a, t_vec3 b, t_vec3 d)
{
  vec3_cross(a, b, d);
}

/*
**vec3 dot product
**this is just convenient wrapper
*/
float	dot(t_vec3 a, t_vec3 b)
{
  return (vec3_dot(a, b));
}

/*
**normalize vec3 and store result in same vec
**this is just convenient wrapper
*/
void	normalize(t_vec3 v)
{
	vec3_normalize(v);
}

/*
**normalize vec3 to dest
**this is just convenient wrapper
*/
void	normalize_to(t_vec3 v, t_vec3 dest)
{
  vec3_normalize_to(v, dest);
}

/*
  __  __    _  _____ ____  _____  __  _____
 |  \/  |  / \|_   _|  _ \|_ _\ \/ / |___ /
 | |\/| | / _ \ | | | |_) || | \  /    |_ \
 | |  | |/ ___ \| | |  _ < | | /  \   ___) |
 |_|  |_/_/   \_\_| |_| \_\___/_/\_\ |____/
 */

#define MAT3_IDENTITY_INIT  {{1.f, .0f, .0f}, {.0f, 1.f, .0f}, {.0f, .0f, 1.f}}
#define MAT3_ZERO_INIT      {{.0f, .0f, .0f}, {.0f, .0f, .0f}, {.0f, .0f, .0f}}
#define MAT3_IDENTITY 		((t_mat3)MAT3_IDENTITY_INIT)
#define MAT3_ZERO     		((t_mat3)MAT3_ZERO_INIT)

/*!
 * @brief copy all members of [mat] to [dest]
 */
void	mat3_copy(t_mat3 mat, t_mat3 dest)
{
	dest[0][0] = mat[0][0];
	dest[0][1] = mat[0][1];
	dest[0][2] = mat[0][2];
	dest[1][0] = mat[1][0];
	dest[1][1] = mat[1][1];
	dest[1][2] = mat[1][2];
	dest[2][0] = mat[2][0];
	dest[2][1] = mat[2][1];
	dest[2][2] = mat[2][2];
}

/*!
 * make given matrix identity. It is identical with below,
 * but it is more easy to do that with this func especially for members
 * e.g. mat3_identity(aStruct->aMatrix);
 * @code
 * mat3_copy(MAT3_IDENTITY, mat); // C only
 * // or
 * mat3 mat = MAT3_IDENTITY_INIT;
 * @endcode
*/
void	mat3_identity(t_mat3 mat)
{
	mat3_copy(MAT3_IDENTITY, mat);
}

/*!
 * make given matrix array's each element identity matrix
*/
void	mat3_identity_array(t_mat3 *mat, size_t count)
{
	t_mat3	t;
	size_t	i;

	mat3_identity(t);
	i = 0;
	while (i < count)
	{
		mat3_copy(t, mat[i]);
		i++;
	}
}

/*!
 * make given matrix zero.
*/
void	mat3_zero(t_mat3 mat)
{
	mat3_copy(MAT3_ZERO, mat);
}

/*!
 *multiply m1 and m2 to dest
 *
 * m1, m2 and dest matrices can be same matrix, it is possible to write this:
 *
 * @code
 * mat3 m = MAT3_IDENTITY_INIT;
 * mat3_mul(m, m, m);
*/
void	mat3_mul(t_mat3 m1, t_mat3 m2, t_mat3 dest)
{
	t_mat3	tmp;

	tmp[0][0] =
		m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0];
	tmp[0][1] =
		m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1];
	tmp[0][2] =
		m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2];
	tmp[1][0] =
		m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0];
	tmp[1][1] =
		m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1];
	tmp[1][2] =
		m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2];
	tmp[2][0] =
		m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0];
	tmp[2][1] =
		m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1];
	tmp[2][2] =
		m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2];
	mat3_copy(tmp, dest);
}

/*!
 *transpose mat3 and store in dest
 *
 * source matrix will not be transposed unless dest is m
*/
void	mat3_transpose_to(t_mat3 m, t_mat3 dest)
{
	dest[0][0] = m[0][0];
	dest[0][1] = m[1][0];
	dest[0][2] = m[2][0];
	dest[1][0] = m[0][1];
	dest[1][1] = m[1][1];
	dest[1][2] = m[2][1];
	dest[2][0] = m[0][2];
	dest[2][1] = m[1][2];
	dest[2][2] = m[2][2];
}

/*
 *tranpose mat3 and store result in same matrix
*/
void	mat3_transpose(t_mat3 m)
{
	t_mat3 tmp;

	tmp[0][1] = m[1][0];
	tmp[0][2] = m[2][0];
	tmp[1][0] = m[0][1];
	tmp[1][2] = m[2][1];
	tmp[2][0] = m[0][2];
	tmp[2][1] = m[1][2];
	m[0][1] = tmp[0][1];
	m[0][2] = tmp[0][2];
	m[1][0] = tmp[1][0];
	m[1][2] = tmp[1][2];
	m[2][0] = tmp[2][0];
	m[2][1] = tmp[2][1];
}

/*
** multiply mat3 with vec3 (column vector) and store in dest vector
*/
void	mat3_mulv(t_mat3 m, t_vec3 v, t_vec3 dest)
{
  dest[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2];
  dest[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2];
  dest[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2];
}

/*
 * trace of matrix
 * sum of the elements on the main diagonal from upper left to the lower right
*/
float	mat3_trace(t_mat3 m)
{
	return (m[0][0] + m[1][1] + m[2][2]);
}

/*!
 * @brief convert mat3 to quaternion
 */
/* it seems using like m12 instead of m[1][2] causes extra instructions */
void	mat3_quat(t_mat3 m, t_versor dest)
{
  float trace;
  float	r;
  float	rinv;

  trace = m[0][0] + m[1][1] + m[2][2];
  if (trace >= 0.0f)
  {
    r       = sqrtf(1.0f + trace);
    rinv    = 0.5f / r;
    dest[0] = rinv * (m[1][2] - m[2][1]);
    dest[1] = rinv * (m[2][0] - m[0][2]);
    dest[2] = rinv * (m[0][1] - m[1][0]);
    dest[3] = r    * 0.5f;
  }
  else if (m[0][0] >= m[1][1] && m[0][0] >= m[2][2])
  {
    r       = sqrtf(1.0f - m[1][1] - m[2][2] + m[0][0]);
    rinv    = 0.5f / r;
    dest[0] = r    * 0.5f;
    dest[1] = rinv * (m[0][1] + m[1][0]);
    dest[2] = rinv * (m[0][2] + m[2][0]);
    dest[3] = rinv * (m[1][2] - m[2][1]);
  }
  else if (m[1][1] >= m[2][2])
  {
    r       = sqrtf(1.0f - m[0][0] - m[2][2] + m[1][1]);
    rinv    = 0.5f / r;
    dest[0] = rinv * (m[0][1] + m[1][0]);
    dest[1] = r    * 0.5f;
    dest[2] = rinv * (m[1][2] + m[2][1]);
    dest[3] = rinv * (m[2][0] - m[0][2]);
  }
  else
  {
    r       = sqrtf(1.0f - m[0][0] - m[1][1] + m[2][2]);
    rinv    = 0.5f / r;
    dest[0] = rinv * (m[0][2] + m[2][0]);
    dest[1] = rinv * (m[1][2] + m[2][1]);
    dest[2] = r    * 0.5f;
    dest[3] = rinv * (m[0][1] - m[1][0]);
  }
}

/*!
 * scale (multiply with scalar) matrix
 * multiply matrix with scalar
 */
void	mat3_scale(t_mat3 m, float s)
{
  m[0][0] *= s;
  m[0][1] *= s;
  m[0][2] *= s;
  m[1][0] *= s;
  m[1][1] *= s;
  m[1][2] *= s;
  m[2][0] *= s;
  m[2][1] *= s;
  m[2][2] *= s;
}

/*
 * mat3 determinant
 */
float	mat3_det(t_mat3 mat)
{
  return (mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])
  		- mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2])
		+ mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]));
}

/*
 * inverse mat3 and store in dest
 */
void	mat3_inv(t_mat3 mat, t_mat3 dest)
{
  	float	det;
  	t_mat3	dest1;

  	dest1[0][0] =   mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
  	dest1[0][1] = -(mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2]);
  	dest1[0][2] =   mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2];
  	dest1[1][0] = -(mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);
  	dest1[1][1] =   mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0];
  	dest1[1][2] = -(mat[0][0] * mat[1][2] - mat[1][0] * mat[0][2]);
  	dest1[2][0] =   mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];
  	dest1[2][1] = -(mat[0][0] * mat[2][1] - mat[2][0] * mat[0][1]);
  	dest1[2][2] =   mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
  	det = 1.0f / (mat[0][0] * dest1[0][0] + mat[0][1] * dest1[1][0]
	  									  + mat[0][2] * dest1[2][0]);
	mat3_copy(dest1, dest);
	mat3_scale(dest, det);
}

/*
 * swap two matrix columns
*/
void	mat3_swap_col(t_mat3 mat, int col1, int col2)
{
	t_vec3 tmp;

	vec3_copy(mat[col1], tmp);
	vec3_copy(mat[col2], mat[col1]);
	vec3_copy(tmp, mat[col2]);
}

/*
 * swap two matrix rows
*/

void	mat3_swap_row(t_mat3 mat, int row1, int row2)
{
	t_vec3 tmp;

	tmp[0] = mat[0][row1];
	tmp[1] = mat[1][row1];
	tmp[2] = mat[2][row1];
	mat[0][row1] = mat[0][row2];
	mat[1][row1] = mat[1][row2];
	mat[2][row1] = mat[2][row2];
	mat[0][row2] = tmp[0];
	mat[1][row2] = tmp[1];
	mat[2][row2] = tmp[2];
}

/*
 * helper for  R (row vector) * M (matrix) * C (column vector)
 * rmc stands for Row * Matrix * Column
 * the result is scalar because R * M = Matrix1x3 (row vector),
 * then Matrix1x3 * Vec3 (column vector) = Matrix1x1 (Scalar)
 */
float	mat3_rmc(t_vec3 r, t_mat3 m, t_vec3 c)
{
	t_vec3	tmp;

  	mat3_mulv(m, c, tmp);
	return (vec3_dot(r, tmp));
}

/*


MATRIX 4


*/

#define MAT4_IDENTITY_INIT  {{1.0f, 0.0f, 0.0f, 0.0f},                    \
                            {0.0f, 1.0f, 0.0f, 0.0f},                    \
                            {0.0f, 0.0f, 1.0f, 0.0f},                    \
                            {0.0f, 0.0f, 0.0f, 1.0f}}

#define MAT4_ZERO_INIT      {{0.0f, 0.0f, 0.0f, 0.0f},                    \
                            {0.0f, 0.0f, 0.0f, 0.0f},                    \
                            {0.0f, 0.0f, 0.0f, 0.0f},                    \
                            {0.0f, 0.0f, 0.0f, 0.0f}}

#define MAT4_IDENTITY ((t_mat4)MAT4_IDENTITY_INIT)
#define MAT4_ZERO     ((t_mat4)MAT4_ZERO_INIT)

/*!
 * copy all members of [mat] to [dest]
 */
void	mat4_copy(t_mat4 mat, t_mat4 dest)
{
  	dest[0][0] = mat[0][0];
	dest[1][0] = mat[1][0];
	dest[0][1] = mat[0][1];
	dest[1][1] = mat[1][1];
	dest[0][2] = mat[0][2];
	dest[1][2] = mat[1][2];
	dest[0][3] = mat[0][3];
	dest[1][3] = mat[1][3];
	dest[2][0] = mat[2][0];
	dest[3][0] = mat[3][0];
	dest[2][1] = mat[2][1];
	dest[3][1] = mat[3][1];
	dest[2][2] = mat[2][2];
	dest[3][2] = mat[3][2];
	dest[2][3] = mat[2][3];
	dest[3][3] = mat[3][3];
}

/*
 * make given matrix identity. It is identical with below,
 *      but it is more easy to do that with this func especially for members
 *      e.g. mat4_identity(aStruct->aMatrix);
 *
 * mat4_copy(MAT4_IDENTITY, mat); // C only
 * // or
 * mat4 mat = MAT4_IDENTITY_INIT;
 */
void	mat4_identity(t_mat4 mat)
{
  	mat4_copy(MAT4_IDENTITY, mat);
}

/*!
 *make given matrix array's each element identity matrix
*/
void	mat4_identity_array(t_mat4 *mat, size_t count)
{
	t_mat4 	t;
	size_t 	i;

	mat4_identity(t);
	i = 0;
	while (i < count)
	{
		mat4_copy(t, mat[i]);
		i++;
	}
}

/*
 * make given matrix zero.
*/
void	mat4_zero(t_mat4 mat)
{
	mat4_copy(MAT4_ZERO, mat);
}

/*
 *copy upper-left of mat4 to mat3
*/
void	mat4_pick3(t_mat4 mat, t_mat3 dest)
{
	dest[0][0] = mat[0][0];
	dest[0][1] = mat[0][1];
	dest[0][2] = mat[0][2];
	dest[1][0] = mat[1][0];
	dest[1][1] = mat[1][1];
	dest[1][2] = mat[1][2];
	dest[2][0] = mat[2][0];
	dest[2][1] = mat[2][1];
	dest[2][2] = mat[2][2];
}

/*
 * copy upper-left of mat4 to mat3 (transposed)
 * the postfix t stands for transpose
*/
void	mat4_pick3t(t_mat4 mat, t_mat3 dest)
{
	dest[0][0] = mat[0][0];
	dest[0][1] = mat[1][0];
	dest[0][2] = mat[2][0];
	dest[1][0] = mat[0][1];
	dest[1][1] = mat[1][1];
	dest[1][2] = mat[2][1];
	dest[2][0] = mat[0][2];
	dest[2][1] = mat[1][2];
	dest[2][2] = mat[2][2];
}

/*
 * copy mat3 to mat4's upper-left
*/
void	mat4_ins3(t_mat3 mat, t_mat4 dest)
{
	dest[0][0] = mat[0][0];
	dest[0][1] = mat[0][1];
	dest[0][2] = mat[0][2];
	dest[1][0] = mat[1][0];
	dest[1][1] = mat[1][1];
	dest[1][2] = mat[1][2];
	dest[2][0] = mat[2][0];
	dest[2][1] = mat[2][1];
	dest[2][2] = mat[2][2];
}

/*!
 * multiply m1 and m2 to dest
 *
 * m1, m2 and dest matrices can be same matrix, it is possible to write this:
 *
 * @code
 * mat4 m = MAT4_IDENTITY_INIT;
 * mat4_mul(m, m, m);
 * @endcode
 */
void	mat4_mul(t_mat4 m1, t_mat4 m2, t_mat4 dest)
{
	float a00 = m1[0][0], a01 = m1[0][1], a02 = m1[0][2], a03 = m1[0][3],
        a10 = m1[1][0], a11 = m1[1][1], a12 = m1[1][2], a13 = m1[1][3],
        a20 = m1[2][0], a21 = m1[2][1], a22 = m1[2][2], a23 = m1[2][3],
        a30 = m1[3][0], a31 = m1[3][1], a32 = m1[3][2], a33 = m1[3][3],
        b00 = m2[0][0], b01 = m2[0][1], b02 = m2[0][2], b03 = m2[0][3],
        b10 = m2[1][0], b11 = m2[1][1], b12 = m2[1][2], b13 = m2[1][3],
        b20 = m2[2][0], b21 = m2[2][1], b22 = m2[2][2], b23 = m2[2][3],
        b30 = m2[3][0], b31 = m2[3][1], b32 = m2[3][2], b33 = m2[3][3];

	dest[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
	dest[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
	dest[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
	dest[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
	dest[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
	dest[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
	dest[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
	dest[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
	dest[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
	dest[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
	dest[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
	dest[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
	dest[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
	dest[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
	dest[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
	dest[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
}

/*!
 * @brief mupliply N mat4 matrices and store result in dest
 *
 * this function lets you multiply multiple (more than two or more...) matrices
 * <br><br>multiplication will be done in loop, this may reduce instructions
 * size but if <b>len</b> is too small then compiler may unroll whole loop,
 * usage:
 * @code
 * mat m1, m2, m3, m4, res;dest[2][3] = m[3][2];
 *
 * mat4_mulN((mat4 *[]){&m1, &m2, &m3, &m4}, 4, res);
 * @endcode
 *
 * @warning matrices parameter is pointer array not mat4 array!
 */

void	mat4_mulN(t_mat4 *matrices[], uint32_t len, t_mat4 dest)
{
	uint32_t i;

	mat4_mul(*matrices[0], *matrices[1], dest);
	for (i = 2; i < len; i++)
		mat4_mul(dest, *matrices[i], dest);
}

/*
 * multiply mat4 with vec4 (column vector) and store in dest vector
*/
void	mat4_mulv(t_mat4 m, t_vec4 v, t_vec4 dest)
{
	t_vec4 res;

	res[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3];
	res[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3];
	res[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3];
	res[3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3];
  vec4_copy(res, dest);
}

/*
 * trace of matrix
 * sum of the elements on the main diagonal from upper left to the lower right
*/
float	mat4_trace(t_mat4 m)
{
	return m[0][0] + m[1][1] + m[2][2] + m[3][3];
}

/*
 * trace of matrix (rotation part)
 * sum of the elements on the main diagonal from upper left to the lower right
 */

float	mat4_trace3(t_mat4 m)
{
	return m[0][0] + m[1][1] + m[2][2];
}

/*
 * convert mat4's rotation part to quaternion
*/
void	mat4_quat(t_mat4 m, t_versor dest)
{
	float	trace;
	float	r;
	float	rinv;

  	/* it seems using like m12 instead of m[1][2] causes extra instructions */

	trace = m[0][0] + m[1][1] + m[2][2];
	if (trace >= 0.0f)
	{
		r       = sqrtf(1.0f + trace);
		rinv    = 0.5f / r;
		dest[0] = rinv * (m[1][2] - m[2][1]);
		dest[1] = rinv * (m[2][0] - m[0][2]);
		dest[2] = rinv * (m[0][1] - m[1][0]);
		dest[3] = r    * 0.5f;
	}
	else if (m[0][0] >= m[1][1] && m[0][0] >= m[2][2])
	{
    	r       = sqrtf(1.0f - m[1][1] - m[2][2] + m[0][0]);
    	rinv    = 0.5f / r;
		dest[0] = r    * 0.5f;
		dest[1] = rinv * (m[0][1] + m[1][0]);
		dest[2] = rinv * (m[0][2] + m[2][0]);
		dest[3] = rinv * (m[1][2] - m[2][1]);
	}
	else if (m[1][1] >= m[2][2])
	{
	r       = sqrtf(1.0f - m[0][0] - m[2][2] + m[1][1]);
	rinv    = 0.5f / r;
	dest[0] = rinv * (m[0][1] + m[1][0]);
	dest[1] = r    * 0.5f;
	dest[2] = rinv * (m[1][2] + m[2][1]);
	dest[3] = rinv * (m[2][0] - m[0][2]);
	}
	else
	{
    	r       = sqrtf(1.0f - m[0][0] - m[1][1] + m[2][2]);
    	rinv    = 0.5f / r;
    	dest[0] = rinv * (m[0][2] + m[2][0]);
    	dest[1] = rinv * (m[1][2] + m[2][1]);
    	dest[2] = r    * 0.5f;
    	dest[3] = rinv * (m[0][1] - m[1][0]);
	}
}

/*
 *multiply vector with mat4
 *
 *m    mat4(affine transform)
 *v    vec3
 *last 4th item to make it vec4
 *dest result vector (t_vec3)
*/

void	mat4_mulv3(t_mat4 m, t_vec3 v, float last, t_vec3 dest)
{
	t_vec4 res;

	vec3_to_vec4(v, last, res);
	mat4_mulv(m, res, res);
	vec4_to_vec3(res, dest);
}

/*
 * transpose mat4 and store in dest
 * source matrix will not be transposed unless dest is m
 * todo: error when dest and m is the same matrix
 */

void	mat4_transpose_to(t_mat4 m, t_mat4 dest)
{
	dest[0][0] = m[0][0];
	dest[0][1] = m[1][0];
	dest[0][2] = m[2][0];
	dest[0][3] = m[3][0];
	dest[1][0] = m[0][1];
	dest[1][1] = m[1][1];
	dest[1][2] = m[2][1];
	dest[1][3] = m[3][1];
	dest[2][0] = m[0][2];
	dest[2][1] = m[1][2];
	dest[2][2] = m[2][2];
	dest[2][3] = m[3][2];
	dest[3][0] = m[0][3];
	dest[3][1] = m[1][3];
	dest[3][2] = m[2][3];
	dest[3][3] = m[3][3];
}

/*
 * tranpose mat4 and store result in same matrix
*/
void	mat4_transpose(t_mat4 m)
{
	t_mat4 d;

	mat4_transpose_to(m, d);
	mat4_copy(d, m);
}

/*
 * scale (multiply with scalar) matrix without
 * multiply matrix with scalar
*/
void	mat4_scale(t_mat4 m, float s)
{
	m[0][0] *= s;
	m[0][1] *= s;
	m[0][2] *= s;
	m[0][3] *= s;
	m[1][0] *= s;
	m[1][1] *= s;
	m[1][2] *= s;
	m[1][3] *= s;
	m[2][0] *= s;
	m[2][1] *= s;
	m[2][2] *= s;
	m[2][3] *= s;
	m[3][0] *= s;
	m[3][1] *= s;
	m[3][2] *= s;
	m[3][3] *= s;
}

/*
 * mat4 determinant
*/
float	mat4_det(t_mat4 mat)
{
	float t[6];
	float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
        e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
        i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
        m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3];

	t[0] = k * p - o * l;
	t[1] = j * p - n * l;
	t[2] = j * o - n * k;
	t[3] = i * p - m * l;
	t[4] = i * o - m * k;
	t[5] = i * n - m * j;
	return a * (f * t[0] - g * t[1] + h * t[2])
       - b * (e * t[0] - g * t[3] + h * t[4])
       + c * (e * t[1] - f * t[3] + h * t[5])
       - d * (e * t[2] - f * t[4] + g * t[5]);
}

/*
 * inverse mat4 and store in dest
*/
void	mat4_inv(t_mat4 mat, t_mat4 dest)
{
	float t[6];
	float det;
	float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
        e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
        i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
        m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3];

	t[0] = k * p - o * l;
	t[1] = j * p - n * l;
	t[2] = j * o - n * k;
	t[3] = i * p - m * l;
	t[4] = i * o - m * k;
	t[5] = i * n - m * j;
	dest[0][0] =  f * t[0] - g * t[1] + h * t[2];
	dest[1][0] =-(e * t[0] - g * t[3] + h * t[4]);
	dest[2][0] =  e * t[1] - f * t[3] + h * t[5];
	dest[3][0] =-(e * t[2] - f * t[4] + g * t[5]);
	dest[0][1] =-(b * t[0] - c * t[1] + d * t[2]);
	dest[1][1] =  a * t[0] - c * t[3] + d * t[4];
	dest[2][1] =-(a * t[1] - b * t[3] + d * t[5]);
	dest[3][1] =  a * t[2] - b * t[4] + c * t[5];
	t[0] = g * p - o * h;
	t[1] = f * p - n * h;
	t[2] = f * o - n * g;
	t[3] = e * p - m * h;
	t[4] = e * o - m * g;
	t[5] = e * n - m * f;
	dest[0][2] =  b * t[0] - c * t[1] + d * t[2];
	dest[1][2] =-(a * t[0] - c * t[3] + d * t[4]);
	dest[2][2] =  a * t[1] - b * t[3] + d * t[5];
	dest[3][2] =-(a * t[2] - b * t[4] + c * t[5]);
	t[0] = g * l - k * h;
	t[1] = f * l - j * h;
	t[2] = f * k - j * g;
	t[3] = e * l - i * h;
	t[4] = e * k - i * g;
	t[5] = e * j - i * f;
	dest[0][3] =-(b * t[0] - c * t[1] + d * t[2]);
	dest[1][3] =  a * t[0] - c * t[3] + d * t[4];
	dest[2][3] =-(a * t[1] - b * t[3] + d * t[5]);
	dest[3][3] =  a * t[2] - b * t[4] + c * t[5];
	det = 1.0f / (a * dest[0][0] + b * dest[1][0]
              + c * dest[2][0] + d * dest[3][0]);
	mat4_scale(dest, det);
}

/*
 * swap two matrix columns
*/
void
mat4_swap_col(t_mat4 mat, int col1, int col2)
{
	t_vec4 tmp;

  	vec4_copy(mat[col1], tmp);
  	vec4_copy(mat[col2], mat[col1]);
  	vec4_copy(tmp, mat[col2]);
}

/*!
 * wap two matrix rows
*/
void	mat4_swap_row(t_mat4 mat, int row1, int row2)
{
	t_vec4 tmp;

	tmp[0] = mat[0][row1];
	tmp[1] = mat[1][row1];
	tmp[2] = mat[2][row1];
	tmp[3] = mat[3][row1];
	mat[0][row1] = mat[0][row2];
	mat[1][row1] = mat[1][row2];
	mat[2][row1] = mat[2][row2];
	mat[3][row1] = mat[3][row2];
	mat[0][row2] = tmp[0];
	mat[1][row2] = tmp[1];
	mat[2][row2] = tmp[2];
	mat[3][row2] = tmp[3];
}

/*
 * helper for  R (row vector) * M (matrix) * C (column vector)
 *
 * rmc stands for Row * Matrix * Column
 * the result is scalar because R * M = Matrix1x4 (row vector),
 * then Matrix1x4 * Vec4 (column vector) = Matrix1x1 (Scalar)
*/
float	mat4_rmc(t_vec4 r, t_mat4 m, t_vec4 c)
{
	t_vec4	tmp;

	mat4_mulv(m, c, tmp);
	return vec4_dot(r, tmp);
}

/*
** convert degree to radians
*/

float	deg_to_rad(float deg)
{
	return (deg * _PI / 180.0f);
}

/*
** convert radians to degree
*/

float	rad_to_deg(float rad)
{
	return (rad * 180.0f / _PI);
}

#endif