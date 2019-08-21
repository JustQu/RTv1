/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:15:26 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/20 18:56:18 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "math.h"
//# include "mlx.h"
# include "pthread.h"
# include "stdlib.h"
# include "stdio.h"
# include "fcntl.h"
# include "unistd.h"

# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_ZERO 29
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_NINE 25
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MULTI 67
# define KEY_SPACE 49
# define KEY_ENTER 36
# define KEY_ESC 53
# define KEY_TAB 48

# define WIDTH 100
# define HEIGHT 100

typedef struct	s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
}				t_param;

typedef float	t_vec3[3];
typedef float	t_vec4[4];

typedef enum	e_objects
{
	sphere
}				t_obj_type;

typedef struct	s_obj
{
	t_obj_type	type;
	t_vec3		origin;
	float		r;
}				t_obj;

typedef struct	s_ray
{
	t_vec3		point;
	t_vec3		vec;
}				t_ray;

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

#endif