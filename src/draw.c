/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/29 17:21:39 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "rtmath.h"
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
** C is the center of the sphere
** r is the radius of the sphere
** a   = D|D
** b/2 = D|X
** c   = X|X - r*r
** Surface normal is N=nrm(P-C).
*/
void	sphere_function(t_obj *obj, t_ray *ray)
{
	t_vec4		tmp;
	t_vec4		coefs;
	t_sphere	sp;

	sp = *(t_sphere *)(obj->data);
	vec3_sub(ray->point, sp.origin, tmp); // O - C
	coefs[a] = vec3_norm2(ray->vec);
	coefs[b] = 2.0f * vec3_dot(ray->vec, tmp);
	coefs[c] = vec3_norm2(tmp) - sp.radius * sp.radius;
	coefs[d] = coefs[b] * coefs[b] - 4.0f * coefs[a] * coefs[c];
	if (coefs[d] >= 0.0f)
	{
		vec3_scale(ray->vec, (-coefs[b] - sqrtf(coefs[d])) * 0.5f / coefs[a], obj->surface_normal);	//D * t
		vec3_sum(obj->surface_normal, tmp, obj->surface_normal);									//D * t + O - C = P - C
		vec3_sum(obj->surface_normal, sp.origin, obj->hit_point);					// D * t + O hit point
		vec3_normalize(obj->surface_normal); 										// nrm(P - C)
		// printf("a: %f b:%f c:%f d:%f t:%f p:%f %f %f N:%f %f %f\n", coefs[a], coefs[b], coefs[c], coefs[d], (-coefs[b] - sqrtf(coefs[d])) * 0.5 / coefs[a], tmp[0], tmp[1], tmp[2], obj->surface_normal[0],obj->surface_normal[1], obj->surface_normal[2]);
	}
	else
	{
		vec3_broadcast(INFINITY, obj->hit_point); // set infinite to
	}
}

/*
** Definition:
** C is the vertex of the cone
** V is the axis vector
** k is the tangent of half angle of the cone
** a   = D|D - (1+k*k)*(D|V)^2
** b/2 = D|X - (1+k*k)*(D|V)*(X|V)
** c   = X|X - (1+k*k)*(X|V)^2
** ь
** N = nrm( P-C - (1+k*k)*V*m )
*/
void	conef(t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec4	coef;
	t_cone	cn;

	cn = *(t_cone *)obj->data;
	cn.k = tan(cn.angle);
	cn.k2 = 1 + cn.k * cn.k;
	vec3_sub(ray->point, cn.origin, tmp);
	coef[a] = vec3_dot(ray->vec, ray->vec) - cn.k2 * pow2(vec3_dot(ray->vec, cn.dir));
	coef[b] = vec3_dot(ray->vec, tmp) - cn.k2 * vec3_dot(ray->vec, cn.dir) * vec3_dot(tmp, cn.dir);
	coef[b] *= 2;
	coef[c] = vec3_dot(tmp, tmp) - cn.k2 * (pow2(vec3_dot(tmp, cn.dir)));
	coef[d] = pow2(coef[b]) - 4 * coef[a] * coef[c];
	if (coef[d] >= 0.0f)
	{
		vec3_scale(ray->vec, (-coef[b] - sqrtf(coef[d])) * 0.5 / coef[a], obj->surface_normal); //D * t
		vec3_sum(obj->surface_normal, tmp, obj->surface_normal);								//D * t + O - C
		vec3_sum(obj->surface_normal, cn.origin, obj->hit_point);								//D * t + O
		vec3_scale(cn.dir, (vec3_dot(ray->vec, cn.dir) * (-coef[b] - sqrtf(coef[d])) * 0.5 / coef[a] + vec3_dot(tmp, cn.dir)) * cn.k2, tmp);// (1+k*k)*V*m, m = D|V*t + X|V
		vec3_sub(obj->surface_normal, tmp, obj->surface_normal);
		vec3_normalize(obj->surface_normal);
	}
}

/*
** C is the start cap point of the cylinder
** V is a unit length vector that determines cylinder's axis
** r is the cylinder's radius
** a   = D|D - (D|V)^2
** b/2 = D|X - (D|V)*(X|V)
** c   = X|X - (X|V)^2 - r*r
*/

