/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:24:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/23 14:35:22 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(int ac, char **arg)
{
	t_param	ptrs;
	(void)ac;
	(void)arg;
	ptrs.mlx_ptr = mlx_init();
	ptrs.win_ptr = mlx_new_window(ptrs.mlx_ptr, WIDTH, HEIGHT, "<3");
	ptrs.img.ptr = NULL;
	calc_all(&ptrs);
	mlx_hook(ptrs.win_ptr, 2, 0, key_press, &ptrs);
	mlx_hook(ptrs.win_ptr, 17, 0, close_w, &ptrs);
	mlx_loop(ptrs.mlx_ptr);
	return (0);
}

