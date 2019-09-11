/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 10:06:00 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/11 15:01:30 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*ft_itoaf(float val, int fdigits)
{
	char		*nnum;
	float		fpart;
	char		*fnum;
	char		*tmp;
	int			sign;

	sign = val < 0 && fabs(val) < 1 ? -1 : 1;
	nnum = ft_itoa((int)val);
	val = val < 0 ? -val : val;
	fpart = val - (int)val;
	fpart *= pow(10, fdigits);
	fpart += pow(10, fdigits);
	fnum = ft_itoa((int)fpart);
	tmp = ft_strjoin(".", fnum + 1);
	ft_strdel(&fnum);
	fnum = ft_strjoin(nnum, tmp);
	ft_strdel(&tmp);
	ft_strdel(&nnum);
	if (sign == -1)
	{
		tmp = ft_strjoin("-", fnum);
		ft_strdel(&fnum);
		return(tmp);
	}
	return (fnum);
}

void	print_fnumber(float val, int fd, int fdigits)
{
	char *c;

	c = ft_itoaf(val, fdigits);
	ft_putstr_fd(c, fd);
	ft_strdel(&c);
}

void	out_fparam(float val, char *param, int fd)
{
	ft_putstr_fd(param, fd);
	ft_putchar_fd('(', fd);
	print_fnumber(val, fd, 3);
	ft_putstr_fd(") ", fd);

}

void	out_v3_param(t_vec3 val, char *param, int fd)
{
	ft_putstr_fd(param, fd);
	ft_putchar_fd('(', fd);
	print_fnumber(val[ox], fd, 3);
	ft_putstr_fd(", ", fd);
	print_fnumber(val[oy], fd, 3);
	ft_putstr_fd(", ", fd);
	print_fnumber(val[oz], fd, 3);
	ft_putstr_fd(") ", fd);
}

int		find_int_len(int val)
{
	int size;

	size = 0;
	while (val > 0)
	{
		val /= 10;
		size++;
	}
	return size;
}

void	convert_to16(int val, char *num, char *ax)
{
	char	*tmp;
	char	swap;

	if (!val)
		return ;
	tmp = num;
	while (val > 0)
	{
		*num = ax[val % 16];
		num++;
		val = val / 16;
	}
	num--;
	while(num - tmp > 0)
	{
		swap = *tmp;
		*tmp = *num;
		*num = swap;
		num--;
		tmp++;
	}
}

void	out_material(t_material material, int fd)
{
	char	*num;
	char	*ax;

	ax = ft_strdup("0123456789abcdef");
	num = ft_strnew(find_int_len(material.diffuse_color.color));
	convert_to16(material.diffuse_color.color, num, ax);
	ft_putstr_fd("color(", fd);
	ft_putstr_fd(num, fd);
	ft_putstr_fd(") ", fd);
	ft_strdel(&ax);
	ft_strdel(&num);
	out_fparam(material.n, "num", fd);
	out_fparam(material.Ks, "ks", fd);
	out_fparam(material.Kd, "kd", fd);
	ft_putchar_fd(';', fd);
}

void	out_plane(t_obj obj, int fd)
{
	t_plane	*plane;

	plane = obj.data;
	ft_putstr_fd("plane: ", fd);
	out_v3_param(obj.origin, "origin", fd);
	out_v3_param(plane->nv, "nv", fd);
	//out_material(obj.material, fd);
}

void	out_sphere(t_obj obj, int fd)
{
	t_sphere	*sphere;

	sphere = obj.data;
	ft_putstr_fd("sphere: ", fd);
	out_v3_param(obj.origin, "origin", fd);
	out_fparam(sphere->radius, "radius", fd);
	//out_material(obj.material, fd);
}

void	out_cone(t_obj obj, int fd)
{
	t_cone	*cone;

	cone = obj.data;
	ft_putstr_fd("cone: ", fd);
	out_v3_param(obj.origin, "origin", fd);
	out_v3_param(cone->dir, "direction", fd);
	out_fparam(cone->angle, "angle", fd);
	//out_material(obj.material, fd);
}

void	out_cylinder(t_obj obj, int fd)
{
	t_cylinder	*cyl;

	cyl = obj.data;
	ft_putstr_fd("cylinder: ", fd);
	out_v3_param(obj.origin, "origin", fd);
	out_v3_param(cyl->direction, "direction", fd);
	out_fparam(cyl->radius, "radius", fd);
	//out_material(obj.material, fd);
}

void	out_camera(t_camera cam, int fd)
{
	ft_putstr_fd("camera: ", fd);
	out_v3_param(cam.pos, "position", fd);
	out_v3_param(cam.orientation, "orientation", fd);
	out_fparam(cam.fov, "fov", fd);
}

void	output_light(t_light_source l, int fd)
{
	ft_putstr_fd("lightsource: ", fd);
	out_v3_param(l.origin, "origin", fd);
	out_fparam(l.intensity, "intensity", fd);
	ft_putchar_fd('\n', fd);
}

void	output_obj(t_obj obj, int fd)
{
	if (obj.type == plane)
		out_plane(obj, fd);
	else if (obj.type == sphere)
		out_sphere(obj, fd);
	else if (obj.type == cone)
		out_cone(obj, fd);
	else if (obj.type == cylinder)
		out_cylinder(obj, fd);
	ft_putchar_fd('\n', fd);
}

void	output_data(t_param *p)
{
	int		i;
	t_obj	*obj;

	i = -1;
	while (++i < p->world.nobjs)
		output_obj(p->world.objs[i], p->fd);
	i = -1;
	while (++i < p->world.nlights)
		output_light(p->world.lights[i], p->fd);
	out_camera(p->camera, p->fd);
	ft_putendl_fd("", p->fd);
}

void	file_save(t_param *p)
{
	int	fd;

	fd = open("save.scene", O_CREAT | O_WRONLY | O_TRUNC);
	p->fd = fd;
	output_data(p);
	close(fd);
}
