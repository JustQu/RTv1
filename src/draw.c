/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/13 18:14:31 by dwalda-r         ###   ########.fr       */
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

	vec3_copy(start, shadow_ray.point);
	vec3_sub(light->c_s, start, shadow_ray.vec);
	normalize(shadow_ray.vec);
	return (shadow_ray);
}

t_color		get_point_color(t_world *world, t_obj *obj, t_ray *ray)
{
	int		i;
	float	diff_light;
	float	spec_light;
	t_obj	*shadow_obj;
	t_vec3	r;
	t_vec4	light_dir;
	t_color	color;
	t_ray	shadow_ray;

	i = -1;
	diff_light= 0.0f;
	spec_light = 0.0f;
	while (++i < world->nlights)
	{
		shadow_ray = cast_shadow_ray(obj->hit_point, world->lights + i);
		if ((shadow_obj = get_first_intesection(world->objs, world->nobjs, &shadow_ray)) != NULL)
			if (shadow_obj != obj && vec3_distance(obj->hit_point, (world->lights + i)->c_s) > vec3_distance(obj->hit_point, shadow_obj->hit_point))
				continue;
		vec3_sub((world->lights + i)->c_s, obj->hit_point, light_dir);
		vec3_normalize(light_dir);
		diff_light += (world->lights + i)->intensity * max(0, vec3_dot(light_dir, obj->surf_normal));
		reflect(light_dir, obj->surf_normal, r);
		spec_light += (world->lights + i)->intensity * powf(max(0.0f, dot(r, ray->vec)), obj->mat.n);
	}
	color.bgra[0] = obj->mat.diff_color.bgra[0] * (diff_light * obj->mat.Kd + spec_light * obj->mat.Ks);
	color.bgra[1] = obj->mat.diff_color.bgra[1] * (diff_light * obj->mat.Kd + spec_light * obj->mat.Ks);
	color.bgra[2] = obj->mat.diff_color.bgra[2] * (diff_light * obj->mat.Kd + spec_light * obj->mat.Ks);
	color.bgra[3] = obj->mat.diff_color.bgra[3] * (diff_light * obj->mat.Kd + spec_light * obj->mat.Ks);
	return (color);
}

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
			ray.vec[oy] = (1 - 2 * ((iters[oy] + 0.5) * p->camera.inv_h)) * p->camera.angle;
			ray.vec[ox] = (2 * ((iters[ox] + 0.5) * p->camera.inv_w) - 1) * p->camera.angle * p->camera.ratio;
			normalize(ray.vec);
			color = trace_ray(p, &ray);
			put_pixel(&p->img, iters[ox], iters[oy], color.color);
		}
	}
}
