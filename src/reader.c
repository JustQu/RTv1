/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:23:23 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/06 19:27:27 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

size_t		list_len(t_list *l, t_param *p)
{
	size_t	len;
	size_t	lnum;

	lnum = 0;
	len = 0;
	if (!l)
		return (0);
	while (l)
	{
		if (ft_strstr(l->content, "lightsource"))
			lnum++;
		len++;
		l = l->next;
	}
	p->world.nlights = lnum;
	p->world.nobjects = len - lnum;
	// p->world.lights = (t_light_source *)malloc(sizeof(t_light_source) * lnum);
	p->world.objects = (t_obj *)malloc(sizeof(t_obj) * p->world.nobjects);
	return (len);
}

t_obj_type	find_type(t_list *l)
{
	if (!ft_strncmp("lightsource", l->content, ft_strlen("lightsource")))
		return (light);
	else if (!ft_strncmp("sphere", l->content, ft_strlen("sphere")))
		return (sphere);
	else if (!ft_strncmp("cone", l->content, ft_strlen("cone")))
		return (cone);
	else if (!ft_strncmp("plane", l->content, ft_strlen("plane")))
		return (plane);
	else if (!ft_strncmp("cylinder", l->content, ft_strlen("cylinder")))
		return (cylinder);
	else
		return (none);
}

float			ft_getfnumber(char *str)
{
	float	num;
	int		sign;
	int		del;

	del = 10;
	num = 0;
	while (*str && ft_isspace(*str))
		str++;
	sign = *str == '-' ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0' && ft_isdigit(*str))
	{
		num = num * del + *str - '0';
		str++;
	}
	str = *str == '.' ? str + 1 : str;
		while (*str != '\0' && ft_isdigit(*str))
		{
			num = num + ((float)(*str - '0')) / (float)del;
			del *= 10;
			str++;
		}
	return (num * sign);
}

void			read_vec3_param(char *str, t_vec3 v3param, char *param, t_vec3 v3def)
{
	char	*c;
	int		i;

	i = 0;
	vec3_copy(v3def, v3param);
	c = ft_strstr(str, param);
	if (c == NULL)
		return ;
	while (*c != '\0' && *c != '(')
		c++;
	if (*c != '\0')
		c++;
	while (*c != '\0' && *c != ')')
	{
		v3param[i++] = ft_getfnumber(c);
		while (*c != '\0' && *c != ',' && *c != ')')
			c++;
		if (*c != '\0')
			c++;
	}
}

float			read_fparam(char *str, char *param, float dfval)
{
	float	num;
	char	*c;

	c = (ft_strstr(str, param));
	if (c)
	{
		num = ft_getfnumber(c + ft_strlen(param) + 1);
		if (num != 0)
			return (num);
	}
	return (dfval);
}

void		init_sphere(t_list *t, t_obj *p)
{
	float		r;
	t_vec3		origin;
	char		*st;

	p->type = sphere;
	p->data = (t_sphere *)malloc(sizeof(t_sphere));
	((t_sphere *)(p->data))->radius = read_fparam(t->content, "radius", 1);
	read_vec3_param(t->content, p->origin, "origin",(t_vec3){0,0,3});
	((t_sphere *)(p->data))->radius2 = ((t_sphere *)(p->data))->radius
	* ((t_sphere *)(p->data))->radius;
	st = ft_strstr(t->content, "color(");
	st = st != NULL ? st + 6 : st;
	p->material.diffuse_color.color = st!= NULL ?
	ft_strtol(st, &(st), 16) : 0xffffff;
}

void		init_light()
{
	float	intensity;
}

void		out_spheres(t_param *p)
{
	int			i;
	t_sphere	*sp;
	i = 0;
	while (i < p->world.nobjects)
	{
		sp = p->world.objects[i].data;
		printf("%fradius\n", sp->radius);
		printf("%fx ,%fy,%fz\n", p->world.objects[i].origin[ox], p->world.objects[i].origin[oy], p->world.objects[i].origin[oz]);
		i++;
	}
}

int			parse_obj(t_list *l, t_param *p, t_obj_type t, int *i, int *j)
{

	if (t == sphere)
	{
		init_sphere(l, p->world.objects + *i);
		*i += 1;
	}
}

int		parse_list(t_param *p, t_list *l)
{

	int			i;
	int			j;
	t_obj_type	t;
	t_sphere	*sp;

	i = 0;
	j = 0;
	while (l)
	{
		if ((t = find_type(l)) == none)
			return (0);
		parse_obj(l, p, t, &i, &j);
		l = l->next;
	}
	printf("%di, %dj", i, j);
	return (1);
}

void	delete_lst(void *s, size_t size)
{
	free(s);
	(void)size;
}

// void	get_sphere(t_obj *obj, t_vec3 origin, float radius, int color)
// {
// 	if (obj->data == NULL)
// 		obj->data = (t_sphere *)malloc(sizeof(t_sphere));
// 	((t_sphere *)(obj->data))->radius = radius;
// 	obj->type = sphere;
// 	vec3_copy(origin, obj->origin);
// 	obj->material.diffuse_color.color = color;
// 	obj->t = INFINITY;
// }

int		read_all(int fd, t_param *p)
{
	char	*str;
	t_list	*list;

	list = NULL;
	while (get_next_line(fd, &str))
	{
		if (list == NULL)
			list = ft_lstnew(str, ft_strlen(str));
		else
			ft_lstadd(&list, ft_lstnew(str, ft_strlen(str)));
		ft_strdel(&str);
	}
	if (fd < 0 || !list_len(list, p))
		return (0);
	if (!parse_list(p, list))
		ft_putstr("proeb");
	ft_lstdel(&list, delete_lst);
	out_spheres(p);
	return (1);
}
