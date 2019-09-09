/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:24:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/09 19:17:44 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** конвеер
** local space->world space->camera space->clip space->window space.
*/

void	get_sphere(t_param *p, t_obj *obj, t_vec3 origin, float radius, int color)
{
	if (obj->data == NULL)
		obj->data = (t_sphere *)malloc(sizeof(t_sphere));
	((t_sphere *)(obj->data))->radius = radius;
	obj->type = sphere;
	vec3_copy(origin, obj->origin);
	obj->material.diffuse_color.color = color;
	obj->t = INFINITY;
}

int		get_objs(t_param *p)
{
	int	i;

	p->world.nobjs = 7;
	p->world.objs = (t_obj *)malloc(p->world.nobjs * sizeof(t_obj));
	i = -1;
	while (++i < p->world.nobjs)
	{
		p->world.objs[i].type = none;
		vec3_zero(p->world.objs[i].origin);
		vec3_broadcast(INFINITY, p->world.objs[i].hit_point);
		vec3_broadcast(INFINITY, p->world.objs[i].surface_normal);
		p->world.objs[i].material.diffuse_color.color = 0;
		p->world.objs[i].material.Kd = 0.8;
		p->world.objs[i].material.Ks = 0.2;
		p->world.objs[i].material.n = 50;
		p->world.objs[i].data = NULL;
		p->world.objs[i].t = INFINITY;
	}

	get_sphere(p, p->world.objs, (t_vec3){0, 0, 6}, 1, 0x00FFFF);

	t_plane pl;
	vec3_copy((t_vec3){0, -1, 0}, pl.nv);
	vec3_normalize(pl.nv);
	vec3_copy((t_vec3){0, -1, 0}, p->world.objs[1].origin);
	p->world.objs[1].data = malloc(sizeof(t_plane));
	p->world.objs[1].type = plane;
	p->world.objs[1].material.diffuse_color.color = 0x7B68EE;
	*(t_plane *)(p->world.objs[1].data) = pl;

	t_cylinder cl;
	vec3_copy((t_vec4){10, 0, 15, 1}, cl.direction);
	vec3_normalize(cl.direction);
	cl.radius = 1;
	vec3_copy((t_vec4){0, 0, 10}, p->world.objs[2].origin);
	p->world.objs[2].data = malloc(sizeof(t_cone));
	p->world.objs[2].type = cylinder;
	p->world.objs[2].material.diffuse_color.color = 0x00BFFF;
	p->world.objs[2].material.Kd = 0.55;
	p->world.objs[2].material.Ks = 0.45;
	p->world.objs[2].material.n = 7;
	*(t_cylinder *)(p->world.objs[2].data) = cl;

	t_cone cn;
	vec3_copy((t_vec3){0,1,0}, cn.dir);
	vec3_normalize(cn.dir);
	cn.angle = 0.5;
	vec3_copy((t_vec3){3, 0 , 5}, p->world.objs[3].origin);
	p->world.objs[3].data = malloc(sizeof(t_cone));
	p->world.objs[3].type = cone;
	p->world.objs[3].material.diffuse_color.color = 0x00ff0000;
	*(t_cone *)p->world.objs[3].data = cn;

	get_sphere(p, p->world.objs + 4, (t_vec3){-5, 3, 10}, 3, 0xF08080);
	get_sphere(p, p->world.objs + 5, (t_vec3){3, 2, 13}, 1, 0xFFDAB9);

	vec3_copy((t_vec3){0, 1, 0}, cl.direction);
	vec3_normalize(cl.direction);
	cl.radius = 0.1;
	vec3_copy((t_vec3){-1, 0, 4}, p->world.objs[6].origin);
	p->world.objs[6].data = malloc(sizeof(t_cone));
	p->world.objs[6].type = cylinder;
	p->world.objs[6].material.diffuse_color.color = 0x0000FF;
	p->world.objs[6].material.Kd = 0.55;
	p->world.objs[6].material.Ks = 0.45;
	p->world.objs[6].material.n = 7;
	*(t_cylinder *)(p->world.objs[6].data) = cl;

	// p->world.objs[1].type = sphere;
	// p->world.objs[1].data = malloc(sizeof(t_sphere));
	// t_sphere *sp1 = p->world.objs[1].data;
	// sp1->origin[0] = 100;
	// sp1->origin[1] = 100;
	// sp1->origin[2] = 10;
	// sp1->radius = 20;

	// p->world.objs[2].type = sphere;
	// p->world.objs[2].data = malloc(sizeof(t_sphere));
	// t_sphere *sp2 = p->world.objs[2].data;
	// sp2->origin[0] = 500;
	// sp2->origin[1] = 900;
	// sp2->origin[2] = 10;
	// sp2->radius = 50;

	// p->world.objs[4].type = cylinder;
	// p->world.objs[4].data = malloc(sizeof(t_cylinder));
	// t_cylinder *cyl1 = p->world.objs[4].data;
	// cyl1->origin[0] = 500;
	// cyl1->origin[1] = 200;
	// cyl1->origin[2] = 10;
	// cyl1->direction[0] = 0;
	// cyl1->direction[1] = -1;
	// cyl1->direction[2] = 0;
	// cyl1->radius = 12;

	p->world.lights = malloc(10 * sizeof(t_light_source));
	p->world.lights[0].origin[0] = 2.0f;
	p->world.lights[0].origin[1] = 0.0f;
	p->world.lights[0].origin[2] = 1.0f;
	p->world.lights[0].intensity = 0.9f;

	p->world.lights[1].origin[0] = -1.0f;
	p->world.lights[1].origin[1] = 0.0f;
	p->world.lights[1].origin[2] = 0.0f;
	p->world.lights[1].intensity = 0.1f;

	p->world.lights[2].origin[0] = 0.0f;
	p->world.lights[2].origin[1] = 5.0f;
	p->world.lights[2].origin[2] = 8.0f;
	p->world.lights[2].intensity = 0.6f;

	p->world.nlights = 2;

	return (0.0);
}

