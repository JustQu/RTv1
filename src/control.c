/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:06:16 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/14 15:13:23 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			mouse_press(int button, int x, int y, void *param)
{
	t_ray	ray;
	t_param	*p;

	p = param;
	if (button == 1)
	{
		vec4_copy((t_vec4){1, 1, 1, 1}, ray.vec);
		vec3_zero(ray.point);
		ray.vec[oy] = (1 - 2 * ((y + 0.5) * p->camera.inv_h)) *
		p->camera.angle;
		ray.vec[ox] = (2 * ((x + 0.5) * p->camera.inv_w) - 1) *
		p->camera.angle * p->camera.ratio;
		normalize(ray.vec);
		p->cntrld_obj = get_first_intesection(p->world.objs,
		p->world.nobjs, &ray);
	}
	return (0);
}

int			close_w(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void		move_obj_key_press(int keycode, t_param *p)
{
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
}

int			key_press(int keycode, void *param)
{
	t_param	*p;

	p = param;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_ENTER)
	{
		file_save(p);
		return (1);
	}
	move_obj_key_press(keycode, p);
	render(p);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.ptr, 0, 0);
	return (1);
}
