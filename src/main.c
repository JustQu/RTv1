/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:24:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/28 19:03:46 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** конвеер
** local space->world space->camera space->clip space->window space.
*/

/*
** get all our objects in this function
*/

#define BACKGROUND 0x1a334d

int		get_objects(t_param *p)
{
	p->world.objects = malloc(10 * sizeof(t_obj));

	p->world.objects[0].type = sphere;
	p->world.objects[0].data = malloc(sizeof(t_sphere));
	t_sphere *sp = p->world.objects[0].data;
	sp->origin[0] = 10;
	sp->origin[1] = 10;
	sp->origin[2] = 10;
	sp->radius = 15;

	p->world.objects[1].type = sphere;
	p->world.objects[1].data = malloc(sizeof(t_sphere));
	t_sphere *sp1 = p->world.objects[1].data;
	sp1->origin[0] = 100;
	sp1->origin[1] = 100;
	sp1->origin[2] = 10;
	sp1->radius = 20;

	p->world.objects[2].type = plane;
	p->world.objects[2].data = malloc(sizeof(t_plane));
	t_plane *pl1 = p->world.objects[2].data;
	pl1->origin[0] = 500;
	pl1->origin[1] = 500;
	pl1->origin[2] = 10;
	pl1->nv[0] = 0;
	pl1->nv[1] = 1;
	pl1->nv[2] = -1;

	p->world.objects[3].type = cone;
	p->world.objects[3].data = malloc(sizeof(t_cone));
	t_cone *con1 = p->world.objects[3].data;
	con1->origin[0] = 500;
	con1->origin[1] = 500;
	con1->origin[2] = 10;
	con1->dir[0] = 0;
	con1->dir[1] = -1;
	con1->dir[2] = 0;
	con1->angle = 0.5;


	p->world.nobjects = 4;

	return (0.0);
}

int		main(int ac, char **arg)
{
	t_param	p;

	p.mlx_ptr = mlx_init();
	p.win_ptr = mlx_new_window(p.mlx_ptr, WIDTH, HEIGHT, "<3");
	p.img.ptr = mlx_new_image(p.mlx_ptr, WIDTH, HEIGHT);
	p.img.data = mlx_get_data_addr(p.img.ptr, &p.img.bpp, &p.img.size_line, &p.img.endian);
	for(int i = 0; i < WIDTH * HEIGHT; i++)
		((int *)p.img.data)[i] = BACKGROUND;

	get_objects(&p);
	render(&p);

	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.ptr, 0, 0);
	mlx_hook(p.win_ptr, 2, 0, key_press, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
