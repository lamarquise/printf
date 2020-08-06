/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:57:48 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 20:32:27 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// make sure frees are good...
	// double check %n
	// double check %N
	

#include "printf.h"

int		ft_display_del(int fd, t_pfelem **lst)
{
	int			c;
	int			ret;
	int			len;
	long			another;
	int			*test;	// temporary var ?
	char		*str;
	t_pfelem	*tmp;

//	printf("display test 1\n");

	c = 0;
	ret = 0;
	len = 0;
	str = NULL;
	test = NULL;
	another = 0;
	if (!lst)
		return (-1);
	while (*lst)
	{
		if ((*lst)->size == -2)	// %N we print # printed so far
		{
			str = ft_itoa(c);
			write(fd, str, ft_fstrlen(str));
			c = ft_fstrlen(str);
			ret += c;
			ft_scott_free(&str, 0);
		}
		else if ((*lst)->size == -3) //%n # printed so far to pointer
		{
			int		arb;
			arb = ft_latoi((*lst)->content, &another);
			test = (int*)another;
			*test = c;
		}
		else
		{
			len += (*lst)->size;
			write(fd, (*lst)->content, (*lst)->size);
			c += (*lst)->size;
			ret += (*lst)->size;
		}
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
//	printf("display test 3 final\n");
	return (ret);
}