void	move_obj_to_camera(t_obj *obj, t_camera *camera)
{
	vec3_copy(obj->origin, obj->camera_space);
	vec3_sub(obj->camera_space, camera->pos, obj->camera_space);
}

void	world_to_camera(t_param *p)
{
	/*
		camera space: (world space - camera coordiantes) * (camera orientation)^-1
	*/
	for (int i = 0; i < p->world.nobjs; i++)
	{
		vec3_copy((p->world.objs + i)->origin, (p->world.objs + i)->camera_space);
		vec3_sub((p->world.objs + i)->camera_space, p->camera.pos, (p->world.objs + i)->camera_space);
	}
	for (int i = 0; i < p->world.nlights; i++)
	{
		vec3_copy((p->world.lights + i)->origin, (p->world.lights + i)->camera_space);
		vec3_sub((p->world.lights + i)->camera_space, p->camera.pos, (p->world.lights + i)->camera_space);
	}
}

int		main(int ac, char **arg)
{
	t_param	p;

	p.mlx_ptr = mlx_init();
	p.win_ptr = mlx_new_window(p.mlx_ptr, WIDTH, HEIGHT, "<3");
	p.img.ptr = mlx_new_image(p.mlx_ptr, WIDTH, HEIGHT);
	p.img.data = mlx_get_data_addr(p.img.ptr, &p.img.bpp, &p.img.size_line, &p.img.endian);
	int fd;
	fd = open(arg[1], O_RDONLY);
	if (fd < 0)
	{
		printf("%s", "ne otkrivaetsya");
		return (0);
	}
	read_all(fd, &p);
	// get_objs(&p);
	world_to_camera(&p);
	render(&p);

	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.ptr, 0, 0);
	mlx_hook(p.win_ptr, 2, 0, key_press, &p);
	mlx_hook(p.win_ptr, 4, 0, mouse_press, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
