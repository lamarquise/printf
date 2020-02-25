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

#includ "printf.h"

			// no va_list ap
int		ft_handle_modulo(char **str, t_param *p)
{
	char	*pre;
	char	*post;
	char	c;

	pre = NULL;
	post = NULL;
	if (p->width > 1)	// there is a width
	{
		c = ' ';
		if (p->flag & 7)	// left justify
		{
			post = ft_fill_with(c, p->width - 1);
		}
		else if (p->flag & 1)	// theres a '0'
		{
			c = '0';
		}
		pre = ft_fill_with(c, p->width - 1);
	}
	else if (p->flag & 0x10)
	{
		pre = ft_fstrjoin(" ", pre);
	}


	*str = ft_fstrjoin(ft_fstrjoin(pre, "%"), post);
	
	return (1);		// 1 ???
}
