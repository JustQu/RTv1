/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:26:15 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/26 14:51:48 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "math.h"
# include "mlx.h"
# include "pthread.h"
# include "stdlib.h"
# include "stdio.h"
# include "fcntl.h"
# include "unistd.h"

# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_ZERO 29
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_NINE 25
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MULTI 67
# define KEY_SPACE 49
# define KEY_ENTER 36
# define KEY_ESC 53
# define KEY_TAB 48

# define WIDTH 1000
# define HEIGHT 1000

typedef struct	s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef float	t_vec2[2];
typedef float	t_vec3[3];
typedef float	t_vec4[4];

typedef enum	e_objects
{
	sphere,
	plane,
	cube,
}				t_obj_type;

/*
** don't use just 'x' and 'y'
** if u do so then you can't use them as parameters in fucntion
*/

typedef enum	e_bca
{
	b,
	c,
	a
}				t_bca;

/*
** actully it is sphere right now
** need to make it more common
*/
typedef struct	s_obj
{
	t_obj_type	type;
	t_vec3		origin;
	float		r;
}				t_obj;

typedef struct	s_ray
{
	t_vec3		point;
	t_vec3		vec;
}				t_ray;

/*
** we store here all our objects
*/
typedef	struct	s_world
{
	t_obj		*objects;
}				t_world;

typedef struct	s_camera
{
	t_vec4		pos;
	t_vec4		orientation;
}				t_camera;

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
	t_world		world;
	t_camera	camera;
}				t_param;

int				close_w(void *param);
int				key_press(int keycode, void *param);
void			calc_all(t_param *ptr);

#endif
