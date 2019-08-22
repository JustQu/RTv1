/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/22 17:55:57 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_color(t_image *img, int color, int x, int y)
{
	int	o;

	o = (x * img->bpp / 8 + y * img->size_line);
	img->data[o] = color & 0xff;
	img->data[++o] = color >> 8 & 0xff;
	img->data[++o] = color >> 16 & 0xff;
	img->data[++o] = 0;
}

void		create_pic(t_param *ptrs)
{
	int		endian;

	ptrs->img.ptr = mlx_new_image(ptrs->mlx_ptr, WIDTH, HEIGHT);
	ptrs->img.data = mlx_get_data_addr(ptrs->img.ptr, &(ptrs->img.bpp),
	&(ptrs->img.size_line), &endian);
}

void	init_sphere(t_obj *s, t_vec3 pos, float r)
{
	s->origin[0] = pos[0];
	s->origin[1] = pos[1];
	s->origin[2] = pos[2];
	s->r = r;
}

void	vec3_init(t_vec3 v3, float x, float y, float z)
{
	v3[0] = x;
	v3[1] = y;
	v3[2] = z;
}

void	vec3_sub(t_vec3 a, t_vec3 b, t_vec3 dest)
{
  dest[0] = a[0] - b[0];
  dest[1] = a[1] - b[1];
  dest[2] = a[2] - b[2];
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

float	vec3_norm2(t_vec3 v)
{
	return (vec3_dot(v, v));
}

void	find_eq(t_param *ptrs, t_vec3 v3, t_vec2 xy)
{
	if (v3[b] * v3[b] - 4 * v3[a] * v3[c] >= 0.0f)
		set_color(&ptrs->img, 0xff, xy[x], xy[y]);
}

void	draw(t_obj sp, t_param *ptrs)
{
	t_vec2	xy;
	t_ray	ray;

	xy[y] = -1;
	while (++xy[y] < HEIGHT)
	{
		xy[x] = -1;
		while (++xy[x] < WIDTH)
		{
			vec3_init(ray.point, xy[x], xy[y], 0);
			vec3_init(ray.vec, 0, 0, 1);
			vec3_sub(ray.point, sp.origin, ray.point);
			find_eq(ptrs, (t_vec3){(2 * vec3_dot(ray.vec, ray.point)),
			(vec3_norm2(ray.point) - sp.r * sp.r), (vec3_norm2(ray.vec))}, xy);
		}
	}
}

void	calc_all(t_param *ptrs)
{
	t_obj	sphere;
	if (!ptrs->img.ptr)
		create_pic(ptrs);
	init_sphere(&sphere, (t_vec3){200, 100, 5}, 15);
	draw(sphere, ptrs);
	mlx_put_image_to_window(ptrs->mlx_ptr, ptrs->win_ptr, ptrs->img.ptr, 0, 0);
}
