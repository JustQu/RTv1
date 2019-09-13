/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:09:18 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/13 18:14:02 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_sphere_normal(t_obj *obj, t_ray *ray)
{
	vec3_sub(obj->hit_point, obj->c_s, obj->surf_normal);
	vec3_normalize(obj->surf_normal);
}

void		get_plane_normal(t_obj *obj, t_ray *ray)
{
	vec3_copy(((t_plane *)obj->data)->nv, obj->surf_normal);
	vec3_negate(obj->surf_normal);
}

void		get_cone_normal(t_obj *obj, t_ray *ray)
{
	float	m;

	vec3_sub(obj->hit_point, obj->c_s, obj->surf_normal);
	m = vec3_dot(obj->surf_normal, ((t_cone *)(obj->data))->dir);
	vec3_scale(((t_cone *)(obj->data))->dir, m *
	((t_cone *)(obj->data))->k2, obj->surf_normal);
	vec3_sub(obj->hit_point, obj->surf_normal, obj->surf_normal);
	vec3_sub(obj->surf_normal, obj->c_s, obj->surf_normal);
	normalize(obj->surf_normal);
}

void		get_cylinder_normal(t_obj *obj, t_ray *ray)
{
	float	m;

	vec3_sub(obj->hit_point, obj->c_s, obj->surf_normal);
	m = vec3_dot(obj->surf_normal, ((t_cylinder *)(obj->data))->dir);
	vec3_scale(((t_cylinder *)(obj->data))->dir, m, obj->surf_normal);
	vec3_sub(obj->hit_point, obj->surf_normal, obj->surf_normal);
	vec3_sub(obj->surf_normal, obj->c_s, obj->surf_normal);
	vec3_normalize(obj->surf_normal);
}

void		get_surface_normal(t_obj *obj, t_ray *ray)
{
	if (obj->type == sphere)
		get_surface_normal(obj, ray);
	else if (obj->type == plane)
		get_plane_normal(obj, ray);
	else if (obj->type == cone)
		get_cone_normal(obj, ray);
	else if (obj->type == cylinder)
		get_cylinder_normal(obj, ray);
}
