/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:05:43 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 19:04:55 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// needs to be shorter. more concise ?
	// double check the return for str, and char why not


#include "printf.h"

int				ft_handle_char(va_list *ap, char **str, t_param *p)	// Secure
{
	size_t	len;
	size_t	plen;
	size_t	wlen;

	if (!ap || !str || !p)
		return (-1);
	len = 1;
	plen = 0;
	if (p->flag & F_PREC && p->precision == 0)
		len = 0;
	if ((wlen = (p->width <= len ? 0 : p->width - len)))
	{
		if (p->flag & F_MINU)
		{
			plen = wlen;
			wlen = 0;
		}
	}
	else if (p->flag & F_SPAC)
		wlen = 1;
	if (!(*str = ft_fill_with(' ', len + wlen + plen)))
		return (-1);
	if (len)
		(*str)[wlen] = (char)va_arg(*ap, int);
	return (len + wlen + plen);
}

	// secure i think but test error cases
int				ft_handle_str(va_list *ap, char **str, t_param *p)
{
	size_t	len;

	if (!ap || !str || !p)
		return (-1);
	if (ft_nstrdup(str, va_arg(*ap, char*)) == -1)
		return (-1);		// scott_free str ? just in case
	len = ft_fstrlen(*str);		// shouldn't exist but what if it does...
	if (!*str)
	{
		if (!(*str = ft_fstrdup("(null)")))
			return (-1);
		p->flag |= (1 << 7);
		len = 6;
	}
	return (ft_gen_arg_str_s(p, str, len));
}

	// secure i think but test...
int			ft_gen_arg_str_s(t_param *p, char **str, size_t len)
{
	if (!p || !str)
		return (ft_scott_free(str, -1));
	if (p->flag & F_PREC && ft_h_str_prec(p, str, &len) == -1)
		return (ft_scott_free(str, -1));
	if ((len = ft_h_str_wid(p, str, len)) == -1)
		return (ft_scott_free(str, -1));
	return (len);
}

