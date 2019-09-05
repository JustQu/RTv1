/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:23:23 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/04 19:34:41 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

size_t		list_len(t_list *l, t_param *p)
{
	size_t	len;
	size_t	lnum;

	lnum = 0;
	len = 0;
	while (l)
	{
		if (ft_strstr(l->content, "lightsource"))
			lnum++;
		len++;
		l = l->next;
	}
	p->world.nlights = lnum;
	p->world.nobjects = len - lnum;
	p->world.lights = (t_light_source *)malloc(sizeof(t_light_source) * lnum);
	p->world.objects = (t_obj *)malloc(sizeof(t_obj) * (len - lnum));
	return (len);
}

t_obj_type	find_type(t_list *l)
{
	if (ft_strnstr(l->content, "lightsource", ft_strlen("lightsource")))
		return (light);
	else if (ft_strnstr(l->content, "sphere", ft_strlen("sphere")))
		return (sphere);
	else if (ft_strnstr(l->content, "cone", ft_strlen("cone")))
		return (cone);
	else if (ft_strnstr(l->content, "plane", ft_strlen("plane")))
		return (plane);
	else if (ft_strnstr(l->content, "cylinder", ft_strlen("cylinder")))
		return (cylinder);
	else
		return (none);
}

float			ft_getfnumber(char *str)
{
	float	num;
	int		sign;

	num = 0;
	while (ft_isspace(*str))
		str++;
	sign = *str == '-' ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0' && (ft_isdigit(*str) || *str == '.'))
	{

	}
}

void			find_origin(char *str, t_vec3 origin)
{
	char	*c;
	int		i;

	i = 0;
	vec3_copy((t_vec3){500, 200, 3}, origin);
	c = ft_strstr(str, "origin");
	while (*c != '\0' && *c != '(')
		c++;
	if (*c != '\0')
		c++;
	while (*c != '\0' && *c != ')')
	{

	}
}

int			init_sphere(t_list *t, t_param *p, t_vec3 ij)
{
	t_sphere	*sp;
	float		r;
	t_vec3		origin;

	p->world.objects[(int)ij[ox]].data = (t_sphere *)malloc(sizeof(t_sphere));
	sp = p->world.objects[(int)ij[ox]].data;

}

int			parse_obj(t_list *l, t_param *p, t_vec3 ij, t_obj_type t)
{
	if (t == sphere)
		init_sphere(l, p, ij);
}

int		parse_list(t_param *p, t_list *l)
{

	t_vec3		ij;
	t_obj_type	t;

	vec3_zero(ij);
	while (l)
	{
		if ((t = find_type(l)) == none)
			return (0);
		parse_obj(l, p, ij, t);
	}
}

int		read_all(int fd, t_param *p)
{
	char	*str;
	t_list	*list;

	list = ft_lstnew(NULL, 0);
	while (get_next_line(fd, &str))
	{
		ft_lstadd(&list, ft_lstnew(str, ft_strlen(str)));
		ft_strdel(&str);
	}
	if (fd < 0 || !list_len(list, p))
		return (0);

	return (1);
}
