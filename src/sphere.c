/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 13:52:46 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/09 09:31:01 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** C is the center of the sphere
** r is the radius of the sphere
** a   = D|D
** b/2 = D|X
** c   = X|X - r*r
** Surface normal is N=nrm(P-C).
*/
t_bool	sphere_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4		tmp;
	t_vec4		coefs;
	t_sphere	sp;
	float		t;

	sp = *(t_sphere *)(obj->data);
	vec3_sub(ray->point, obj->origin, tmp); // O - C //L
	coefs[a] = vec3_norm2(ray->vec);
	coefs[b] = 2.0f * vec3_dot(ray->vec, tmp);//tca/2
	coefs[c] = vec3_norm2(tmp) - sp.radius * sp.radius;
	coefs[d] = coefs[b] * coefs[b] - 4.0f * coefs[a] * coefs[c];
	if (coefs[d] >= 0.0f)
	{
		coefs[a] *= 2.0f;
		coefs[d] = sqrtf(coefs[d]);
		t = (-coefs[b] -coefs[d]) / coefs[a]; //t = (-b +- sqrt(D))/(2a)
		if (t < 0.0f)
			if ((t = (-coefs[b] - coefs[d]) / coefs[a]) < 0.0f)
				return (FALSE);
		obj->t = t;
		return (TRUE);
	}
	return (FALSE);
}
