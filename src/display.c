/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:57:48 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/27 18:48:48 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

	// can do this the old way if i want, but for now...

		// displays and deletes
		// could easily add a fd arg

int		ft_display_del(int fd, t_pfelem **lst)
{
	int			c;
	int			len;
	t_pfelem	*tmp;

//	printf("display test 1\n");

//	printf("buf lst: [%s]\n", buf->lst->content);

	c = 0;
	len = 0;
	if (!lst)
		return (-1);
	while (*lst)	// maybe secure, if something fucks up then ret 0....
	{
		if ((*lst)->content[0] == '\0')
		{
			write(fd, ft_itoa(c), ft_fstrlen(ft_itoa(c)));	// will it work ????
			c = 0;
		}
		else
		{
			len += ft_fstrlen((*lst)->content);
			write(fd, (*lst)->content, len);
			c += len;
		}
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
	printf("display test 3 final\n");
	return (1);
}
