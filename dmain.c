/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:15:26 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/22 17:51:02 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char *p;

	if (x <= 0 || y <= 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	p = img->data;
	p = (p + img->size_line * y) + ((x * img->bpp) >> 3);
	*(int *)p = color;
}

/*
**vec3 dot product
*/
float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

/*
**norm * norm (magnitude) of vec
*/
float	vec3_norm2(t_vec3 v)
{
	return (vec3_dot(v, v));
}

/*
**substract b vector from a vector store result in dest
*/
void	vec3_sub(t_vec3 a, t_vec3 b, t_vec3 dest)
{
  dest[0] = a[0] - b[0];
  dest[1] = a[1] - b[1];
  dest[2] = a[2] - b[2];
}

enum
{
	ox,oy,oz
};
int		main(int ac, char **av)
{
	t_param p;
	t_obj	sphere;
	t_ray	ray;

	sphere.origin[ox] = 50;
	sphere.origin[oy] = 50;
	sphere.origin[oz] = 0;
	sphere.r = 21;

	ray.point[0] = 0;
	ray.point[1] = 0;
	ray.point[2] = 0;
	ray.vec[0] = 0.0f;
	ray.vec[1] = 0.0f;
	ray.vec[2] = 1.0f;

	//p.mlx_ptr = mlx_init();
	//p.win_ptr = mlx_new_window(p.mlx_ptr, WIDTH, HEIGHT, "<3");
	//p.img.ptr = mlx_new_image(p.mlx_ptr, WIDTH, HEIGHT);
	//p.img.data = mlx_get_data_addr(p.img.ptr, &p.img.bpp, &p.img.size_line, &p.img.endian);

	FILE *f = fopen("test", "w");
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			ray.point[0] = i;
			ray.point[1] = j;
			float a = vec3_norm2(ray.vec);
			t_vec3 dest;
			vec3_sub(ray.point, sphere.origin, dest);
			float b = 2 * vec3_dot(ray.vec, dest);
			float c = vec3_norm2(dest) - sphere.r * sphere.r;
			if (b * b - 4 * a * c >= 1.0f)
			{
				fprintf(f, "  ", i, j);
				//put_pixel(&p.img, i, j, 0x00ff0000);
			}
			else
				fprintf(f, "▌▌");
		}
		fprintf(f, "\n");
	}
	//mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.ptr, 0, 0);
	//mlx_loop(p.mlx_ptr);
	return (0);
}
