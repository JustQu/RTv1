/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 21:55:57 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/13 16:39:23 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTM_TYPES_H
# define RTM_TYPES_H

# define RTM_E				2.71828182845904523536028747135266250
# define RTM_LOG2E			1.44269504088896340735992468100189214
# define RTM_LOG10E			0.434294481903251827651128918916605082
# define RTM_LN2			0.693147180559945309417232121458176568
# define RTM_LN10			2.30258509299404568401799145468436421
# define RTM_PI				3.14159265358979323846264338327950288
# define RTM_PI_2			1.57079632679489661923132169163975144
# define RTM_PI_4			0.785398163397448309615660845819875721
# define RTM_1_PI			0.318309886183790671537767526745028724
# define RTM_2_PI			0.636619772367581343075535053490057448
# define RTM_2_SQRTPI 		1.12837916709551257389615890312154517
# define RTM_SQRT2			1.41421356237309504880168872420969808
# define RTM_SQRT1_2		0.707106781186547524400844362104849039

typedef float	t_vec2[2];
typedef float	t_vec3[3];
typedef float	t_vec4[4];
typedef float	t_mat3[3][3];
typedef float	t_mat4[4][4];
typedef t_vec4	t_versor;

enum f
{
	ox, oy, oz, ok
};

#endif

