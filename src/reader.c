/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:23:23 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/11 14:26:14 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj_type	find_type(t_list *l)
{
	char *str = l->content;
	if (!l->content)
		return (none);
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
	else if (!ft_strncmp("camera", l->content, ft_strlen("camera")))
		return (camera);
	else
		return (none);
}

size_t		list_len(t_list *l, t_param *p)
{
	size_t	len;
	size_t	lnum;
	t_obj_type tp;

	lnum = 0;
	len = 0;
	while (l)
	{
		if ((tp = find_type(l)) == light)
		{
			lnum++;
			len++;
		}
		else if (tp != none && tp != camera)
			len++;
		l = l->next;
	}
	p->world.nlights = lnum;
	p->world.nobjs = len - lnum;
	if (lnum)
		p->world.lights = (t_light_source *)malloc(sizeof(t_light_source) * lnum);
	if (p->world.nobjs)
		p->world.objs = (t_obj *)malloc(sizeof(t_obj) * p->world.nobjs);
	return (len);
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

void			read_vec3_param(char *str, t_vec3 v3param,
								char *param, t_vec3 v3def)
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

void	noramlize_2values(float *first, float *second)
{
	float	sum;

	sum = 0;
	sum = *first + *second;
	if (sum != 0)
	{
		*first /= sum;
		*second /= sum;
	}
}

t_material	read_material(char *str, t_color dcolor)
{
	t_material	mat;
	char		*st;

	st = ft_strstr(str, "color(");
	st = st != NULL ? st + 6 : st;
	mat.diffuse_color.color = st!= NULL ? ft_strtol(st, &(st), 16) : dcolor.color;
	mat.Kd = read_fparam(str, "kd", 0);
	mat.Ks = read_fparam(str, "ks", 0);
	noramlize_2values(&mat.Kd, &mat.Ks);
	if (mat.Kd == 0 || mat.Ks == 0)
	{
		if (mat.Kd != 0)
			mat.Ks = 1 - mat.Kd;
		else if (mat.Ks != 0)
			mat.Kd = 1 - mat.Ks;
		else
		{
			mat.Kd = 0.8;
			mat.Ks = 0.2;
		}
	}
	mat.n = read_fparam(str, "num", 50);
	return (mat);
}

void		init_sphere(t_list *t, t_obj *p)
{
	float		r;
	t_vec3		origin;
	t_color		dcolor;

	dcolor.color = 0x96d38c;
	p->type = sphere;
	p->data = (t_sphere *)malloc(sizeof(t_sphere));
	((t_sphere *)(p->data))->radius = read_fparam(t->content, "radius", 0.2);
	read_vec3_param(t->content, p->origin, "origin",(t_vec3){0,0,3});
	((t_sphere *)(p->data))->radius2 = ((t_sphere *)(p->data))->radius
	* ((t_sphere *)(p->data))->radius;
	p->material = read_material(t->content, dcolor);
}

void		init_light(t_list *t, t_light_source *light)
{
	read_vec3_param(t->content, light->origin, "origin", (t_vec3){0, 1, 0});
	light->intensity = read_fparam(t->content, "intensity", 0.8);
}

void		out_spheres(t_param *p)
{
	int			i;
	t_sphere	*sp;
	i = 0;
	while (i < p->world.nobjs)
	{
		sp = p->world.objs[i].data;
		printf("%f\n",p->world.objs[i].material.n);
		printf("%fradius\n", sp->radius);
		printf("%fx ,%fy,%fz\n", p->world.objs[i].origin[ox], p->world.objs[i].origin[oy], p->world.objs[i].origin[oz]);
		i++;
	}
}

void		init_plane(t_list *t, t_obj *p)
{
	t_color		dcolor;

	dcolor.color = 0xc4def6;
	p->type = plane;
	p->data = (t_plane *)malloc(sizeof(t_plane));
	read_vec3_param(t->content, ((t_plane *)p->data)->nv,
	"nv", (t_vec3){0, -1, 0});
	vec3_normalize(((t_plane *)p->data)->nv);
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0, -1, 0});
	p->material = read_material(t->content, dcolor);
}

void		init_cone(t_list *t, t_obj *p)
{
	t_color		dcolor;

	dcolor.color = 0x213458;
	p->type = cone;
	p->data = (t_cone *)malloc(sizeof(t_cone));
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0, 0, 4});
	read_vec3_param(t->content, ((t_cone *)p->data)->dir,
	"direction", (t_vec3){0, 1, 0});
	vec3_normalize(((t_cone *)p->data)->dir);
	((t_cone *)p->data)->angle = read_fparam(t->content, "angle", 0.5);
	((t_cone *)p->data)->k = tan(((t_cone *)p->data)->angle);
	((t_cone *)p->data)->k2 = 1 + ((t_cone *)p->data)->k * ((t_cone *)p->data)->k;
	p->material = read_material(t->content, dcolor);
}

