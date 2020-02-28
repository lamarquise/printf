/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/27 19:02:01 by erlazo           ###   ########.fr       */
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
	char		*str;

	i = 0;
	c = 0;
	str = NULL;
//	printf("hq test 1\n");
	while (format[i])		// while (*format) ????
	{
//		printf("hq test 2\n");
		if ((i += ft_findchar(&format[c], '%')) != -1)		// NO idea if my math is right ????
		{
			printf("hq spec test 1, i = %d, c = %d\n", i, c);

			// i is the pos of %

			if (!(str = ft_memalloc(sizeof(char) * (i - c + 1))))
				return (-9);

			ft_bzero(str, i - c + 1);	// i don't love this
		
			str = ft_memcpy(str, &format[c], i - c);
			if (!pflist_append(lst, ft_buf_to_elem(str)))
				return (-2);
//			printf("hq spec test 2, str: %s\n", str);

			ft_scott_free(&str);
//			ft_bzero(str, ft_strlen(str));	// is all this necessary ????
//			free(str);
//			str = NULL;
			
					// might want to check that ret isn't like -1, and if so stop all...
			if (!(c = ft_field_parsing(&format[i], ap, &str)))		// returns the length of % and stuff thats been read.
			{
				printf("field error\n");
				return (-3);
			}
			printf("HQ spec 3, c: %d\n", c);
			i += c;
			c = i;

			printf("HQ spec 3.5, i: %d\n", i);

//			printf("format: %c\n", *format);
//			printf("hq spec test 3, str: %s\n", str);

			if (!pflist_append(lst, ft_buf_to_elem(str)))
			{
				printf("append error\n");
				return (-4);
			}
//			printf("hq spec test 4, str: %s\n", str);
//			printf("str: |%s|\n", str);
//			printf("format: |%c|\n", format[i]);
	
			// ft_bzero str shit here too ????

			ft_bzero(str, ft_strlen(str));
			free(str);
			str = NULL;

			printf("HQ spec 4, i: %d, c: %d\n", i, c);
		
		}
		else
		{
			printf("HQ no Spec\n");
			i = ft_strlen(format);		// do - c here so only use i ???						// can all this stuff be compressed ????
			if (!(str = ft_memalloc(sizeof(char) * (i - c + 1))))		// not + 1????
				return (-5);
			ft_bzero(str, i - c + 1);
			str = ft_memcpy(str, &format[c], i - c);			// hopefully this math is right...
			if (!pflist_append(/*&buf->*/lst, ft_buf_to_elem(str)))
				return (-6);
//			printf("hq no spec test 1, str: %s\n", str);

			// bzero here ???

		}
	}
	printf("end of hq\n");
	return (1);		// something better ????
}