void		cylinder_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4		tmp;
	t_vec4		coefs;
	t_cylinder	cl;

	cl = *(t_cylinder *)obj->data;
	vec3_sub(ray->point, cl.origin, tmp);
	coefs[a] = vec3_norm2(ray->vec) - pow2(vec3_dot(ray->vec, cl.direction));
	coefs[b] = vec3_dot(ray->vec, tmp) - vec3_dot(ray->vec, cl.direction) * vec3_dot(tmp, cl.direction);
	coefs[b] *= 2.0f;
	coefs[c] = vec3_norm2(tmp) - pow2(vec3_dot(tmp, cl.direction)) - cl.radius * cl.radius;
	coefs[d] = pow2(coefs[b]) - 4.0f * coefs[a] * coefs[c];
	if (coefs[d] >= 0.0f)
	{
		vec3_scale(ray->vec, (-coefs[b] - sqrtf(coefs[d])) * 0.5 / coefs[a], obj->surface_normal); //D * t
		vec3_sum(obj->surface_normal, tmp, obj->surface_normal);								//D * t + O - C
		vec3_sum(obj->surface_normal, cl.origin, obj->hit_point);								//D * t + O
		vec3_scale(cl.direction, (vec3_dot(ray->vec, cl.direction) * (-coefs[b] - sqrtf(coefs[d])) * 0.5 / coefs[a] + vec3_dot(tmp, cl.direction)), tmp);// V*m, m = D|V*t + X|V
		vec3_sub(obj->surface_normal, tmp, obj->surface_normal);
		vec3_normalize(obj->surface_normal);
	}
}

void	planef(t_param *p, t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec2	ab;
	t_plane pl;

	pl = *(t_plane *)obj->data;
	vec3_sub(pl.origin, ray->point, tmp);
	ab[a] = vec3_dot(pl.nv, tmp);
	ab[b] = vec3_dot(pl.nv, ray->vec);
	if (ab[a] / ab[b] > 0)
		put_pixel(&p->img, ray->point[ox], ray->point[1], 0x0faaf0);
}

int			intersection(t_obj *obj, t_ray *ray)
{
	if (obj->type == sphere)
	{
		sphere_function(obj, ray);
	}
	else if (obj->type == cone)
		conef(obj, ray);
	else if (obj->type == cylinder)
		cylinder_intersection(obj, ray);
	if (obj->hit_point[0] < INFINITY)
		return (1);
	return (0);
}

t_obj		*get_first_intesection(t_obj *objects, unsigned nobjects, t_ray *ray)
{
	int		i;

	i = -1;
	while (++i < nobjects)
	{
		if (intersection(objects + i, ray))
			return (objects + i);
	}
	return (NULL);
}

t_color		get_point_color(t_world *world, t_obj *obj, t_ray *ray)
{
	int i;
	float diffuse_light_intensity;
	t_vec4 light_dir;
	t_color color;

	i = -1;
	diffuse_light_intensity = 0;
	while (++i < world->nlights)
	{
		vec3_sub((world->lights + i)->origin, obj->hit_point, light_dir);
		vec3_normalize(light_dir);
		diffuse_light_intensity += (world->lights + i)->intensity * max(0, vec3_dot(light_dir, obj->surface_normal));
	}
	color.color = obj->material.diffuse_color.color * diffuse_light_intensity;
	// color.color = obj->material.diffuse_color.color;
	return (color);
}

//пускаем луч, ищем пересечение с объектом,есть, если hit_point > INFINITE
//получаем цвет в точке
//пускаем дополнительные лучи
t_color		trace_ray(t_param *p, t_ray *ray)
{
	t_obj	*obj;
	t_color	color;

	obj = get_first_intesection(p->world.objects, p->world.nobjects , ray);
	if (obj)
	{
		color = get_point_color(&(p->world), obj, ray);
		put_pixel(&p->img, ray->point[0], ray->point[1], color.color);
	}
}

/*
** this function calculate all pixels for our scene
*/
void	render(t_param *p)
{
	t_ray	ray;
	t_vec2	iters;
	vec4_copy((t_vec4){0, 0, 1, 1}, ray.vec);
	vec3_zero(ray.point);
	iters[oy] = -1;
	while (++iters[oy] < HEIGHT)
	{
		ray.point[1] = iters[oy];
		iters[ox] = -1;
		while (++iters[ox] < WIDTH)
		{
			ray.point[0] = iters[ox];
			trace_ray(p, &ray);
		}
	}
}
