/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:42:09 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/03/15 18:45:24 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_input(int fd, char **str)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	ret = 0;
	if (*str)
		if (ft_strchr(*str, (int)'\n'))
			return (1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (!*str)
			*str = ft_strdup("");
		buff[ret] = 0;
		tmp = *str;
		*str = ft_strjoin(*str, buff);
		ft_strdel(&tmp);
		if (ft_strchr(buff, (int)'\n'))
			break ;
	}
	if (ret < 0)
	{
		ft_strdel(str);
		return (-1);
	}
	return (1);
}

static int	generate_line(char **str, char **line)
{
	char	*tmp;
	int		n;

	if ((tmp = ft_strchr(*str, (int)'\n')) == NULL)
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	else
	{
		n = tmp - *str;
		*line = ft_strsub(*str, 0, n++);
		tmp = ft_strdup(*str + n);
		ft_strdel(str);
		*str = tmp;
		tmp = NULL;
		if (*str[0] == '\0')
			ft_strdel(str);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char *inf[OPEN_MAX];

	if (fd < 0 || !line || fd >= OPEN_MAX)
		return (-1);
	if (read_input(fd, &(inf[fd])) == -1)
		return (-1);
	if (inf[fd])
		return (generate_line(&(inf[fd]), line));
	else
		return (0);
}
