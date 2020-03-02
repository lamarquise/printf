/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfelem_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:48:49 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/02 21:34:16 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// double check some things, free things ???
	// make an elem_del func ???

#include "printf.h"

t_pfelem	*new_pfelem(char *str, int size)
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

int		pflist_append(t_pfelem **lst, t_pfelem *new)
{
	t_pfelem	*tmp;

	printf("new content: [%s]\n", new->content);

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
	new->next = NULL;		// necessary???

	printf("append list test 2\n");
	return (1);
}

t_pfelem	*ft_buf_to_elem(char *str, int size)
{
	t_pfelem	*new;
	char		*cp;

//	printf("buf to elem test 1\n");

	if (!(cp = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	new = new_pfelem(ft_strcpy(cp, str), size);	// something more secure ???

	// could actually scott free str here...

//	printf("buf to elem test 2, str: %s\n", str);
	return (new);
}
