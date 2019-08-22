/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:06:16 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/22 16:07:38 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
