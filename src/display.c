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
	// need to fix %N

#include "printf.h"

int		ft_display_del(int fd, t_pfelem **lst)
{
	int			c;
	int			ret;
	int			len;
	char		*str;
	t_pfelem	*tmp;

//	printf("display test 1\n");

	c = 0;
	ret = 0;
	len = 0;
	str = NULL;
	if (!lst)
		return (-1);
	while (*lst)	// maybe secure, if something fucks up then ret 0....
	{
/*		if ((*lst)->content[0] == '\0')	// needs to be fixed...
		{
			str = ft_itoa(c);
			write(fd, str, ft_fstrlen(str));
			c = ft_fstrlen(str);
			ret += c;
			ft_scott_free(&str);
		}
		else
		{
*/	//		printf("[lst cont: |%s|\n]", (*lst)->content);

//			len = ft_fstrlen((*lst)->content);
//			printf("display size: %d\n", (*lst)->size);

			write(fd, (*lst)->content, (*lst)->size);
			c += (*lst)->size;
			ret += (*lst)->size;
//		}
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
//	printf("display test 3 final\n");
	return (ret);
}
