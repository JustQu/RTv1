/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_initiation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:48:35 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/13 16:46:51 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_light(t_list *t, t_light_source *light)
{
	read_vec3_param(t->content, light->origin, "origin", (t_vec3){0, 1, 0});
	light->intensity = read_fparam(t->content, "intensity", 0.8);
}

void		set_default_camera(t_camera *camera)
{
	camera->origin[ox] = 0.0f;
	camera->origin[oy] = 0.0f;
	camera->origin[oz] = 0.0f;
	camera->near_z = 1;
	camera->orient[ox] = 0.0f;
	camera->orient[oy] = 0.0f;
	camera->orient[oz] = 0.0f;
	camera->fov = 45;
	camera->inv_w = 1.0f / WIDTH;
	camera->inv_h = 1.0f / HEIGHT;
	camera->ratio = (float)WIDTH / (float)HEIGHT;
	camera->angle = tanf(M_PI * 0.5f * camera->fov / 180.0f);
}

void		init_camera(t_list *t, t_camera *camera)
{
	read_vec3_param(t->content, camera->origin, "origin",
	(t_vec3){0, 0, 1});
	camera->near_z = read_fparam(t->content, "near_z", 1);
	read_vec3_param(t->content, camera->orient,
	"orientation", (t_vec3){0, 0, 0});
	camera->fov = read_fparam(t->content, "fov", 45);
	camera->inv_w = 1.0f / WIDTH;
	camera->inv_h = 1.0f / HEIGHT;
	camera->ratio = (float)WIDTH / (float)HEIGHT;
	camera->angle = tanf(M_PI * 0.5f * camera->fov / 180.0f);
}

void		parse_obj(t_list *l, t_param *p, t_obj_type t)
{
	static int		i;
	static int		j;

	if (!l)
		return ;
	if (t == sphere)
		init_sphere(l, p->world.objs + i++);
	else if (t == light)
		init_light(l, p->world.lights + j++);
	else if (t == plane)
		init_plane(l, p->world.objs + i++);
	else if (t == cone)
		init_cone(l, p->world.objs + i++);
	else if (t == cylinder)
		init_cylinder(l, p->world.objs + i++);
}
