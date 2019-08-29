/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:23:23 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/08/28 19:17:17 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj_type		find_type(char *str)
{
	if (strcmp(str, "plane"))
		return (plane);
	else if (strcmp(str, "sphere"))
		return (sphere);
	else if (strcmp(str, "cylinder"))
		return (cylinder);
	else if (strcmp(str, "cone"))
		return	(cone);
	return (error);
}

void	parse_val(char **str, t_vec3 dst)
{
	int	i;

	i = 0;
	while (str[i] != NULL && i < 3)
	{
		dst[i] = ft_atoi(str[i]);
		i++;
	}
}

void	init_cone(char **str, t_obj *obj)
{

}

void	init_sp(char **str, t_obj *obj)
{
	t_sphere	*sp;
	float		r;
	char		**origin;

	if (str[1] != NULL)
		origin = ft_strsplit(str[1], ',');
	parse_val(origin, sp->origin);
	if (str[2] != NULL)
		r = ft_atoi(str[2]);
	obj->data = sp;
	//освободить память, добавить защиту

}

void	init_plane(char **str, t_obj *obj)
{
	t_plane	*pl;
	char	**origin;
	char	**nv;

	if (str[1] != NULL)
		origin = ft_strsplit(str[1], ',');
	parse_val(origin, pl->origin);
	if (str[2] != NULL)
		nv = ft_strsplit(str[2], ',');
	parse_val(nv, pl->nv);
	obj->data = pl;
	//освободить память, добавить защиту
}

void	init_cyl(char **str, t_obj *obj)
{

}

void	init_er(char **str, t_obj *obj)
{

}

void	choose_func(t_obj *obj)
{
	if (obj->type == plane)
		obj->initf = init_plane;
	else if (obj->type == cone)
		obj->initf = init_cone;
	else if (obj->type == sphere)
		obj->initf = init_sp;
	else if (obj->type == cylinder)
		obj->initf = init_cyl;
	else if (obj->type == error)
		obj->initf = init_er;
}

t_obj	parse(char *str)
{
	char	**c;
	t_obj	obj;

	c = ft_strsplit(str, ';');
	if ((obj.type = find_type(c[0])) == error)
		return (obj);
	choose_func(&obj);

	return (obj);
}

void	read_all(int fd, t_param *p)
{
	char	*str;
	int		i;

	i = 0;
	if (get_next_line(fd, &str) > 0)
		p->world.nobjects = ft_atoi(str);
	p->world.objects = (t_obj *)malloc(sizeof(t_obj) * p->world.nobjects);
	while (get_next_line(fd, &str))
	{

	}
}
