/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/26 21:06:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "rtmath.h"
#include "nmmintrin.h"
#include "immintrin.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*p;

	if (x <= 0 || y <= 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	p = img->data;
	p = (p + img->size_line * y) + ((x * img->bpp) >> 3);
	*(int *)p = color;
}

void	sphere_function(t_param *p, t_obj *obj, t_ray *ray)
{
	t_vec4		tmp;
	t_vec4		coefs;
	t_sphere	sphere;

	sphere = *(t_sphere *)(obj->data);
	vec3_sub(ray->point, sphere.origin, tmp);
	coefs[a] = vec3_norm2(ray->vec);
	coefs[b] = 2 * vec3_dot(ray->vec, tmp);
	coefs[c] = vec3_norm2(tmp) - sphere.radius * sphere.radius;
	coefs[d] = coefs[b] * coefs[b] - 4 * coefs[a] * coefs[c];
	if (coefs[d] >= 0.0f)
	{
		t_vec3 tmp2;
		float t = (-coefs[b] - sqrtf(coefs[d])) * 0.5 / coefs[a];
		vec3_scale(ray->vec, t, tmp2);
		vec3_sum(ray->point, tmp2, tmp2);
		printf("a: %f b:%f c:%f d:%f t:%f p:%f %f %f\n", coefs[a], coefs[b], coefs[c], coefs[d], t, tmp2[0], tmp2[1], tmp2[2]);
		//put_pixel(&p->img, ray->point[ox], ray->point[oy], 0xf0);
	}
}


/*
** cone c and ray ray intersection
*/
void	conef(t_param *p, t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec4	coef;
	t_vec4	norm_vec;
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
		put_pixel(&p->img, ray->point[ox], ray->point[1], 0xf000);
	obj->hit_point = (-coef[b] + sqrtf(coef[d])) * 0.5 / coef[a];//wrong
	//N = nrm( P-C - (1+k*k)*V*m )
}

int			intersection(t_param *p, t_obj *obj, t_ray ray)
{
	if (obj->type == sphere)
		sphere_function(p, obj, &ray);
	else if (obj->type == cone)
		conef(p, obj, &ray);
}

t_obj		get_first_intesection(t_param *p, t_ray ray)
{
	int		i;

	i = -1;
	while (++i < p->world.nobjects)
	{
		if (intersection(p, p->world.objects + i, ray))
			return (p->world.objects[i]);
	}
}

t_color		trace_ray(t_param *p, t_ray ray)
{
	t_obj	obj;
	t_color	color;

	obj = get_first_intesection(p, ray);
	//color = get_point_color(obj);
}

/*
** this function calculate all pixels for our scene
*/
void	render(t_param *p)
{
	t_ray	ray;
	t_vec2	iters;

	vec4_copy((t_vec4){0, 0, 1, 1}, ray.vec);
	iters[oy] = -1;
	while (++iters[oy] < WIDTH)
	{
		ray.point[1] = iters[oy];
		iters[ox] = -1;
		while (++iters[ox] < HEIGHT)
		{
			ray.point[0] = iters[ox];
			trace_ray(p, ray);
		}
	}
}
