/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:06:16 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/05 19:03:08 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			mouse_press(int button, int x, int y, void *param)
{
	int	i;
	int	r;
	int	g;
	int b;
	if (button == 1)
	{
		printf("%d, %d\n", x, y);
		i = (x * ((t_param *)param)->img.bpp / 8 + y * ((t_param *)param)->img.size_line);
		b = (((t_param *)param)->img.data[i]) & 0xff;
		g = (((t_param *)param)->img.data[++i]) & 0xff;
		r = (((t_param *)param)->img.data[++i]) & 0xff;
		printf("%d, %d, %d\n", r, g, b);


		(void)param;

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
	(void)param;
	if (keycode == 53)
		exit(0);
	return (1);
}
