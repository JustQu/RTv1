/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:59:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/13 16:12:38 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		normalize_light(t_param *p)
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

char		*str_to_low(char *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		if (ft_isupper(str[i]))
			str[i] += 'a' - 'A';
	return (str);
}

t_obj_type	find_type(t_list *l)
{
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
