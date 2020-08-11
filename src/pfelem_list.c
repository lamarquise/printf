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

t_pfelem	*ft_str_to_elem(char *str, int size) // secure
{
	t_pfelem	*new;
	char		*cp;
	int			num;
	
	if (!str)
		return (NULL);
	cp = NULL;
	new = NULL; // necessary ???
	num = (size < -1 ? ft_fstrlen(str) : size);
/*	if (!(cp = ft_substr(str, 0, num)))			// doesn't work in exacly 1 case...
		return (NULL);
	if (!(new = ft_new_pfelem(cp, size)))
		return ((t_pfelem*)ft_scott_free(&cp, 0));
*/
	if (!(cp = (char*)ft_memalloc(sizeof(char) * (num + 1))))
		return (NULL);
	if (!(new = ft_new_pfelem(ft_memcpy(cp, str, num), size)))
//	if (!(new = ft_new_pfelem(ft_memcpy(cp, str, -2), size)))
		return ((t_pfelem*)ft_scott_free(&cp, 0));



	return (new);
}

int		ft_pflist_append(t_pfelem **lst, t_pfelem *new)	// secure
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

int			ft_pflist_del_all(t_pfelem **lst)	// test security
{
	t_pfelem	*tmp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return (-1);
}
