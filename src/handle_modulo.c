/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_modulo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:35:59 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/25 17:51:35 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// other flags ???

#include "printf.h"

int		ft_handle_modulo(char **str, t_param *p)
{
	char	*pre;
	char	*post;
	char	c;

	pre = NULL;
	post = NULL;
	if (p->width > 1)
	{
		c = ' ';
		if (p->flag & F_MINU)
		{
			post = ft_fill_with(c, p->width - 1);
//			printf("theres a -\n");
		}
		else
		{
			if (p->flag & F_ZERO)
				c = '0';
			pre = ft_fill_with(c, p->width - 1);
		}
	}
	else if (p->flag & F_SPAC)
		pre = ft_fstrjoin(" ", pre);

	*str = ft_fstrjoin(ft_fstrjoin(pre, "%"), post);

//	printf("modulo test 1, width: %zu, str |%s|\n", p->width, *str);

	// free shit like pre and post ????
	
	return (1);		// 1 ???
}
