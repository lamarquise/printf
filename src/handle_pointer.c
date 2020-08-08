/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:51:45 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 17:34:37 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int			ft_h_point_prec(char **str, t_param *p, size_t *len)		// Secure
{
	char	*pre;
	size_t	plen;

	if (!str || !p || !len)
		return (-1);
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
	return (1);	//was 1
}

int			ft_handle_pointer(va_list *ap, char **str, t_param *p)	// Secure
{
	char	*pre;
	size_t	len;
	size_t	wlen;

	if (!ap || !str || !p)
		return (-1);
	pre = NULL;
	if (!(*str = ft_any_base_convert((long)va_arg(*ap, void*), "0123456789abcdef")))
		return (-1);
	len = ft_fstrlen(*str);
	if (ft_h_point_prec(str, p, &len) == -1 || !(pre = ft_fstrdup("0x")) || !(*str = ft_fstrjoin(&pre, str)))
		return (ft_scott_free(str, -1));
	len = ft_fstrlen(*str);
	wlen = (p->width <= len ? 0 : p->width - len);	
	if (wlen)
	{
		if (p->flag & F_MINU)
		{
			if (!(pre = ft_fill_with(' ', wlen))
			|| !(*str = ft_fstrjoin(str, &pre)))
				return (ft_scott_free(str, -1));
		}
		else
		{ 
			if (!(pre = ft_fill_with(' ', wlen))
				|| !(*str = ft_fstrjoin(&pre, str)))
				return (ft_scott_free(str, -1));
		}
	}
	return (ft_fstrlen(*str));
}






