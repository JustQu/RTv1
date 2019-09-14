/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_initiation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:35:10 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/14 15:16:10 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_sphere(t_list *t, t_obj *p)
{
	t_color		dcolor;

	dcolor.color = 0x96d38c;
	p->type = sphere;
	p->data = (t_sphere *)malloc(sizeof(t_sphere));
	((t_sphere *)(p->data))->radius = read_fparam(t->content, "radius", 0.2);
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0, 0, 3});
	((t_sphere *)(p->data))->radius2 = ((t_sphere *)(p->data))->radius
	* ((t_sphere *)(p->data))->radius;
	p->mat = read_material(dcolor);
}

void		init_plane(t_list *t, t_obj *p)
{
	t_color		dcolor;

	dcolor.color = 0xc4def6;
	p->type = plane;
	p->data = (t_plane *)malloc(sizeof(t_plane));
	read_vec3_param(t->content, ((t_plane *)p->data)->nv,
	"nv", (t_vec3){0, -1, 0});
	vec3_normalize(((t_plane *)p->data)->nv);
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0, -1, 0});
	p->mat = read_material(dcolor);
}

void		init_cone(t_list *t, t_obj *p)
{
	t_color		dcolor;

	dcolor.color = 0x213458;
	p->type = cone;
	p->data = (t_cone *)malloc(sizeof(t_cone));
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0, 0, 4});
	read_vec3_param(t->content, ((t_cone *)p->data)->dir,
	"direction", (t_vec3){0, 1, 0});
	vec3_normalize(((t_cone *)p->data)->dir);
	((t_cone *)p->data)->angle = read_fparam(t->content, "angle", 0.5);
	((t_cone *)p->data)->k = tan(((t_cone *)p->data)->angle);
	((t_cone *)p->data)->k2 = 1 + ((t_cone *)p->data)->k *
	((t_cone *)p->data)->k;
	p->mat = read_material(dcolor);
}

void		init_cylinder(t_list *t, t_obj *p)
{
	t_color		dcolor;

	dcolor.color = 0xffd464;
	p->type = cylinder;
	p->data = (t_cylinder *)malloc(sizeof(t_cylinder));
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0, 0, 4});
	read_vec3_param(t->content, ((t_cylinder *)p->data)->dir,
	"direction", (t_vec3){0, 1, 0});
	vec3_normalize(((t_cylinder *)p->data)->dir);
	((t_cylinder *)p->data)->radius = read_fparam(t->content, "radius", 0.3);
	p->mat = read_material(dcolor);
}
