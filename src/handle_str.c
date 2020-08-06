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

	// double check the return...

int				ft_handle_str(va_list *ap, char **str, t_param *p)	// Secure except Gen Arg
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


	int a;

	a = ft_gen_arg_str_s(p, str, len);	// secure !!!!!!!!

//	printf("a = %d\n", a);

	return (a);
//	printf("crusial str: |%s|\n", *str);

//	return (ft_fstrlen(*str));		// not len += n ????
}


	// this whole thing needs mad security...

int			ft_gen_arg_str_s(t_param *p, char **str, size_t len)
{
	char	c;
	int		n;	// do i need n ?
	char	*pre;
	char	*post;

//	printf("len at start: %zu\n", len);
	pre = NULL;
	post = NULL;
	if (p->flag & F_PREC)
	{
		if (p->precision == 0 && ft_prec_is_zero(str, &len) == -1)
			return (-1);		// scott free str
		else if ((n = (p->precision < len ? p->precision : 0)) > 0)
		{
			pre = ft_substr(*str, 0, n);	// secure
			ft_scott_free(str, 0);
			*str = pre;
			pre = NULL;
			len = n;
		}
		// free things ????
	}
//	printf("len in mid: %zu\n", len);
	n = (p->width <= len ? 0 : p->width - len);
	c = ' ';
	if (n)		// double check what happens when n = 0
	{
		if (p->flag & F_MINU)
		{
//			post = ft_fill_with(c, n);
			pre = ft_fill_with(c, n);		// is better but i hate it...
			*str = ft_fstrjoin(str, &pre);	// WHY LIKE THIS !!!!
			return (len + n);
//			pre = NULL;
		}
		else
		{
			if (p->flag & F_ZERO)
				c = '0';
			pre = ft_fill_with(c, n);
		}
	}
	else if (p->flag & F_SPAC)
	{
		pre = ft_fill_with(c, 1);
	//	something = ft_cstrjoin(' ', &pre); // and secure...
		++len;
	}
//	printf("len at end: %zu\n", len);

	*str = ft_fstrjoin(str, &post);		// 2 of these is too many
	*str = ft_fstrjoin(&pre, str);

	return (len + n);
}

