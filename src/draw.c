/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/04 19:33:36 by dmelessa         ###   ########.fr       */
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
float	cone_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec4	coef;
	t_cone	cn;

	cn = *(t_cone *)obj->data;
	cn.k = tan(cn.angle);
	cn.k2 = 1 + cn.k * cn.k;
	vec3_sub(ray->point, obj->origin, tmp);
	coef[a] = vec3_dot(ray->vec, ray->vec) - cn.k2 * pow2(vec3_dot(ray->vec, cn.dir));
	coef[b] = vec3_dot(ray->vec, tmp) - cn.k2 * vec3_dot(ray->vec, cn.dir) * vec3_dot(tmp, cn.dir);
	coef[b] *= 2;
	coef[c] = vec3_dot(tmp, tmp) - cn.k2 * (pow2(vec3_dot(tmp, cn.dir)));
	coef[d] = pow2(coef[b]) - 4 * coef[a] * coef[c];
	if (coef[d] >= 0.0f)
	{
		vec3_scale(ray->vec, (-coef[b] - sqrtf(coef[d])) * 0.5 / coef[a], obj->surface_normal); //D * t
		vec3_sum(obj->surface_normal, tmp, obj->surface_normal);								//D * t + O - C
		vec3_sum(obj->surface_normal, obj->origin, obj->hit_point);								//D * t + O
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

t_bool		cylinder_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4		tmp;
	t_vec4		coefs;
	t_cylinder	cl;

	cl = *(t_cylinder *)obj->data;
	vec3_sub(ray->point, obj->origin, tmp);
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
		if (obj -> t < 0.0f)
			obj -> t = (-coefs[b] + coefs[d]) / coefs[a];
				return TRUE;
		return (TRUE);
		vec3_scale(ray->vec, (-coefs[b] - sqrtf(coefs[d])) * 0.5 / coefs[a], obj->surface_normal); //D * t
		vec3_sum(obj->surface_normal, tmp, obj->surface_normal);								//D * t + O - C
		vec3_sum(obj->surface_normal, obj->origin, obj->hit_point);								//D * t + O
		vec3_scale(cl.direction, (vec3_dot(ray->vec, cl.direction) * (-coefs[b] - sqrtf(coefs[d])) * 0.5 / coefs[a] + vec3_dot(tmp, cl.direction)), tmp);// V*m, m = D|V*t + X|V
		vec3_sub(obj->surface_normal, tmp, obj->surface_normal);
		vec3_normalize(obj->surface_normal);
	}
	return (FALSE);
}

/*
**Definition:
** C is a point that lies on the plane
** V is the plane normal (unit length)
** t = -X|V / D|V
*/
float	plane_intersection(t_param *p, t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec2	coefs;
	t_plane pl;

	pl = *(t_plane *)obj->data;
	vec3_sub(obj->origin, ray->point, tmp);
	coefs[a] = -vec3_dot(pl.nv, tmp);
	coefs[b] = vec3_dot(pl.nv, ray->vec);
	if (coefs[b] != 0 && coefs[a] / coefs[b] > 0)
	{
		vec3_scale(ray->vec, coefs[a] / coefs[b], obj->hit_point);
		vec3_sum(obj->hit_point, ray->vec, obj->hit_point);
		vec3_copy(pl.nv, obj->surface_normal);
		if (coefs[b] < 0)
			vec3_negate(obj->surface_normal);
	}
}

int			intersection(t_obj *obj, t_ray *ray)
{
	t_bool	is_hit;

	is_hit = FALSE;
	if (obj->type == sphere)
		is_hit = sphere_intersection(obj, ray);
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
		vec3_sub(obj->hit_point, obj->origin, obj->surface_normal);
		vec3_normalize(obj->surface_normal);
	}
	else if (obj->type == cone)
	{
		
	}
	else if (obj->type == cylinder)
	{
		t_vec3	tmp;
		vec3_sum(obj->hit_point, obj->origin, obj->surface_normal);
		m = vec3_dot(obj->surface_normal, ((t_cylinder *)(obj->data))->direction);
		//else
		vec3_scale(((t_cylinder *)(obj->data))->direction, m, obj->surface_normal);
		vec3_sub(obj->hit_point, obj->surface_normal, obj->surface_normal);
		vec3_sub(obj->surface_normal, obj->origin, obj->surface_normal);
		vec3_normalize(obj->surface_normal);
		//vec3_negate(obj->surface_normal);
	}
}

