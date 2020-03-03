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

	// seems to do the right things but needs to be shorter. more concise ?

#include "printf.h"

int				ft_handle_char(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	size_t	len;
	size_t	plen;
	size_t	wlen;

	tmp = NULL;
	len = 0;
	plen = 0;
	if (p->spec == 'c')
	{
		if (!(tmp = ft_memalloc(sizeof(char) * 2)))
			return (-1);
		tmp[0] = (char)va_arg(ap, int);
		len = 1;
	}
	if (p->flag & F_PREC && p->precision == 0)
	{
		if (tmp)
			ft_scott_free(&tmp);
		tmp = ft_fstrdup("");		// see solution below...
		len = 0;
	}
	wlen = (p->width <= len ? 0 : p->width - len);
	if (wlen)
	{
		if (p->flag & F_MINU)
		{
			plen = wlen;
			wlen = 0;
		}
	}
	else if (p->flag & F_SPAC)
		wlen = 1;
	*str = ft_fill_with(' ', len + wlen + plen);
	if (len)
		(*str)[wlen] = tmp[0];
	if (tmp)
		free(tmp);
	if (!*str)
		return (-1);
	return (len + wlen + plen);
}

int				ft_handle_str(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	size_t	len;

//	printf("handle str test 1\n");
	tmp = NULL;
	len = 0;
	if (p->spec == 's')
	{
		tmp = ft_fstrdup(va_arg(ap, char*));
		len = ft_fstrlen(tmp);
	}

	if (!tmp)
	{
//		printf("test: tmp |%s|\n", tmp);
		tmp = ft_fstrdup("(null)");
		p->flag |= (1 << 7);	// after width
		len = 6;	// ???		// seems good i guess...

//		return (1);
	}
//	printf("test 2\n");

/*
	if (p->flag & F_PREC)
	{
		if (p->precision == 0)
		{
			ft_scott_free(&tmp);
			tmp = ft_fstrdup("");	// was *str...
			len = 0;
//			return (1);
		}
		else if ((plen = (p->precision < len ? p->precision : 0)) > 0)
		{
//			ft_scott_free(&tmp);
			pre = ft_substr(tmp, 0, plen);
			ft_scott_free(&tmp);
			tmp = pre;
			pre = NULL;
			len = plen;
		}
		// free things ????
	}

*/

//	if (p->flag & F_NULL)
//		wlen = p->width;
//	else


/*
	wlen = (p->width <= len ? 0 : p->width - len);

	c = ' ';
	if (wlen)
	{
		if (p->flag & F_MINU)
			post = ft_fill_with(c, wlen);
		else
		{
			if (p->flag & F_ZERO)
				c = '0';
			pre = ft_fill_with(c, wlen);
		}
	}
	else if (p->flag & F_SPAC)
		pre = ft_fill_with(c, 1);

	*str = ft_fstrjoin(&tmp, &post);
	
//	printf("handle str test 2, str: |%s|\n", *str);

	*str = ft_fstrjoin(&pre, str);

	

	len += wlen;
*/
//	printf("pre: |%s|, post: |%s|\n", pre, post);

//	printf("handle str test 3, str: |%s| size: %zu\n", *str, len);

//	printf("len: %zu\n", len);

	*str = ft_gen_arg_str_s(p, &tmp, len);

//	printf("crusial str: |%s|\n", *str);

	return (ft_fstrlen(*str));		// not len += wlen ????
}

char			*ft_gen_arg_str_s(t_param *p, char **tmp, size_t len)
{
	char	c;
	int		plen;
	int		wlen;
	char	*pre;
	char	*post;

	pre = NULL;
	post = NULL;
	if (p->flag & F_PREC)
	{
		if (p->precision == 0)
		{
			if (*tmp)		// ok so i need to make it an empty string but also free it...
				free(*tmp);
//				ft_scott_free(tmp);
//			*tmp = NULL;
			*tmp = ft_fstrdup("");		// no idea if this is correct ???	// seems like it would be tho...		// causes a seg fault and a leak ????
//			if (*tmp)
//				printf("there is something in tmp: |%s|\n", *tmp);
			len = 0;
		}
		else if ((plen = (p->precision < len ? p->precision : 0)) > 0)
		{
			pre = ft_substr(*tmp, 0, plen);
			ft_scott_free(tmp);
			*tmp = pre;
			pre = NULL;
			len = plen;
		}
		// free things ????
	}
	wlen = (p->width <= len ? 0 : p->width - len);
	c = ' ';
	if (wlen)
	{
		if (p->flag & F_MINU)
			post = ft_fill_with(c, wlen);
		else
		{
			if (p->flag & F_ZERO)						// is this possible ????
				c = '0';
			pre = ft_fill_with(c, wlen);
		}
	}
	else if (p->flag & F_SPAC)
		pre = ft_fill_with(c, 1);

	post = ft_fstrjoin(tmp, &post);
	post = ft_fstrjoin(&pre, &post);

//	len += wlen;


	return (post);
}

