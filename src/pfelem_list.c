/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfelem_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:48:49 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 20:56:54 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// seems good 

#include "printf.h"

t_pfelem	*ft_new_pfelem(char *str, int size)
{
	t_pfelem	*new;

	if (!str)
		return (NULL);
	if (!(new = (t_pfelem*)ft_memalloc(sizeof(t_pfelem))))
		return (NULL);
	new->content = str;
	new->size = size;
	new->next = NULL;
	return (new);
}

int		ft_pflist_append(t_pfelem **lst, t_pfelem *new)
{
	t_pfelem	*tmp;

	if (!lst || !new)
		return (0);
	if (!(*lst))
	{
		*lst = new;
		return (1);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (1);
}

t_pfelem	*ft_buf_to_elem(char *str, int size)
{
	t_pfelem	*new;
	char		*cp;

	if (!str)
		return (NULL);
	if (!(cp = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (!(new = ft_new_pfelem(ft_memcpy(cp, str, size), size)))
		return (NULL);
	return (new);
}

int			ft_pflist_del_all(t_pfelem **lst)
{
	t_pfelem	*tmp;

	if (!lst)
		return (0);		// -1 ???
	if (!*lst)
		return (-1);			// dif ret here or in ft_priuntf...
	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
	return (-1);		// correct ret ???
}

