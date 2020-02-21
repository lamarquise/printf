/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:05:43 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/21 19:04:26 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"


		// we want it to handle either strings or chars...

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
		if (!(tmp = malloc(sizeof(char) * 1)))
			return (-1);
		*tmp = (char)va_arg(ap, int);	// correct casting ???		will it work for the whiles ???? // has to be an int for some reason....
		len = 1;
//		printf("tmp: %c\n", *tmp);
	}
	else if (p->spec == 's')
	{
		tmp =  va_arg(ap, char*);
		len = ft_strlen(tmp);
	}


//	printf("handle str test 2, tmp: %s\n", tmp);

	// check width then others...
	// '-' left justify with width. - is 3rd pos
	// '0' no left justify adds 0s with width.	0 is 0th pos 

	wlen = (p->width <= len ? 0 : p->width - len);	// now it's the number of spaces or 0s....

//	printf("wlen: %zu\n", wlen);

	if (!(*str = malloc(sizeof(char) * (wlen + len + 1))))
		return (0);


	i = 0;
//	if (wlen > 0)		// theres extra width...
//	{
//		printf("made it into there is a width\n");
		if (wlen && p->flag & 7)	// correct syntax ???	// theres a -		// & 7 ???
		{
			while (*tmp)
				(*str)[i] = *tmp++;
			while (i < wlen + len)
				(*str)[i++] = ' ';
			(*str)[i] = '\0';
		}
		else if (wlen && p->flag & 1)		// theres a 0		// this did not work at all lol 
		{
//			printf("made it into there is a 0\n");
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
//			printf("wlen and str: |%s|\n", *str);
		}
//	}
/*	else
	{
		while (*tmp)
			(*str)[i++] = *tmp++;
		(*str)[i] = '\0';
	}
*/

//	printf("handle str test 3, str: %s\n", *str);

		// I assume all that will work for c and for wlen = 0...

	return (1);		// 1 ????	i think yes 1 unless have a lL or hH or that shit
}



/*


	// eventually move this to another file
	// just for char * for now
char	*ft_salloc(size_t len, char fill)
{
	char	*ret;
	int		i;

	if (len < 1)		// other conditions ???
		return (NULL);
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len + 1] = '\0';
	ft_memset(ret, fill, len);
	return (ret);
}	// string alloc



	// eventually add spec struct to args...

int			ft_handle_str(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	char	*pre;
	char	*post;
	int		len;

	tmp = NULL;
	// OR
//	tmp = va_arg(ap, char*);	take both and sort out later... ?

	if (p->type == 'c')
	{
		// do the char thing
		*tmp = va_arg(ap, char);
		len = 1;
//			p->width > 1 ? p->width : 1;	// i think, there might be a
	}										// special case for 0
	else
	{
		// string
		tmp = va_arg(ap, char*);
		while (tmp[len])
			++len;
//		len = p->width > len ? p->width : len;
	}
	// now what ???

	if (p->width > len)		// i think, but low key no idea need to test
	{
		len = p->width - len;		// use calloc ??? could actually be dope
				// make my own function that allocates and fills but null 
				// terminates
		
		if ((p->flag & 7) == 1)
		{
			// len spaces after string
			post = ft_salloc(len, ' ');		//secure ???
		}
		else if ((p->flag & 1) == 1)
		{
			// len 0's before string
			pre = ft_salloc(len, '0');
		}
		else
		{
			// len spaces before string
			pre = ft_salloc(len, ' ');
		}

	}

	if ((p->flag & 1) == 1)		// means there is a 0 ???
								// if width and no -
	if ((p->flag & 7) == 1)		// there is a -		// most important
	if ((p->flag & 15) == 1)	// there is a space	// only applies if 
								// width too small
						// wait no, it's irrelevant ???

	// precision is meaningless to strings

	// is width bigger
	// if yes, by how much
	// is there a 0
	// is there a -


	// 0's only if before not if - flag, otherwise spaces	


	// use p->type which is the int, to do shit, a generic function that could be applied to all handles would be nice...

	// need to create what comes before and what comes after...


		// OR i write a func that takes 3 param and smashes them together, also frees them ???
	*str = ft_str(ft_strjoin(pre, tmp), post);



	buf->content = va_arg(ap, char*);
	// same as handle int need more conditions as progress

	if (param->prefix[0])
	{		// use new gnl version of join ???
		tmp = ft_strjoin(" ", buf->content);
//		free(buf->content);
		buf->content = tmp;
	}

	return (1);
}


*/

