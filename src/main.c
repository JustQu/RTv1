/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:24:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/12 17:37:59 by dwalda-r         ###   ########.fr       */
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
	vec3_zero(p->camera.pos);
}

void	rot_obj(t_vec3 c_s, t_vec3 rot_mat)
{
	t_vec3	rot;

	if (rot_mat[oy] != 0)
	{
		rot[ox] = cos(rot_mat[oy]) * c_s[ox] + sin(rot_mat[oy]) * c_s[oz];
		rot[oz] = -sin(rot_mat[oy]) * c_s[ox] + cos(rot_mat[oy]) * c_s[oz];
		c_s[ox] = rot[ox];
		c_s[oz] = rot[oz];
	}
	if (rot_mat[ox] != 0)
	{
		rot[oy] = cos(rot_mat[ox]) * c_s[oy] + sin(rot_mat[ox]) * c_s[oz];
		rot[oz] = -sin(rot_mat[ox]) * c_s[oy] + cos(rot_mat[ox]) * c_s[oz];
		c_s[oy] = rot[oy];
		c_s[oz] = rot[oz];
	}
	if (rot_mat[oz] != 0)
	{
		rot[ox] = cos(rot_mat[oz]) * c_s[ox] - sin(rot_mat[oz]) * c_s[oy];
		rot[oy] = sin(rot_mat[oz]) * c_s[ox] + cos(rot_mat[oz]) * c_s[oy];
		c_s[ox] = rot[ox];
		c_s[oy] = rot[oy];
	}
}

void	rotate_camera(t_param *p)
{
	t_vec3	cam_rot;
	int		i;

	i = -1;
	vec3_copy(p->camera.orientation, cam_rot);
	cam_rot[ox] *= -1;
	cam_rot[oy] *= -1;
	cam_rot[oz] *= -1;
	while (++i < p->world.nobjs)
	{
		rot_obj(p->world.objs[i].camera_space, cam_rot);
		if (p->world.objs[i].type == cone)
			rot_obj(((t_cone *)p->world.objs[i].data)->dir, cam_rot);
		else if (p->world.objs[i].type == plane)
			rot_obj(((t_plane *)p->world.objs[i].data)->nv, cam_rot);
		else if (p->world.objs[i].type == cylinder)
			rot_obj(((t_cylinder *)p->world.objs[i].data)->direction,
			cam_rot);
	}
	i = -1;
	while (++i < p->world.nlights)
	{
		rot_obj(((p->world.lights[i]).camera_space), cam_rot);
	}
}

int		main(int ac, char **arg)
{
	t_param	p;
	int fd;

	fd = open(arg[1], O_RDONLY);
	if (fd < 0)
	{
		printf("%s", "ne otkrivaetsya");
		return (0);
	}
	p.world.nobjs = 0;
	p.world.nlights = 0;
	p.mlx_ptr = mlx_init();
	p.win_ptr = mlx_new_window(p.mlx_ptr, WIDTH, HEIGHT, "<3");
	p.img.ptr = mlx_new_image(p.mlx_ptr, WIDTH, HEIGHT);
	p.img.data = mlx_get_data_addr(p.img.ptr, &p.img.bpp, &p.img.size_line, &p.img.endian);
	read_all(fd, &p);
	world_to_camera(&p);
	rotate_camera(&p);
	//file_save(&p);
	//out_spheres(&p);
	render(&p);
	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.ptr, 0, 0);
	mlx_hook(p.win_ptr, 2, 0, key_press, &p);
	mlx_hook(p.win_ptr, 4, 0, mouse_press, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
