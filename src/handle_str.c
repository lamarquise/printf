/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:05:43 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 21:24:37 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// needs to be shorter. more concise ?
	// add a ft_cast like for ints  ????	No.
	// double check the return for str, and char why not


#include "printf.h"

	// this is for those times when you need to verify with a number..
	// add to lib ?

int				ft_nstrdup(char **cp, char *og)
{
	int		a;

//	return (-1);
	if (!og || !cp)
		return (-1);
	if (*cp)
		free(*cp);		// should work ?
	a = 0;
	while (og[a])
		++a;
	if (!(*cp = ft_memalloc(sizeof(char) * (a + 1))))
		return (-1);
	a = 0;
	while (og[a])
	{
		(*cp)[a] = og[a];
		++a;
	}
	return (1);
}

	// does - take precedent over space for char flags ?
	// my algo has it being that way.

int				ft_handle_char(va_list *ap, char **str, t_param *p)
{
	size_t	len;
	size_t	plen;
	size_t	wlen;		// char *tmp got cut

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
	if (!*str)			// necessary?
		return (-1);
	return (len + wlen + plen);
}

	// double check the return...

int				ft_handle_str(va_list *ap, char **str, t_param *p)
{
	size_t	len;

	len = 0;		// unnecessary...
	if (p->spec == 's')		// unnecessary
	{
//		if (!(*str = ft_fstrdup(va_arg(ap, char*))))
//			return (-1);
		if (!(ft_nstrdup(str, va_arg(*ap, char*))))
			return (-1);
/*		if (!(ft_nstrdup(str, ft_cast_s(ap, p, str))))
			return (-1);
		ft_cast_s(ap, p, str);	*/
		len = ft_fstrlen(*str);
	}

//	printf("str: |%s|\n", *str);

	if (!*str)
	{
		
		if (!(*str = ft_fstrdup("(null)")))
			return (-1);
		p->flag |= (1 << 7);	// after width
		len = 6;
	}
//	printf("test 2\n");


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
	int		n;
	char	*pre;
	char	*post;

//	printf("len at start: %zu\n", len);
	pre = NULL;
	post = NULL;
	if (p->flag & F_PREC)
	{
		if (p->precision == 0 && !ft_prec_is_zero(str, &len))
			return (-1);
		else if ((n = (p->precision < len ? p->precision : 0)) > 0)
		{
			pre = ft_substr(*str, 0, n);
			ft_scott_free(str);
			*str = pre;
			pre = NULL;
			len = n;
		}
		// free things ????
	}
//	printf("len in mid: %zu\n", len);
	n = (p->width <= len ? 0 : p->width - len);
	c = ' ';
	if (n)
	{
		if (p->flag & F_MINU)
		{
//			post = ft_fill_with(c, n);
			pre = ft_fill_with(c, n);		// is better but i hate it...
			*str = ft_fstrjoin(str, &pre);
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
		++len;
	}
//	printf("len at end: %zu\n", len);

	*str = ft_fstrjoin(str, &post);		// 2 of these is too many
	*str = ft_fstrjoin(&pre, str);

	return (len + n);
}

