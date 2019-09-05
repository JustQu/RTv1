/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:24:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/05 19:55:15 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** конвеер
** local space->world space->camera space->clip space->window space.
*/

#define BACKGROUND 0x1a334d

//read specific information for object type from str
void	read_type_data(void *data, t_obj_type type, char *str)
{
	if (type == sphere)
	{
		if (data == NULL)
			data = malloc (sizeof(t_sphere));
	}
}

void	func(t_param *p)
{
	p->world.nobjects = 1;
	p->world.objects = malloc(p->world.nobjects * sizeof(t_obj));
	p->world.objects[0].type = none;
	vec3_broadcast(INFINITY, p->world.objects[0].hit_point);
	vec3_broadcast(INFINITY, p->world.objects[0].surface_normal);
	p->world.objects[0].material.diffuse_color.color = 0;
	p->world.objects[0].data = NULL;
}

void	get_sphere(t_param *p, t_obj *obj, t_vec3 origin, float radius, int color, t_vec2 albedo)
{
	if (obj->data == NULL)
		obj->data = (t_sphere *)malloc(sizeof(t_sphere));
	((t_sphere *)(obj->data))->radius = radius;
	obj->type = sphere;
	vec3_copy(origin, obj->origin);
	obj->material.diffuse_color.color = color;
	obj->material.albedo[0] = albedo[0];
	obj->material.albedo[1] = albedo[1];
	obj->t = INFINITY;
}

int		get_objects(t_param *p)
{
	int	i;

	p->world.nobjects = 6;
	p->world.objects = (t_obj *)malloc(p->world.nobjects * sizeof(t_obj));
	i = -1;
	while (++i < p->world.nobjects)
	{
		p->world.objects[i].type = none;
		vec3_zero(p->world.objects[i].origin);
		vec3_broadcast(INFINITY, p->world.objects[i].hit_point);
		vec3_broadcast(INFINITY, p->world.objects[i].surface_normal);
		p->world.objects[i].material.diffuse_color.color = 0;
		p->world.objects[i].data = NULL;
		p->world.objects[i].t = INFINITY;
	}
	
	t_vec2 t;
	t[0] = 0.3f;
	t[1] = 0.6f;
	get_sphere(p, p->world.objects, (t_vec3){0, 0, 6}, 1, 0x00FFFF, t);

	t_plane pl;
	vec3_copy((t_vec3){0, -1, 0}, pl.nv);
	vec3_normalize(pl.nv);
	vec3_copy((t_vec3){0, -1, 0}, p->world.objects[1].origin);
	p->world.objects[1].data = malloc(sizeof(t_plane));
	p->world.objects[1].type = plane;
	p->world.objects[1].material.diffuse_color.color = 0x7B68EE;
	*(t_plane *)(p->world.objects[1].data) = pl;

	t_cylinder cl;
	vec3_copy((t_vec4){10, 1, 15, 1}, cl.direction);
	vec3_normalize(cl.direction);
	cl.radius = 1;
	vec3_copy((t_vec4){0, 0, 10}, p->world.objects[2].origin);
	p->world.objects[2].data = malloc(sizeof(t_cone));
	p->world.objects[2].type = cylinder;
	p->world.objects[2].material.diffuse_color.color = 0x00BFFF;
	*(t_cylinder *)(p->world.objects[2].data) = cl;

	
	t_cone cn;
	vec3_copy((t_vec3){0,1,0}, cn.dir);
	vec3_normalize(cn.dir);
	cn.angle = 0.5;
	vec3_copy((t_vec3){3, 0 , 5}, p->world.objects[3].origin);
	p->world.objects[3].data = malloc(sizeof(t_cone));
	p->world.objects[3].type = cone;
	p->world.objects[3].material.diffuse_color.color = 0x00ff0000;
	*(t_cone *)p->world.objects[3].data = cn;

	get_sphere(p, p->world.objects + 4, (t_vec3){-5, 3, 10}, 3, 0xF08080, t);

	get_sphere(p, p->world.objects + 5, (t_vec3){3, 2, 13}, 1, 0xFFDAB9,t);

	// p->world.objects[1].type = sphere;
	// p->world.objects[1].data = malloc(sizeof(t_sphere));
	// t_sphere *sp1 = p->world.objects[1].data;
	// sp1->origin[0] = 100;
	// sp1->origin[1] = 100;
	// sp1->origin[2] = 10;
	// sp1->radius = 20;

	// p->world.objects[2].type = sphere;
	// p->world.objects[2].data = malloc(sizeof(t_sphere));
	// t_sphere *sp2 = p->world.objects[2].data;
	// sp2->origin[0] = 500;
	// sp2->origin[1] = 900;
	// sp2->origin[2] = 10;
	// sp2->radius = 50;

	// p->world.objects[4].type = cylinder;
	// p->world.objects[4].data = malloc(sizeof(t_cylinder));
	// t_cylinder *cyl1 = p->world.objects[4].data;
	// cyl1->origin[0] = 500;
	// cyl1->origin[1] = 200;
	// cyl1->origin[2] = 10;
	// cyl1->direction[0] = 0;
	// cyl1->direction[1] = -1;
	// cyl1->direction[2] = 0;
	// cyl1->radius = 12;

	p->world.lights = malloc(10 * sizeof(t_light_source));
	p->world.lights[0].origin[0] = -3.0f;
	p->world.lights[0].origin[1] = 5.0f;
	p->world.lights[0].origin[2] = 0.0f;
	p->world.lights[0].intensity = 0.9f;

	p->world.nlights = 1;

	return (0.0);
}

void	world_to_camera(t_param *p)
{
	/*
		camera space: (world space - camera coordiantes) * (camera orientation)^-1
	*/
	for (int i = 0; i < p->world.nobjects; i++)
	{
		vec3_copy((p->world.objects + i)->origin, (p->world.objects + i)->camera_space);
		vec3_sub((p->world.objects + i)->camera_space, p->camera.pos, (p->world.objects + i)->camera_space);
	}
}

void	set_default_camera(t_camera *camera)
{
	camera->pos[ox] = 0.0f;
	camera->pos[oy] = 0.0f;
	camera->pos[oz] = 0.0f;
	camera->near_z = 1;

	/*
		without rotation for now
	*/
	camera->orientation[ox] = 0.0f;
	camera->orientation[oy] = 0.0f;
	camera->orientation[oz] = 0.0f;
	camera->fov = 45;
	camera->inv_width = 1.0f / WIDTH;
	camera->inv_height = 1.0f / HEIGHT;
	camera->aspectratio = WIDTH / (float)HEIGHT;
	camera->angle = tanf(RTM_PI * 0.5f * camera->fov / 180.0f);
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


	set_default_camera(&p.camera);
	get_objects(&p);
	render(&p);

	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.ptr, 0, 0);
	mlx_hook(p.win_ptr, 2, 0, key_press, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
