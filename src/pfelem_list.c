/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfelem_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:48:49 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/27 18:45:21 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

t_pfelem	*new_pfelem(char *str)
{
	t_pfelem	*new;

	if (!str)
		return (NULL);
	if (!(new = (t_pfelem*)ft_memalloc(sizeof(t_pfelem))))
		return (NULL);
	new->content = str;
	new->next = NULL;
	return (new);
}


			// may not need a **lst,  *lst would do, i think...

int		pflist_append(t_pfelem **lst, t_pfelem *new)
{
	t_pfelem	*tmp;

//	printf("append list test 1\n");

//	printf("new content: [%s]\n", new->content);


	if (!lst || !new)
		return (0);
//	printf("append list test 1.1\n");
	if (!(*lst))
	{
//		printf("append list test 1.2\n");
		*lst = new;
//		printf("append list test 1.5\n");
		return (1);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;		// necessary???

//	printf("append list test 2\n");

	return (1);
}

t_pfelem	*ft_buf_to_elem( char *str)			// not constant char any more
{
	t_pfelem	*new;
	char		*cp;		// more efficeint to use a var for len
	int			l;

//	printf("buf to elem test 1\n");

	l = ft_strlen(str);
	if (!(cp = (char*)ft_memalloc(sizeof(char) * (l + 1))))
		return (NULL);
	new = new_pfelem(ft_strcpy(cp, str)/*, l*/);// something more secure ???

	// OR i could do the free of str here ???	

//	printf("buf to elem test 2, str: %s\n", str);

	return (new);


}
/*
int			ft_del_pflist(t_pfelem **lst)
{
	t_pfelem	*tmp;

	



}

*/




