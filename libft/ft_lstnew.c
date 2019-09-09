/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 19:39:33 by dwalda-r          #+#    #+#             */
/*   Updated: 2018/12/27 19:05:39 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*nlist;
	size_t		sizecpy;

	if ((nlist = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		nlist->content = NULL;
		nlist->content_size = 0;
		nlist->next = NULL;
		return (nlist);
	}
	sizecpy = content_size;
	if ((nlist->content = ft_memalloc(sizecpy)) == NULL)
		return (NULL);
	nlist->content = ft_memmove(nlist->content, content, sizecpy);
	nlist->content_size = sizecpy;
	nlist->next = NULL;
	return (nlist);
}
