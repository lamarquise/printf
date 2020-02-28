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

	// shorten ??? switch to strjoin, ie middle out method ???

#include "printf.h"

int				ft_handle_str(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	size_t	len;
	size_t	wlen;
	size_t	i;

//	printf("handle str test 1\n");

	tmp = NULL;
	len = 0;
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
	wlen = (p->width <= len ? 0 : p->width - len);

//	printf("wlen: %zu\n", wlen);

	if (!(*str = ft_memalloc(sizeof(char) * (wlen + len + 1))))
		return (-1);

	// would be less efficient but more legible with a fstrjoin()...

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
//	printf("handle str test 3, str: %s\n", *str);

	return (1);
}
