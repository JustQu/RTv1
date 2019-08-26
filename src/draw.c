/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/23 16:30:31 by dmelessa         ###   ########.fr       */
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

void	find_eq(t_param *ptrs, t_vec3 v3, t_vec2 xy)
{
	if (v3[b] * v3[b] - 4 * v3[a] * v3[c] >= 0.0f)
		put_pixel(&ptrs->img, xy[x], xy[y], 0xff);
}

void	draw_sphere(t_obj sp, t_param *ptrs)
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
			vec3_copy((t_vec3){0,0,1}, ray.vec);
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
	draw_sphere(sphere, ptrs);
	mlx_put_image_to_window(ptrs->mlx_ptr, ptrs->win_ptr, ptrs->img.ptr, 0, 0);
}
