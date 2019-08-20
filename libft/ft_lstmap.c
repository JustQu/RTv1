/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 05:05:43 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/17 16:13:41 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *retp;
	t_list *p;
	t_list *node;

	if (!lst || !f)
		return (NULL);
	p = (*f)(lst);
	retp = p;
	while ((lst = lst->next))
	{
		if (!(node = (*f)(lst)))
		{
			free(node);
			while (p)
			{
				node = p->next;
				free(p);
				p = node;
			}
			return (NULL);
		}
		p->next = node;
		p = p->next;
	}
	return (retp);
}
