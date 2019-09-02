/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:24:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/02 21:46:54 by dmelessa         ###   ########.fr       */
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

void	get_object_data(t_obj *obj, t_obj_type type)
{

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

void	get_sphere(t_param *p, t_obj *obj, t_vec3 origin, float radius, int color, int albedo)
{
	if (obj->data == NULL)
		obj->data = (t_sphere *)malloc(sizeof(t_sphere));
	((t_sphere *)(obj->data))->radius = radius;
	obj->type = sphere;
	vec3_copy(origin, obj->origin);
	obj->material.diffuse_color.color = color;
	obj->t = INFINITY;
}

int		get_objects(t_param *p)
{
	int	i;

	p->world.nobjects = 2;
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

	get_sphere(p, p->world.objects, (t_vec3){300, 800, 3}, 150, 0x222b57,0);

	t_cylinder cl;
	vec3_copy((t_vec4){1, 1, 0, 1}, cl.direction);
	vec3_normalize(cl.direction);
	cl.radius = 70;
	vec3_copy((t_vec4){500, 1000, 4}, p->world.objects[1].origin);
	p->world.objects[1].data = malloc(sizeof(t_cone));
	p->world.objects[1].type = cylinder;
	p->world.objects[1].material.diffuse_color.color = 0x002b00;
	*(t_cylinder *)(p->world.objects[1].data) = cl;

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

	// p->world.objects[3].type = cone;
	// p->world.objects[3].data = malloc(sizeof(t_cone));
	// t_cone *con1 = p->world.objects[3].data;
	// con1->origin[0] = 500;
	// con1->origin[1] = 500;
	// con1->origin[2] = 10;
	// con1->dir[0] = 0;
	// con1->dir[1] = -1;
	// con1->dir[2] = 0;
	// con1->angle = 0.5;

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
	p->world.lights[0].origin[0] = 500;
	p->world.lights[0].origin[1] = 500;
	p->world.lights[0].origin[2] = 100;
	p->world.lights[0].intensity = 1;

	p->world.nlights = 1;

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
