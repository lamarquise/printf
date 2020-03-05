/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_modulo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:35:59 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/02 21:27:40 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// other flags ???
	// protect cuz why not ???


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
	{
		post = ft_fstrdup(" ");
		pre = ft_fstrjoin(&post, &pre);
	}
			// can make % == str...

	*str = ft_fstrdup("%");
	pre = ft_fstrjoin(&pre, str);
	*str = ft_fstrjoin(&pre, &post);

//	printf("modulo test 1, width: %zu, str |%s|\n", p->width, *str);

	// free shit like pre and post ????
	
	return (p->width > 0 ? p->width : 1);		// 1 ???
}
