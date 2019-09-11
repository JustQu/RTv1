/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:06:16 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/11 14:18:00 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	all_info(t_param *p)
{
	int i;
	i = -1;
	printf("num = %d\n", p->world.nobjs);
	while (++i < p->world.nobjs)
	{
		if(p->world.objs[i].type == plane)
			out_plane(p->world.objs[i], 1);
		else if(p->world.objs[i].type == cone)
			out_cone(p->world.objs[i], 1);
		else if(p->world.objs[i].type == cylinder)
			out_cylinder(p->world.objs[i], 1);
		else if(p->world.objs[i].type == sphere)
			out_sphere(p->world.objs[i], 1);
		else printf("Unknown object type");
		printf("%s\n", " ");
	}
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_ray	ray;
	t_param	*p;
	t_obj	*obj;

	p = param;
	if (button == 1)
	{
		vec4_copy((t_vec4){1, 1, 1, 1}, ray.vec);
		vec3_zero(ray.point);
		ray.vec[oy] = (1 - 2 * ((y + 0.5) * p->camera.inv_height)) * p->camera.angle;
		ray.vec[ox] = (2 * ((x + 0.5) * p->camera.inv_width) - 1) * p->camera.angle * p->camera.aspectratio;
		normalize(ray.vec);
		p->cntrld_obj = get_first_intesection(p->world.objs, p->world.nobjs, &ray);
	}
	return(0);
}

int			close_w(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int			key_press(int keycode, void *param)
{
	t_param	*p;

	p = param;
	if (keycode == 53)
		exit(0);
	if (keycode == KEY_W && p->cntrld_obj)
		p->cntrld_obj->origin[oz] += 0.5;
	if (keycode == KEY_S && p->cntrld_obj)
		p->cntrld_obj->origin[oz] -= 0.5;
	if (keycode == KEY_A && p->cntrld_obj)
		p->cntrld_obj->origin[ox] -= 0.5;
	if (keycode == KEY_D && p->cntrld_obj)
		p->cntrld_obj->origin[ox] += 0.5;
	if (keycode == KEY_UP && p->cntrld_obj)
		p->cntrld_obj->origin[oy] += 0.5;
	if (keycode == KEY_DOWN && p->cntrld_obj)
		p->cntrld_obj->origin[oy] -= 0.5;
	if (p->cntrld_obj)
		move_obj_to_camera(p->cntrld_obj, &p->camera);
	if (keycode == KEY_ENTER)
		file_save(param);
	if (keycode == KEY_TAB)
		all_info(p);
	if (keycode != KEY_ENTER && keycode != KEY_TAB)
	{
		render(p);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.ptr, 0, 0);
	}
	return (1);
}
