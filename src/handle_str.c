/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:05:43 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/02 21:33:23 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// seems to do the right things but needs to be shorter. more concise ?

#include "printf.h"

int				ft_handle_str(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	size_t	len;
	size_t	plen;
	size_t	wlen;

	char	c;
	char	*pre;
	char	*post;

//	printf("handle str test 1\n");

	pre = NULL;
	post = NULL;
	tmp = NULL;
	len = 0;
	plen = 0;
	wlen = 0;


	if (p->spec == 'c')		// actually way more complicated, may need to handle
	{						// printing the int value with \x00 or whatever
//		printf("found a c\n");
		if (!(tmp = ft_memalloc(sizeof(char) * 2)))
			return (-1);
		tmp[0] = (char)va_arg(ap, int);	// seems to work
//		tmp[1] = '\0';	// useful ???
		len = 1;
//		printf("tmp: %c\n", *tmp);
	}
	else if (p->spec == 's')
	{
		tmp = ft_fstrdup(va_arg(ap, char*));
		len = ft_fstrlen(tmp);
	}

	if (!tmp)
	{
		tmp = ft_fstrdup("(null)");
		p->flag |= (1 << 7);	// after width
		len = 6;	// ???		// seems good i guess...

//		return (1);
	}
//	printf("test 2\n");



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

//	if (p->flag & F_NULL)
//		wlen = p->width;
//	else
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

//	printf("pre: |%s|, post: |%s|\n", pre, post);

//	printf("handle str test 3, str: |%s| size: %zu\n", *str, len);

//	printf("len: %zu\n", len);

	return (len);		// ????
}
