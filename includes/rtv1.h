/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:26:15 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/29 17:54:36 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "get_next_line.h"
# include <math.h>

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

typedef float	t_vec2[2];
typedef float	t_vec3[3];
typedef float	t_vec4[4];
typedef float	t_mat3[3][3];
typedef float	t_mat4[4][4];
typedef struct	s_obj	t_obj;
typedef void	(*t_initf)(char **str, t_obj *obj);
void			vec3_broadcast(float val, t_vec3 d);

typedef union	u_color
{
	char		a;
	char		r;
	char		g;
	char		b;
	int			color;
}				t_color;

typedef struct	s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef enum	e_objects
{
	sphere,
	plane,
	cone,
	cylinder,
	error
}				t_obj_type;

enum
{
	a, b, c, d
};

typedef struct	s_material
{
	t_color		diffuse_color;
	float		reflect_coef;
	float		refract_coef;
	float		mate;
}				t_material;

typedef struct	s_light_source
{
	t_vec4		origin;
	float		intensity;
}				t_light_source;

/*
**
*/


typedef struct	s_obj
{
	t_obj_type	type;
	t_vec4		surface_normal;
	t_initf		initf;
	t_vec4		hit_point;
	t_color		color;
	t_material	material;
	void		*data;
	t_material	material;
}				t_obj;


/*
** s_ray store information about rays
** point - coordinate of plane view where ray starts
** vec - direction of ray at point position
*/

typedef struct	s_ray
{
	t_vec4		point;
	t_vec4		vec;
}				t_ray;

typedef struct	s_sphere
{
	t_vec4		origin;
	float		radius;
}				t_sphere;

typedef struct	s_plane
{
	t_vec4		origin;
	t_vec4		nv;
}				t_plane;

typedef struct	s_cone
{
	t_vec3		origin;
	t_vec3		dir;
	float		angle;
	float		k;
	float		k2;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec4		origin;
	t_vec4		direction;
	float		radius;
}				t_cylinder;

/*
** we store here all our objects
** objects - all object in world
** nobjects - total number of objects
** lights - all light sources in world
** nlights - total number if light sources
*/

typedef	struct	s_world
{
	t_obj		*objects;
	int			nobjects;
	t_light_source		*lights;
	int			nlights;
}				t_world;

/*
** s_camera store information about camera that we control
** pos - current postion of camera
** orientation - direction of camera
*/

typedef struct	s_camera
{
	t_vec4		pos;
	t_vec4		orientation;
}				t_camera;

/*
** s_param store all information that we need in our program
** mlx_ptr - the connection identifier
** win_ptr - window identifier
** img - store information about displaying image
** world - store information about all objects and light sources
** camera - store information about controlled camera
*/

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
	t_world		world;
	t_camera	camera;
}				t_param;

int		key_press(int keycode, void *param);
void	render(t_param *p);

#endif
