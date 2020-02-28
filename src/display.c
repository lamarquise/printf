/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:57:48 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/28 19:23:19 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_display_del(int fd, t_pfelem **lst)
{
	int			c;
	int			len;
	char		*str;
	t_pfelem	*tmp;

//	printf("display test 1\n");

	c = 0;
	len = 0;
	str = NULL;
	if (!lst)
		return (-1);
	while (*lst)	// maybe secure, if something fucks up then ret 0....
	{
		if ((*lst)->content[0] == '\0')
		{
			str = ft_itoa(c);
			write(fd, str, ft_fstrlen(str));
			c = ft_fstrlen(str);
			ft_scott_free(&str);
		}
		else
		{
			len = ft_fstrlen((*lst)->content);
			write(fd, (*lst)->content, len);
			c += len;
		}
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
//	printf("display test 3 final\n");
	return (1);
}
