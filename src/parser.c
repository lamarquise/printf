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

	// Needs to be shorter
	// double check securities and frees

#include "printf.h"

/*
int			ft_found_spec()
{



}
*/
	// Does work but is it the best/most elegant solution ?
	// might as well use i cuz clear

int			ft_listify_not_spec(int i, int c, char *format, t_pfelem **lst)
{
	char	*str;

	str = NULL;
	if (!format) /*|| (i - c == 0))*/	// check for i - c here ?
		return (-1);		// good place for an error handling func
	if (!(str = ft_memalloc(sizeof(char) * (i - c + 1))))
		return (-2);
	ft_memcpy(str, &format[c], i - c);
	if (!ft_pflist_append(lst, ft_buf_to_elem(str, i - c)))
		return (ft_scott_free(&str));
//	printf("hq spec test 2\n");
	ft_scott_free(&str);
	return (1);
}

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
			i += m;
//			printf("test some %%, i=%d\n", i);
			if (m > 0)
			{
				if (!ft_listify_not_spec(i, c, format, lst))
					return (ft_scott_free(&str));
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
			return (ft_listify_not_spec(ft_fstrlen(format), c, format, lst));
	}
//	printf("end of hq\n");
	return (1);		// amount that has been read ???
}
