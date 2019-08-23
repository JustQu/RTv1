/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/23 18:17:59 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "math.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*p;

	if (x <= 0 || y <= 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	p = img->data;
	p = (p + img->size_line * y) + ((x * img->bpp) >> 3);
	*(int *)p = color;
}

void		create_pic(t_param *p)
{
	int		endian;

	p->img.ptr = mlx_new_image(p->mlx_ptr, WIDTH, HEIGHT);
	p->img.data = mlx_get_data_addr(p->img.ptr, &(p->img.bpp),
	&(p->img.size_line), &endian);
}

void	init_sphere(t_obj *s, t_vec3 pos, float r)
{
	s->type = sphere;
	s->origin[0] = pos[0];
	s->origin[1] = pos[1];
	s->origin[2] = pos[2];
	s->r = r;
}

void	find_eq(t_param *p, t_vec3 v3, t_vec2 xy)
{
	if (v3[b] * v3[b] - 4 * v3[a] * v3[c] >= 0.0f)
		put_pixel(&p->img, xy[x], xy[y], 0xff);
}

void	draw_sphere(t_obj sp, t_param *p)
{
	t_vec2	xy;
	t_ray	ray;

	xy[y] = -1;
	while (++xy[y] < HEIGHT)
	{
		xy[x] = -1;
		while (++xy[x] < WIDTH)
		{
			vec3_copy((t_vec3){xy[x], xy[y], 0}, ray.point);
			vec3_copy((t_vec3){0, 0, 1}, ray.vec);
			vec3_sub(ray.point, sp.origin, ray.point);
			find_eq(p, (t_vec3){(2 * vec3_dot(ray.vec, ray.point)),
			(vec3_norm2(ray.point) - sp.r * sp.r), (vec3_norm2(ray.vec))}, xy);
		}
	}
}

void	calc_all(t_param *p)
{
	t_obj	sphere;
	init_sphere(&sphere, (t_vec3){200, 100, 5}, 15);
	draw_sphere(sphere, p);
}

void	sphere_function(t_param *p, t_obj *obj, t_ray *ray)
{
	t_vec3	tmp;
	float	a;
	float	b;
	float	c;

	vec3_sub(ray->point, obj->origin, tmp);
	a = vec3_norm2(ray->vec);
	b = 2 * vec3_dot(ray->vec, tmp);
	c = vec3_norm2(tmp) - obj->r * obj->r;
	if (b * b - 4 * a * c >= 0.0f)
		put_pixel(&p->img, ray->point[0], ray->point[1], 0xff);
}

/*
** this function calculate all pixels for our scene
*/
void	render(t_param *p)
{
	t_ray	ray;
	int		x;
	int		y;
	int		i;
	t_vec3	tmp;

	//init_sphere(&obj, (t_vec3){333, 333, 5}, 50);
	vec3_copy((t_vec3){0, 0, 1}, ray.vec);
	i = -1;
	while (++ i < p->world.nobjects)
	{
		y = -1;
		while (++y < WIDTH)
		{
			ray.point[1] = y;
			x = -1;
			while (++x < HEIGHT)
			{
				ray.point[0] = x;
				sphere_function(p, p->world.objects + i, &ray);
			}
		}
	}
}