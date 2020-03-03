/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 15:43:10 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

	// this will have to be shorter...

int     	ft_hq(char *format, va_list ap, t_pfelem **lst)
{
	int			i;
	int			c;
	int			m;
	char		*str;

	i = 0;
	c = 0;
	m = 0;
	str = NULL;
//	printf("hq test 1\n");
	while (format[i])
	{
//		printf("hq loop start test\n");
		if ((m = ft_findchar(&format[c], '%')) != -1)	// get around using m ????
		{
//			printf("HQ modulo found, i: %d, c: %d, m: %d\n", i, c, m);
			i += m;
			if (m > 0)
			{
//				printf("hq spec test 1, i = %d, c = %d\n", i, c);
				if (!(str = ft_memalloc(sizeof(char) * (i - c + 1))))
					return (-2);
				ft_memcpy(str, &format[c], i - c);
				if (!ft_pflist_append(lst, ft_buf_to_elem(str, i - c)))
					return (ft_scott_free(&str));
//				printf("hq spec test 2\n");
				ft_scott_free(&str);
			}
			if ((c = ft_field_parsing(&format[i], ap, &str, &m)) == -1)
				return (ft_scott_free(&str));
			i += c;
//			printf("HQ spec 3,str: |%s|\n", str);
//			printf("HQ spec 3,c: %d i: %d\n", c, i);
			if (!ft_pflist_append(lst, ft_buf_to_elem(str, m)))
				return (ft_scott_free(&str));
			c = i;
			ft_scott_free(&str);
//			printf("HQ end spec 4, i: %d, c: %d\n", i, c);
		}
		else
		{
//			printf("HQ no Spec, c: %d\n", c);
			i = ft_fstrlen(format);
			if (!(str = ft_memalloc(sizeof(char) * (i - c + 1))))
				return (-3);
			if (!ft_pflist_append(lst, ft_buf_to_elem(ft_memcpy(str, &format[c], i - c), i - c)))
				return (ft_scott_free(&str));
			ft_scott_free(&str);
		}
	}
//	printf("end of hq\n");
	return (1);		// amount that has been read ???
}
