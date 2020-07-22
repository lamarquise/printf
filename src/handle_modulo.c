/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_modulo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:35:59 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 17:33:45 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_handle_modulo(char **str, t_param *p)
{
	char	*add;
	char	c;

	if (!str || !p)
		return (-1);
	add = NULL;
	if (!(*str = ft_fstrdup("%")))
		return (-1);
	if (p->width > 1)
	{
		c = ' ';
		if (p->flag & F_MINU)
		{
			if (!(add = ft_fill_with(c, p->width - 1))
				|| !(*str = ft_fstrjoin(str, &add)))
				return (-1);
		}
		else
		{
			if (p->flag & F_ZERO)
				c = '0';
			if (!(add = ft_fill_with(c, p->width - 1))
				|| !(*str = ft_fstrjoin(&add, str)))
				return (-1);
		}
	}
	return (p->width > 0 ? p->width : 1);
}
