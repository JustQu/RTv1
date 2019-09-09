/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/09 19:02:10 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "nmmintrin.h"
#include "immintrin.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*p;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	p = img->data;
	p = (p + img->size_line * y) + ((x * img->bpp) >> 3);
	*(int *)p = color;
}

/*
**A ray is defined in the following way:
**	P = O + D*t
**where O is the ray origin and D is the ray direction.From this we create a
**shape-specific equation that we solve for scalar t. Obtained t is actually
**the distance of the hit point from the ray origin. If t is negative, the hit
**point lies behind the origin, and is beyond our interest
**Vector dot product is denoted with "|".
*/

/*
** Definition:
** C is the vertex of the cone
** V is the axis vector
** k is the tangent of half angle of the cone
** a   = D|D - (1+k*k)*(D|V)^2
** b/2 = D|X - (1+k*k)*(D|V)*(X|V)
** c   = X|X - (1+k*k)*(X|V)^2
** N = nrm( P-C - (1+k*k)*V*m )
*/
t_bool	cone_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec4	coef;
	t_cone	*cn;

	cn = (t_cone *)obj->data;
	vec3_sub(ray->point, obj->camera_space, tmp);
	coef[a] = vec3_dot(ray->vec, ray->vec) - cn->k2 * pow2(vec3_dot(ray->vec, cn->dir));
	coef[b] = vec3_dot(ray->vec, tmp) - cn->k2 * vec3_dot(ray->vec, cn->dir) * vec3_dot(tmp, cn->dir);
	coef[b] *= 2;
	coef[c] = vec3_dot(tmp, tmp) - cn->k2 * (pow2(vec3_dot(tmp, cn->dir)));
	coef[d] = pow2(coef[b]) - 4 * coef[a] * coef[c];
	if (coef[d] >= 0.0f)
	{
		obj -> t = (-coef[b] - sqrtf(coef[d])) * 0.5 / coef[a];
		if (obj -> t <= 0.0f)
			obj -> t = (-coef[b] - sqrtf(coef[d])) * 0.5 / coef[a];
		return (obj -> t >= 0.0f);
	}
	return (FALSE);
}

/*
** C is the start cap point of the cylinder
** V is a unit length vector that determines cylinder's axis
** r is the cylinder's radius
** a   = D|D - (D|V)^2
** b/2 = D|X - (D|V)*(X|V)
** c   = X|X - (X|V)^2 - r*r
*/

t_bool		cylinder_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4		tmp;
	t_vec4		coefs;
	t_cylinder	cl;

	cl = *(t_cylinder *)obj->data;
	vec3_sub(ray->point, obj->camera_space, tmp);
	coefs[a] = vec3_norm2(ray->vec) - pow2(vec3_dot(ray->vec, cl.direction));
	coefs[b] = vec3_dot(ray->vec, tmp) - vec3_dot(ray->vec, cl.direction) * vec3_dot(tmp, cl.direction);
	coefs[b] *= 2.0f;
	coefs[c] = vec3_norm2(tmp) - pow2(vec3_dot(tmp, cl.direction)) - cl.radius * cl.radius;
	coefs[d] = pow2(coefs[b]) - 4.0f * coefs[a] * coefs[c];
	if (coefs[d] >= 0.0f)
	{
		coefs[a] *= 2.0f;
		coefs[d] = sqrtf(coefs[d]);
		obj->t = (-coefs[b] - coefs[d]) / coefs[a];
		if (obj -> t >= 0.0f)
			return (TRUE);
	}
	return (FALSE);
}

