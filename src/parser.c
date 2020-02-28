/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/28 19:10:06 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

// Parse.c cuts format around %'s and puts resutls in a linked list


	// can add fd arg if necessary
	// goes through format sending sections with % or not to dif places

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
	while (format[i])		// while (*format) ????
	{
//		printf("hq loop start test\n");
		if ((m = ft_findchar(&format[c], '%')) != -1)		// NO idea if my math is right ????
		{
			i += m;
//			printf("hq spec test 1, i = %d, c = %d\n", i, c);
			if (!(str = ft_memalloc(sizeof(char) * (i - c + 1))))
				return (-9);
			ft_memcpy(str, &format[c], i - c);
			if (!pflist_append(lst, ft_buf_to_elem(str)))
				return (-2);
//			printf("hq spec test 2\n");

			ft_scott_free(&str);
					// might want to check that ret isn't like -1, and if so stop all...
			if ((c = ft_field_parsing(&format[i], ap, &str)) == -1)		// returns the length of % and stuff thats been read.
			{
//				printf("field error\n");
				return (-3);
			}
//			printf("HQ spec 3, c: %d\n", c);
			i += c;
			c = i;

//			printf("HQ spec 3.5, i: %d\n", i);

			if (!pflist_append(lst, ft_buf_to_elem(str)))
			{
//				printf("append error\n");
				return (-4);
			}
			ft_scott_free(&str);
//			printf("HQ spec 4, i: %d, c: %d\n", i, c);
		
		}
		else
		{
//			printf("HQ no Spec, c: %d\n", c);
			i = ft_fstrlen(format);
			if (!(str = ft_memalloc(sizeof(char) * (i - c + 1))))		// not + 1????
				return (-5);
			str = ft_memcpy(str, &format[c], i - c);			// hopefully this math is right...
			if (!pflist_append(lst, ft_buf_to_elem(str)))
				return (-6);
			ft_scott_free(&str);
		}
	}
//	printf("end of hq\n");
	return (1);		// something better ????
}


