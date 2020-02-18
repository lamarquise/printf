/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/18 18:32:39 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

// Parse.c cuts format around %'s and puts resutls in a linked list


	// can add fd arg if necessary
	// goes through format sending sections with % or not to dif places

int     	ft_hq(char *format, va_list ap, t_buf *buf)
{
	int			i;
	int			c;
	char		*tmp;
//	char		*buf;
	t_pfelem	*new;

	i = 0;
	c = 0;
	tmp = NULL;
	new = NULL;

//	new = new_pfelem(NULL, 0, 0, NULL);
	printf("hq test 1\n");
//	buf->cursor = 0;
//	ft_bzero(buf->content, BUFF_SIZE);





		// could use a ft_findchar here, as in look for '%'...
		// OR
		// if it aint broke don't fix it ??? may be too much trouble....
		// cuz at that point could also do 


	while (format[i])		// totally forgot but i need to do cursor too...
	{						// the cursor is i, I think...
//		printf("hq test 2\n");
//		if (format[i] != '%' && c < BUFF_SIZE)
		if (format[i] != '%')
		{
			++i;
			++c;
//			buf->content[c++] = format[i++];
		}
		else
		{		// i think i don't need c - 1...
			printf("hq spec test 1\n");
			if (!(tmp = ft_memalloc(sizeof(char) * (c + 1))))
				return (0);
			tmp = ft_memcpy(tmp, &format[i - c], c);
			if (!pflist_append(&buf->lst, ft_buf_to_elem(tmp)))
				return (0);
	//		printf("hq spec test 2\n");
//			buf->cursor += i;		// may not be super useful ???
	//		printf("tmp: [%s]\n", tmp);

			ft_bzero(tmp, ft_strlen(tmp));	// may not be necessary
			free(tmp);
			tmp = NULL;		// causes a segfault ???
			
	//		printf("bad tmp 1: [%s]\n", tmp);
//			ft_bzero(buf->content, BUFF_SIZE);
			c = 0;
			i += ft_field_parsing(&format[i], ap, &tmp);

	//		printf("bad tmp 2: [%s]\n", tmp);
	//		printf("hq buf content: [%s]\n", buf->content);
	//		printf("hq spec test 3\n");

			if (!pflist_append(&buf->lst, ft_buf_to_elem(tmp)))
				return (0);
	//		printf("hq spec test 4\n");
//			buf->cursor += i;
	//		printf("bad tmp 3: [%s]\n", tmp);
//			ft_bzero(buf->content, BUFF_SIZE);
		}
//		printf("end of loop format char: %c\n", format[i]);
	}
	printf("hq out of loop\n");
//	printf("tmp: [%s]\n", tmp);
	if (c > 0)
	{
		if (!(tmp = ft_memalloc(sizeof(char) * (c + 1))))
			return (0);
		tmp = ft_memcpy(tmp, &format[i - c], c);
		if (!pflist_append(&buf->lst, ft_buf_to_elem(tmp)))
			return (0);
//		printf("list contents end of hq: [%s]\n", buf->lst->content);
		ft_bzero(tmp, ft_strlen(tmp));
		free(tmp);
		tmp = NULL;
		c = 0;
	}
	printf("end of hq\n");
	return (1);		// something better ????
}


