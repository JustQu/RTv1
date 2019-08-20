/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:54:32 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 08:06:09 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Determine length of NEEDLE, and in the process, make sure
** HAYSTACK is at least as long (no point processing all of a long
** NEEDLE if HAYSTACK is too short).
*/

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*pneedle;
	const char	*phaystack;
	int			ok;

	ok = 1;
	pneedle = needle;
	phaystack = haystack;
	while (*phaystack && *pneedle)
		ok &= *phaystack++ == *pneedle++;
	if (*pneedle)
		return (NULL);
	if (ok)
		return ((char *)(haystack));
	pneedle = needle;
	while (*haystack && *needle)
		if (*haystack++ == *needle)
			needle++;
		else
		{
			haystack -= needle - pneedle;
			needle = pneedle;
		}
	return (*(needle) ? NULL : (char *)(haystack - (needle - pneedle)));
}
