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

#include "printf.h"

t_pfelem	*ft_new_pfelem(char *str, int size)//secured by call & ret in ft_str_to_elem
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

int		ft_pflist_append(t_pfelem **lst, t_pfelem *new)	// secure
{
	t_pfelem	*tmp;

	if (!lst || !new)
		return (-1);
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

t_pfelem	*ft_str_to_elem(char *str, int size) // secure but ugly
{
	t_pfelem	*new;
	char		*cp;

	if (!str)
		return (NULL);
	if (!(cp = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (!(new = ft_new_pfelem(ft_memcpy(cp, str, size), size)))
		return (ft_scott_free(&cp) == -1 ? NULL : NULL);			// ewww
	return (new);
}

int			ft_pflist_del_all(t_pfelem **lst)
{
	t_pfelem	*tmp;

	if (!lst)
		return (-1);	// make better ???
	if (!*lst)
		return (-1);
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

