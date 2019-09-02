/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 13:52:46 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/02 20:56:20 by dmelessa         ###   ########.fr       */
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
float	sphere_intersection(t_obj *obj, t_ray *ray)
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
			if ((t = (-coefs[b] + coefs[d]) / coefs[a]) < 0.0f)
				return (FALSE);
		obj->t = t;
		return (TRUE);

		vec3_scale(ray->vec, (-coefs[b] - sqrtf(coefs[d])) * 0.5f / coefs[a], obj->surface_normal);	//D * t
		vec3_sum(obj->surface_normal, tmp, obj->surface_normal);									//D * t + O - C = P - C
		vec3_sum(obj->surface_normal, obj->origin, obj->hit_point);					// D * t + O hit point
		vec3_normalize(obj->surface_normal); 										// nrm(P - C)
		// printf("a: %f b:%f c:%f d:%f t:%f p:%f %f %f N:%f %f %f\n", coefs[a], coefs[b], coefs[c], coefs[d], (-coefs[b] - sqrtf(coefs[d])) * 0.5 / coefs[a], tmp[0], tmp[1], tmp[2], obj->surface_normal[0],obj->surface_normal[1], obj->surface_normal[2]);
	}
}