t_obj		*get_first_intesection(t_obj *objects, unsigned nobjects, t_ray *ray)
{
	int		i;
	int		hit_id;
	float	hit_distance;

	i = -1;
	hit_id = -1;
	hit_distance = __FLT_MAX__;
	while (++i < nobjects)
	{	
		if (intersection(objects + i, ray) && (objects + i)->t < hit_distance)
		{
			if (hit_id != -1)
				(objects + hit_id)->t = INFINITY;
			hit_distance = (objects + i)->t;
			hit_id = i;
		}
	}
	if (hit_id != -1)
	{
		get_hit_point(objects + hit_id, ray);
		get_surface_normal(objects + hit_id, ray);
		(objects + hit_id)->t = INFINITY;
	}
	return ((hit_id != -1 && hit_distance < 1000.0f) ? objects + hit_id : NULL);
}

static int	get_light(int start, double pr)
{
	return (int)(pr * start);
}

int			new_color(int start, double pr)
{
	int	r;
	int	g;
	int b;

	b = get_light(start & 0xff, pr);
	g = get_light(start >> 8 & 0xff, pr);
	r = get_light(start >> 16 & 0xff, pr);
	return ((r << 16) | (g << 8) | b);
}

t_color		get_point_color(t_world *world, t_obj *obj, t_ray *ray)
{
	int		i;
	float	diffuse_light_intensity;
	t_vec4	light_dir;
	t_color	color;

	i = -1;
	diffuse_light_intensity = 0.0f;
	while (++i < world->nlights)
	{
		vec3_sub((world->lights + i)->origin, obj->hit_point, light_dir);
		//vec3_negate(light_dir);
		vec3_normalize(light_dir);
		diffuse_light_intensity += (world->lights + i)->intensity * max(0, vec3_dot(light_dir, obj->surface_normal));
	}
	color.bgra[0] = obj->material.diffuse_color.bgra[0] * diffuse_light_intensity;
	color.bgra[1] = obj->material.diffuse_color.bgra[1] * diffuse_light_intensity;
	color.bgra[2] = obj->material.diffuse_color.bgra[2] * diffuse_light_intensity;
	color.bgra[3] = obj->material.diffuse_color.bgra[3] * diffuse_light_intensity;
	//color.color = new_color(obj->material.diffuse_color.color, diffuse_light_intensity);
	return (color);
}

t_color		get_albedo_color(t_world *world, t_obj *obj, t_ray *ray)
{
	int		i;
	float	diffuse_light_intensity;
	t_vec4	light_dir;
	t_color	color;

	i = -1;
	diffuse_light_intensity = 0;
	while (++i < world->nlights)
	{
		vec3_sub((world->lights + i)->origin, obj->hit_point, light_dir);
		vec3_normalize(light_dir);
		diffuse_light_intensity += (world->lights + i)->intensity * max(0, vec3_dot(light_dir, obj->surface_normal));
	}
	//color = (t_color){.bgra[0] = obj->material.diffuse_color.bgra[0] * diffuse_light_intensity,
	//					.bgra[1] = obj->material.diffuse_color.bgra[1] * diffuse_light_intensity,
	//					.bgra[2] = obj->material.diffuse_color.bgra[2] * diffuse_light_intensity};
	color.color = new_color(obj->material.diffuse_color.color, diffuse_light_intensity);
	return (color);
}


//пускаем луч, ищем пересечение с объектом,есть, если hit_point > INFINITE
//получаем цвет в точке
//пускаем дополнительные лучи
t_color		trace_ray(t_param *p, t_ray *ray)
{
	t_obj	*obj;
	t_color	color;

	color.color = 0x1a334d;
	obj = get_first_intesection(p->world.objects, p->world.nobjects , ray);
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
	
	FILE *f = fopen("wer", "w");
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
			if (color.color == 0)
				(1 == 1);
			color.color = 0x1a334d;
		}
	}
}