/*
**Definition:
** C is a point that lies on the plane
** V is the plane normal (unit length)
** t = -X|V / D|V
*/
t_bool	plane_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec2	coefs;
	t_plane pl;
	float	denom;

	pl = *(t_plane *)obj->data;
	vec3_sub(obj->camera_space, ray->point, tmp);
	denom = vec3_dot(pl.nv, ray->vec);
	coefs[a] = -vec3_dot(pl.nv, tmp);
	coefs[b] = vec3_dot(pl.nv, ray->vec);
	if (denom > 1e-6f)
	{
		vec3_sub(obj->camera_space, ray->point, tmp);
		obj -> t = vec3_dot(tmp, pl.nv) / denom;
		return (obj -> t >= 0);
		if ((obj->t = coefs[a] / coefs[b]) >= 0.0f)
			return (TRUE);
		if (coefs[b] < 0.0f)
		{
			obj->t = -obj->t;
			return (TRUE);
		}
		return (FALSE);
	}
	return (FALSE);
}

int			intersection(t_obj *obj, t_ray *ray)
{
	t_bool	is_hit;

	is_hit = FALSE;
	if (obj->type == sphere)
		is_hit = sphere_intersection(obj, ray);
	else if (obj->type == plane)
		is_hit = plane_intersection(obj, ray);
	else if (obj->type == cone)
		is_hit = cone_intersection(obj, ray);
	else if (obj->type == cylinder)
		is_hit = cylinder_intersection(obj, ray);
	return (is_hit);
}

void		get_hit_point(t_obj *obj, t_ray *ray)
{
	vec3_scale(ray->vec, obj->t, obj->hit_point);
	vec3_sum(obj->hit_point, ray->point, obj->hit_point);
}

/*
** get normal to obj surface
** use this after get_hit_point call
*/
void		get_surface_normal(t_obj *obj, t_ray *ray)
{
	float	m;

	if (obj->type == sphere)
	{
		vec3_sub(obj->hit_point, obj->camera_space, obj->surface_normal);
		vec3_normalize(obj->surface_normal);
	}
	else if (obj->type == plane)
	{
		vec3_copy(((t_plane *)obj->data)->nv, obj->surface_normal);
		vec3_negate(obj->surface_normal);
	}
	else if (obj->type == cone)
	{
		vec3_sub(obj->hit_point, obj->camera_space, obj->surface_normal); // X = O - C
		m = vec3_dot(obj->surface_normal, ((t_cone *)(obj->data))->dir); // m = D|V * t + X|V
		vec3_scale(((t_cone *)(obj->data))->dir, m * ((t_cone *)(obj->data))->k2, obj->surface_normal); // (1 + k * k) * V * m
		vec3_sub(obj->hit_point, obj->surface_normal, obj->surface_normal);
		vec3_sub(obj->surface_normal, obj->camera_space, obj->surface_normal);
		normalize(obj->surface_normal);
	}
	else if (obj->type == cylinder)
	{
		vec3_sub(obj->hit_point, obj->camera_space, obj->surface_normal);
		m = vec3_dot(obj->surface_normal, ((t_cylinder *)(obj->data))->direction);
		vec3_scale(((t_cylinder *)(obj->data))->direction, m, obj->surface_normal);
		vec3_sub(obj->hit_point, obj->surface_normal, obj->surface_normal);
		vec3_sub(obj->surface_normal, obj->camera_space, obj->surface_normal);
		vec3_normalize(obj->surface_normal);
	}
}

t_obj		*get_first_intesection(t_obj *objs, unsigned nobjs, t_ray *ray)
{
	int		i;
	int		hit_id;
	float	hit_distance;

	i = -1;
	hit_id = -1;
	hit_distance = __FLT_MAX__;
	while (++i < nobjs)
	{
		if (intersection(objs + i, ray) && (objs + i)->t < hit_distance)
		{
			if (hit_id != -1)
				(objs + hit_id)->t = INFINITY;
			hit_distance = (objs + i)->t;
			hit_id = i;
		}
	}
	if (hit_id != -1)
	{
		get_hit_point(objs + hit_id, ray);
		get_surface_normal(objs + hit_id, ray);
		(objs + hit_id)->t = INFINITY;
	}
	return ((hit_id != -1 && hit_distance < 1000.0f) ? objs + hit_id : NULL);
}

