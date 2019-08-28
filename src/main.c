/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:24:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/26 15:26:46 by dwalda-r         ###   ########.fr       */
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
	p->world.objects[0].data = malloc(sizeof(sphere));
	t_sphere *sphere = p->world.objects[0].data;
	sphere->origin[0] = 10;
	sphere->origin[1] = 10;
	sphere->origin[2] = 10;
	sphere->radius = 2;

	/*p->world.objects[1].type = sphere;
	p->world.objects[1].origin[0] = 600;
	p->world.objects[1].origin[1] = 600;
	p->world.objects[1].origin[2] = 0;
	p->world.objects[1].r = 60;*/
	p->world.nobjects = 1;

	return (0.0);
}

int		main(int ac, char **arg)
{
	t_param	p;

	//p.mlx_ptr = mlx_init();
	//p.win_ptr = mlx_new_window(p.mlx_ptr, WIDTH, HEIGHT, "<3");
	//p.img.ptr = mlx_new_image(p.mlx_ptr, WIDTH, HEIGHT);
	//p.img.data = mlx_get_data_addr(p.img.ptr, &p.img.bpp, &p.img.size_line, &p.img.endian);
	//for(int i = 0; i < WIDTH * HEIGHT; i++)
		//((int *)p.img.data)[i] = BACKGROUND;

	get_objects(&p);
	render(&p);

	//mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.ptr, 0, 0);
	//mlx_hook(p.win_ptr, 2, 0, key_press, &p);
	//mlx_loop(p.mlx_ptr);
	return (0);
}
