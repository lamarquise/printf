/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:51:45 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/02 21:27:21 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// protection ??? all flags ???

#include "printf.h"

int			ft_handle_pointer(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	char	*pre;
	void	*nb;
	size_t	len;
	size_t	plen;
	size_t	wlen;

	pre = NULL;
	tmp = NULL;

	// 0x0 is address null

	// petite protection ???		// necessary ????

//	printf("pointer test 1\n");

	nb = va_arg(ap, void*);
//	printf("pointer test 2\n");

//	printf("pointer test 3 ptr: |%p|\n", tmp);


	tmp = ft_any_base_convert((long)nb, "0123456789abcdef");

	len = ft_fstrlen(tmp);

	// handle if null pointer ????

	// more flags ???


	if (p->flag & F_PREC && p->precision == 0)
	{
		tmp = ft_fstrdup("");
		len = 0;
	}
	

	plen = (p->precision <= len ? 0 : p->precision - len);

	if (plen)
	{
		pre = ft_fill_with('0', plen);
		tmp = ft_fstrjoin(&pre, &tmp);
	}


	pre = ft_fstrdup("0x");
	tmp = ft_fstrjoin(&pre, &tmp);
	len = ft_fstrlen(tmp);
	wlen = (p->width <= len ? 0 : p->width - len);
	
	if (wlen)
	{
		if (p->flag & F_MINU)
		{
			pre = ft_fill_with(' ', wlen);
			tmp = ft_fstrjoin(&tmp, &pre);
//			printf("is minu\n");
		}
		else
		{
			pre = ft_fill_with(' ', wlen);
			tmp = ft_fstrjoin(&pre, &tmp);
		}
	}
//	printf("pointer test 2, tmp: |%s|\n", tmp);

	*str = tmp;		// make this better... more elegant...
	return (ft_fstrlen(*str));
}