void		reflect(t_vec3 i, t_vec3 n, t_vec3 dest)
{
	float	k;
	t_vec3	tmp;

	k = vec3_dot(i, n);
	vec3_scale(n, 2 * k, tmp);
	vec3_sub(i, tmp, dest);
}

t_ray		cast_shadow_ray(t_vec3 start, t_light_source *light)
{
	t_ray	shadow_ray;
	t_vec3	bias;

	//vec3_broadcast(1e-1, bias);
	vec3_copy(start, shadow_ray.point);
	//vec3_sum(shadow_ray.point, bias, shadow_ray.point);
	vec3_sub(light->camera_space, start, shadow_ray.vec);
	normalize(shadow_ray.vec);
	return (shadow_ray);
}

t_color		get_point_color(t_world *world, t_obj *obj, t_ray *ray)
{
	int		i;
	float	diffuse_light;
	float	specular_light;
	t_obj	*shadow_obj;
	t_vec3	r;
	t_vec4	light_dir;
	t_color	color;
	t_ray	shadow_ray;

	i = -1;
	diffuse_light= 0.0f;
	specular_light = 0.0f;
	while (++i < world->nlights)
	{
		shadow_ray = cast_shadow_ray(obj->hit_point, world->lights + i);
		if ((shadow_obj = get_first_intesection(world->objs, world->nobjs, &shadow_ray)) != NULL)
			if (shadow_obj != obj && vec3_distance(obj->hit_point, (world->lights + i)->camera_space) > vec3_distance(obj->hit_point, shadow_obj->hit_point))
				continue;
		vec3_sub((world->lights + i)->camera_space, obj->hit_point, light_dir);
		vec3_normalize(light_dir);
		diffuse_light += (world->lights + i)->intensity * max(0, vec3_dot(light_dir, obj->surface_normal));
		reflect(light_dir, obj->surface_normal, r);
		specular_light += (world->lights + i)->intensity * powf(max(0.0f, dot(r, ray->vec)), obj->material.n);
	}
	color.bgra[0] = obj->material.diffuse_color.bgra[0] * (diffuse_light * obj->material.Kd + specular_light * obj->material.Ks);
	color.bgra[1] = obj->material.diffuse_color.bgra[1] * (diffuse_light * obj->material.Kd + specular_light * obj->material.Ks);
	color.bgra[2] = obj->material.diffuse_color.bgra[2] * (diffuse_light * obj->material.Kd + specular_light * obj->material.Ks);
	color.bgra[3] = obj->material.diffuse_color.bgra[3] * (diffuse_light * obj->material.Kd + specular_light * obj->material.Ks);
	return (color);
}

//пускаем луч, ищем пересечение с объектом,есть, если hit_point > INFINITE
//получаем цвет в точке
//пускаем дополнительные лучи
t_color		trace_ray(t_param *p, t_ray *ray)
{
	t_obj	*obj;
	t_color	color;

	color.color = BACKGROUND;
	obj = get_first_intesection(p->world.objs, p->world.nobjs , ray);
	if (obj)
	{
		return (color = get_point_color(&(p->world), obj, ray));
	}
	return (color);
}

/*
** this function calculate all pixels for our scene
*/
void	render(t_param *p)
{
	t_ray	ray;
	t_vec2	iters;
	t_color	color;

	vec3_zero(ray.point);
	iters[oy] = -1;
	while (++iters[oy] < HEIGHT)
	{
		iters[ox] = -1;
		while (++iters[ox] < WIDTH)
		{
			vec4_copy((t_vec4){1, 1, 1, 1}, ray.vec);
			ray.vec[oy] = (1 - 2 * ((iters[oy] + 0.5) * p->camera.inv_height)) * p->camera.angle;
			ray.vec[ox] = (2 * ((iters[ox] + 0.5) * p->camera.inv_width) - 1) * p->camera.angle * p->camera.aspectratio;
			normalize(ray.vec);
			color = trace_ray(p, &ray);
			put_pixel(&p->img, iters[ox], iters[oy], color.color);
		}
	}
}
