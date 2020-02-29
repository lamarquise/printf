/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:05:43 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/28 19:23:16 by erlazo           ###   ########.fr       */
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
	size_t	i;

	char	c;
	char	*pre;
	char	*post;

//	printf("handle str test 1\n");

	pre = NULL;
	post = NULL;

	tmp = NULL;
	len = 0;
//	plen = 0;

//	if (p->precision == 0)
//		return (-1);		// should i maybe do this in parse flags ????



	if (p->spec == 'c')
	{
//		printf("found a c\n");
		if (!(tmp = ft_memalloc(sizeof(char) * 1)))
			return (-1);
		*tmp = (char)va_arg(ap, int);	// seems to work
		len = 1;
//		printf("tmp: %c\n", *tmp);
	}
	else if (p->spec == 's')
	{
		tmp = va_arg(ap, char*);
		len = ft_fstrlen(tmp);
	}

	if (!tmp)
	{
		tmp = ft_strdup("(null)");
		p->flag |= (1 << 7);	// after width
		len = 6;	// ???		// seems good i guess...

//		return (1);
	}
//	printf("test 2\n");



	if (p->flag & F_PREC)
	{
		if (p->precision == 0)
		{
//			ft_scott_free(&tmp);
			tmp = ft_strdup("");	// was *str...
			len = 0;
//			return (1);
		}	
		else if ((plen = (p->precision < len ? p->precision : 0)) > 0)
		{
			tmp = ft_substr(tmp, 0, plen);
			len = plen;
		}
		// free things ????
	}

//	if (p->flag & F_NULL)
//		wlen = p->width;
//	else
		wlen = (p->width <= len ? 0 : p->width - len);

//	printf("wlen: %zu\n", wlen);

//	if (!(*str = ft_memalloc(sizeof(char) * (wlen + len + 1))))
//		return (-1);

	// would be less efficient but more legible with a fstrjoin()...

	// trying the jopin way...


//	if (plen)	// ie not 0
//		tmp = ft_substr(tmp, 0, plen);		// that's it i think...

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
	{
		pre = ft_fill_with(c, 1);
	}

	*str = ft_fstrjoin(pre, ft_fstrjoin(tmp, post));
		// will need to manage freeing...

	i = 0;
/*

	i = 0;
//		printf("made it into there is a width\n");
	if (wlen && p->flag & F_MINU)
	{
		while (*tmp)
			(*str)[i] = *tmp++;
		while (i < wlen + len)
			(*str)[i++] = ' ';
		(*str)[i] = '\0';	
	}
	else if (wlen && p->flag & F_ZERO)
	{
//		printf("made it into there is a 0\n");
		while (i < wlen)
			(*str)[i++] = '0';
		while (i < wlen + len)
			(*str)[i++] = *tmp++;
		(*str)[i] = '\0';
	}
	else // width or no
	{
		while (i < wlen)
			(*str)[i++] = ' ';
		while (*tmp)
			(*str)[i++] = *tmp++;
		(*str)[i] = '\0';
//		printf("wlen and str: |%s|\n", *str);
	}
*/

//	printf("handle str test 3, str: %s\n", *str);

	return (1);
}
