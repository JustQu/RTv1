/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:29:51 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/30 22:29:51 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VEC4_H
# define VEC4_H

# include "rt_types.h"

# define VEC4_ONE_INIT   {1.0f, 1.0f, 1.0f, 1.0f}
# define VEC4_ZERO_INIT  {0.0f, 0.0f, 0.0f, 0.0f}
# define VEC4_ONE        ((t_vec4)VEC4_ONE_INIT)
# define VEC4_ZERO       ((t_vec4)VEC4_ZERO_INIT)

/*
** init vec4 using vec3
*/
void	vec3_to_vec4(t_vec3 v3, float last, t_vec4 dest);

/*
**copy all members of [v] to dest
*/
void	vec4_copy(t_vec4 v, t_vec4 dest);

/*
**make vector zero
*/
void	vec4_zero(t_vec4 v);

/*
**make vector one
*/
void	vec4_one(t_vec4 v);

/*
**vec4 dot product
*/
float	vec4_dot(t_vec4 a, t_vec4 b);

/*
**norm * norm(magnitude) of vec
*/
float	vec4_norm2(t_vec4 v);

/*
**norm(magnitude) of vec4
*/
float	vec4_norm(t_vec4 v);

/*
**add b vector to a vector store result in dest
*/
void	vec4_sum(t_vec4 a, t_vec4 b, t_vec4 dest);

/*
**add scalar to v vector store result in dest (d = v + vec(s))
*/
void	vec4_adds(t_vec4 v, float s, t_vec4 dest);

/*
**substract b vector from a vector store result in dest (d = a - b)
*/
void	vec4_sub(t_vec4 a, t_vec4 b, t_vec4 dest);

/*
**substract scalar from v vector sore result in dest (d = v - vec(s))
*/
void	vec4_subs(t_vec4 v, float s, t_vec4 dest);

/*
**multiply two vector (component-wise multuplication)
*/
void	vec4_mul(t_vec4 a, t_vec4 b, t_vec4 dest);

/*
**multiply/scale vec4 vector with scalar: result = v * s
*/
void	vec4_scale(t_vec4 a, float s, t_vec4 dest);

/*
**make vec4 vector scale as specified: result = unit(v) * s
*/
void	vec4_scale_as(t_vec4 v, float s, t_vec4 dest);

/*
**negate vector components and store result in dest
*/
void	vec4_negate_to(t_vec4 v, t_vec4 dest);

/*
**flip sign of all vec4 members
*/
void 	vec4_negate(t_vec4 v);

/*
**normalize vec4 to dest
*/
void	vec4_normalize_to(t_vec4 v, t_vec4 dest);

/*
**normalize vec4 and store result in same vec
*/
void	vec4_normalize(t_vec4 v);

/*
**distance between two vectors
*/
float	vec4_distance(t_vec4 a, t_vec4 b);

/*
**fill a vectir with specified value
*/
void	vec4_broadcast(float val, t_vec4 d);

/*
**linear interpolation between two vector
**formula: from + s * (to - from)
**t - interpolant (amount) clamped between 0 and 1
*/
void	vec4_lerp(t_vec4 from, t_vec4 to, float t, t_vec4 dest);

/*
**mul vector with scalar and add result to sum
*/
void	vec4_muladds(t_vec4 a, float s, t_vec4 dest);

#endif
