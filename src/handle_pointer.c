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

	// do i need to add protections ???
	// are there other flags to mange
	// does it need a ft_cast ???
	// secure


#include "printf.h"

	// more secure ?

int			ft_handle_pointer_prec(char **str, t_param *p, size_t *len)
{
	char	*pre;
	size_t	plen;

	pre = NULL;
	if (p->flag & F_PREC && p->precision == 0 && !ft_prec_is_zero(str, len))
		return (-1);
	plen = (p->precision <= *len ? 0 : p->precision - *len);
	if (plen)
	{
		if (!(pre = ft_fill_with('0', plen))
		|| !(*str = ft_fstrjoin(&pre, str)))
			return (-1);
	}
//	printf("str: |%s|\n", *str);
	return (1);
}

	// yeeted nb and tmp
	// handle if null pointer ????
	// more flags ???
	// 0x0 is address null

int			ft_handle_pointer(va_list *ap, char **str, t_param *p)
{
	char	*pre;
	size_t	len;
//	size_t	plen;
	size_t	wlen;

	pre = NULL;
	if (!(*str = ft_any_base_convert((long)va_arg(*ap, void*), "0123456789abcdef")))
		return (-1);
	len = ft_fstrlen(*str);

	if (!ft_handle_pointer_prec(str, p, &len))
		return (-1);


	if (!(pre = ft_fstrdup("0x")) || !(*str = ft_fstrjoin(&pre, str)))
		return (ft_scott_free(str));	// too secure ?	// also free pre ?
	len = ft_fstrlen(*str);
	wlen = (p->width <= len ? 0 : p->width - len);	
	if (wlen)
	{
		if (p->flag & F_MINU)
		{
			if (!(pre = ft_fill_with(' ', wlen))
			|| !(*str = ft_fstrjoin(str, &pre)))
				return (-1); // or scott_free ?
		}
		else
		{ 
			if (!(pre = ft_fill_with(' ', wlen))
				|| !(*str = ft_fstrjoin(&pre, str)))
				return (-1); // or scott_free ?
//			printf("here ?\n");
		}
	}
	return (ft_fstrlen(*str));
}






