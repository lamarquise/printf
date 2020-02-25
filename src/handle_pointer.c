/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:51:45 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/25 19:18:36 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int			ft_handle_pointer(va_list ap, char **str, t_param *p)
{
	char	*tmp;

	// 0x0 is address null

	// petite protection ???

	tmp = ft_any_base_convert(va_arg(ap, int), "0123456789abcdef");		// what happens if pointer is NULL ??? it should make 0 to then make 0x0


	// any flags ????

	*str = ft_fstrjoin("0x", tmp);
	return (1);
}

int			ft_handle_binairy(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	int		num;		// int ???

	// also petite protection...

	num = va_arg(ap, int);
	tmp = ft_any_base_convert(num, "01");

	*str = tmp; // any flags ????

	return (1);
}
