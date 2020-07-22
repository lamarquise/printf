/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_arg_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:20:16 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 19:11:49 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

	//only used for handle_int

int		ft_add_hash(char **pre, t_param *p)
{
	char *mid;

	mid = NULL;
	if (p->spec == 'x' && !(mid = ft_fstrdup("0x")))
		return (-1);
	else if (p->spec == 'X' && !(mid = ft_fstrdup("0X")))
		return (-1);
	else if (p->spec == 'o' && !(mid = ft_fstrdup("0")))
		return (-1);
	else if (p->spec == 'b' && !(mid = ft_fstrdup("0b")))
		return (-1);
	if (mid && !(*pre = ft_fstrjoin(&mid, pre)))
		return (-1);
	return (1);
}

	// only used for handle str and pointer
	// Seriously Double check that this shit does what i want it to, like leaks and such

int		ft_prec_is_zero(char **str, size_t *len)
{
	if (*str)
		free(*str);
	if (!(*str = ft_fstrdup("")))
		return (-1);
	*len = 0;
	return (1);
}

