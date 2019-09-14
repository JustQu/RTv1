/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 02:56:09 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/11 09:56:54 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	s11;
	unsigned char	s22;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n )
		i++;
	if (i >= n)
		i--;
	s11 = s1[i];
	s22 = s2[i];
	return (s11 - s22);
}