void		init_cylinder(t_list *t, t_obj *p)
{
	t_color		dcolor;

	dcolor.color = 0xffd464;
	p->type = cylinder;
	p->data = (t_cylinder *)malloc(sizeof(t_cylinder));
	read_vec3_param(t->content, p->origin, "origin", (t_vec3){0, 0, 4});
	read_vec3_param(t->content, ((t_cylinder *)p->data)->direction,
	"direction", (t_vec3){0, 1, 0});
	vec3_normalize(((t_cylinder *)p->data)->direction);
	((t_cylinder *)p->data)->radius = read_fparam(t->content, "radius", 0.3);
	p->material = read_material(t->content, dcolor);
}

void		init_camera(t_list *t, t_camera *camera)
{
	read_vec3_param(t->content, camera->pos, "position",
	(t_vec3){0,0,1});
	camera->near_z = read_fparam(t->content, "near_z", 1);
	read_vec3_param(t->content, camera->orientation,
	"orientation", (t_vec3){0, 0, 1});
	camera->fov = read_fparam(t->content, "fov", 45);
	camera->inv_width = 1.0f / WIDTH;
	camera->inv_height = 1.0f / HEIGHT;
	camera->aspectratio = WIDTH / (float)HEIGHT;
	camera->angle = tanf(RTM_PI * 0.5f * camera->fov / 180.0f);
}

void		parse_obj(t_list *l, t_param *p, t_obj_type t)
{
	static int		i;
	static int		j;

	if (!l)
		return ;
	if (t == sphere)
		init_sphere(l, p->world.objs + i++);
	else if (t == light)
		init_light(l, p->world.lights + j++);
	else if (t == plane)
		init_plane(l, p->world.objs + i++);
	else if (t == cone)
		init_cone(l, p->world.objs + i++);
	else if (t == cylinder)
		init_cylinder(l, p->world.objs + i++);
}

void	set_default_camera(t_camera *camera)
{
	camera->pos[ox] = 0.0f;
	camera->pos[oy] = 0.0f;
	camera->pos[oz] = 0.0f;
	camera->near_z = 1;
	camera->orientation[ox] = 0.0f;
	camera->orientation[oy] = 0.0f;
	camera->orientation[oz] = 1.0f;
	camera->fov = 45;
	camera->inv_width = 1.0f / WIDTH;
	camera->inv_height = 1.0f / HEIGHT;
	camera->aspectratio = WIDTH / (float)HEIGHT;
	camera->angle = tanf(RTM_PI * 0.5f * camera->fov / 180.0f);
}


int		parse_list(t_param *p, t_list *l)
{
	t_obj_type	t;
	t_sphere	*sp;
	int			camflag;

	camflag = 0;
	while (l)
	{
		if ((t = find_type(l)) != none && t != camera)
			parse_obj(l, p, t);
		else if (!camflag && t == camera)
		{
			camflag = 1;
			init_camera(l, &(p->camera));
		}
		l = l->next;
	}
	if (!camflag)
	set_default_camera(&(p->camera));
	return (1);
}

void	delete_lst(void *s, size_t size)
{
	ft_memdel(&s);
	(void)size;
}

char	*str_to_low(char *str)
{
	int		i;

	i = -1;
	while(str[++i] != '\0')
		if(ft_isupper(str[i]))
			str[i] += 'a' - 'A';
	return(str);
}

void	normalize_light(t_param *p)
{
	float			summ;
	int				i;
	t_light_source	*light;

	summ = 0;
	i = -1;
	while (++i < p->world.nlights)
	{
		light = p->world.lights + i;
		summ += light->intensity;
	}
	i = -1;
	while (++i < p->world.nlights)
	{
		light = p->world.lights + i;
		light->intensity /= summ;
	}
}

int		read_all(int fd, t_param *p)
{
	char	*str;
	t_list	*list;

	list = NULL;
	while (get_next_line(fd, &str))
	{
		str = str_to_low(str);
		if (list == NULL)
			list = ft_lstnew(str, ft_strlen(str) + 1);
		else
			ft_lstadd(&list, ft_lstnew(str, ft_strlen(str) + 1));
		ft_strdel(&str);
	}
	if (fd < 0 || !list || !list_len(list, p))
		return (0);
	if (!parse_list(p, list))
		ft_putstr("proeb");
	ft_lstdel(&list, delete_lst);
	normalize_light(p);
	return (1);
}
