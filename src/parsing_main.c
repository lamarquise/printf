/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 15:54:18 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// double check securities and frees

// The algorythm: go through format, if find % deal with str before, then deal
// with %, if no % deal with everything after the most recent %


#include "printf.h"

	// Does work but is it the best/most elegant solution ?
	// might as well use i cuz clear
	// can i send fewer vars?
	// return **lst ? maybe...

int			ft_listify_not_spec(int i, int c, char *format, t_pfelem **lst)
{
	char	*str;

	str = NULL;
	if (!format)	// check for i - c here ?
		return (-1);		// good place for an error handling func
	if (!(str = ft_memalloc(sizeof(char) * (i - c + 1))))
		return (-2);
	ft_memcpy(str, &format[c], i - c);
	if (!ft_pflist_append(lst, ft_str_to_elem(str, i - c)))
		return (ft_scott_free(&str));
	ft_scott_free(&str);
	return (1);
}

	// ideally get rid of str and m...
int     	ft_parsing_hq(char *format, va_list *ap, t_pfelem **lst)
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
		if ((m = ft_findchar(&format[c], '%')) != -1)
		{
			i += m;
			if (m > 0 && !ft_listify_not_spec(i, c, format, lst))
					return (ft_scott_free(&str));	// does str even exist here?
			if ((c = ft_spec_parsing(&format[i], ap, &str, &m)) <= -1)	// get rid of -1?
				return (ft_scott_free(&str));
			i += c;							// can not use m here, is that a good idea?

				// if this fails, free str and pflist
			if (ft_pflist_append(lst, ft_str_to_elem(str, m)) == -1) // -1 necessary
//			if (ft_pflist_append(lst, NULL) == -1)	// testing error cases.
				return (ft_scott_free(&str));
			c = i;
//			printf("test1\n");
//			ft_print_lst(lst);
			ft_scott_free(&str);
		}
		else
			return (ft_listify_not_spec(ft_fstrlen(format), c, format, lst));
	}
//	printf("end of hq\n");
	return (1);		// amount that has been read ???
}
