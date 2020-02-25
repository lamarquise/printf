/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:56:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/25 19:18:44 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
something		ft_size_stuff()
{


	va_arg(ap, int);
	va_arg(ap, long);
	va_arg(ap, long long);
	va_arg(ap, short);
	va_arg(ap, short short);
	va_arg(ap, size_t);		// zu is that what that is ?????
	


}
*/

void			ft_scott_free(char **str)
{
	ft_bzero(*str, ft_fstrlen(*str));
	free(*str);
	*str = NULL;
}

int				ft_handle_int(va_list ap, char **str, t_param *p)
{
	char		*tmp;
	char		*pre;
	char		*post;
	char		c;
	long		num;		// just make it a long long ???? size_t ????
	size_t		len;
	size_t		wlen;
	size_t		plen;
	size_t		i;

	tmp = NULL;
	pre = NULL;
	post = NULL;
	len = 0;		// usefull ???

	i = 0;
	num = 0;


	printf("handle int test 1\n");

		// diuUxX		// possibly also oO other things too ????	better way of doing this ????

	if (p->spec == 'd' || p->spec == 'i')	// regular ints i think
	{
		num = va_arg(ap, int);		// may need to change this to cast as not an int if l or ll or h or ....	// same for all following....
		tmp = ft_itoa(num);		// special itoa ???

		len = ft_fstrlen(tmp);
//		printf("handle int test 2 its an int\n");

	}
	else if (p->spec == 'u')		// could manage this by storring if there is a majuscule or nah with bitwise or something
	{				// this is basically the same as 'd' or 'i', use a func table to get same result without all ifs ????
		num = va_arg(ap, unsigned int);		// not num, dif var ???
		tmp = ft_itoa(num);
		len = ft_fstrlen(tmp);
	}
	else if (p->spec == 'x' || p->spec == 'X')		// do a thing where i standardize x and X to just x but remember if it's maj, same for u and U ???
//		(ft_strchr(p->spec, "xX") != NULL)		// kick ass idea
	{
		num = va_arg(ap, int);
//		printf("is a hex, num: %d\n", num);
		if (p->spec == 'x')
			tmp = ft_any_base_convert((long)num, "0123456789abcdef");
		else
			tmp = ft_any_base_convert((long)num, "0123456789ABCDEF");
		len = ft_fstrlen(tmp);
//		printf("its a hex, tmp: |%s|\n", tmp);
	}
	else if (p->spec == 'b')
	{
		post = va_arg(ap, char*);	// can not free post, not sure why, ok so can't free because its a arg passed to func, so don't worry, just set to NULL...
		num = va_arg(ap, int);
		if (!(tmp = ft_any_base_convert(num, post)))		// should do this more and securiser in parse_buffer too
			return (-1);
		len = ft_fstrlen(tmp);
		post = NULL;
	}
	else if (p->spec == 'o')		// unsigned ocatal
	{
		num = va_arg(ap, int);
		tmp = ft_any_base_convert((long)num, "01234567");
		len = ft_fstrlen(tmp);
	}

	printf("handle int test 3\n");

	if (num < 0)		// if it's neg same as if flag + so set to 1
		p->flag |= 4;		// ????		// is 4 equivalent to (1 << 3) ?????? no idea, but i hope so...


	// "0#+- .123456789*hljz"
	
	// Precision: pads with '0's on right, unaffected by '-', takes precedent over width.	// 0s added on left never right of num unless a float ???
	// Width: pads with ' 's on right, OR '0's if '0' flag, OR left justify with ' '  not '0' if '-'

	// signs + or - do not count in precision but do count in width...
	// 0x of # does not count in precision but does in width...


	// FLag options:
	// '-' left justify
	// '0' zeros not spaces			// ignored if there is a -
	// ' ' a space sometimes ???
	// '+' sign in front of ints
	// '#' 0x in front of hex numbers



//	printf("width: %zu, precision: %zu\n", p->width, p->precision);

	wlen = (p->width <= len ? 0 : p->width - len);
	plen = (p->precision <= len ? 0 : p->precision - len);

//	printf("wlen: %zu, plen: %zu\n", wlen, plen);

		// #				// + but only if not neg ???		// space but only sometimes ??? also will hex work ???
	i = (p->flag & 2) /* * 2 + (p->flag & 4) + (p->flag & 0x10)*/ /*+ 1*/;	// more things that add ????

	printf("the mysterious i: %zu\n", i);

	// i is all the things that are counted by width but not by precision...

	// how to adapt this middle out system to other specs, like the unsigned ones ???? 

	if (plen)		// adding 0s from precision
		pre = ft_fill_with('0', plen);		// could make this a sep func so that can take into acount if a num is a float or whatever....
	if (p->flag & 3)	// thers a # so add 0x
	{
		if (p->spec == 'x')
			pre = ft_fstrjoin("0x", pre);
		else if (p->spec == 'X')
			pre = ft_fstrjoin("0X", pre);
		else if (p->spec == 'o')
			pre = ft_fstrjoin("0", pre);
	}
	if (p->flag & 4)	// theres a + or its negative		// has to be before the - one		// adding a sign
	{
//		pre = ft_fstrjoin((num < 0 ? '-' : '+'), pre);
	}
	if (wlen > plen)	// if - then ignor 0 meaning will put spaces on right, else puts 0s on left
	{
		printf("wlen > plen\n");
		c = ' ';
		if (p->flag & 1 && !(p->flag & 7))	// theres a 0 and theres no -
			c = '0';
		post = ft_fill_with(c, wlen - plen - i);
		if (!(p->flag & 7))    // there is not a -
		{
			pre = ft_fstrjoin(post, pre);
			ft_scott_free(&post);
			//bzero post and free it ???
		}
	}
	else if (p->flag & 0x10)
	{
		pre = ft_fstrjoin(" ", pre);
	}

	printf("handle int: pre |%s|, tmp |%s|, post |%s|\n", pre, tmp, post);
	
	*str = ft_fstrjoin(ft_fstrjoin(pre, tmp), post);

	printf("handle int test 4, str: |%s|\n", *str);

	return (1);			// better ret ????
}


	// kinda like a strjoin		// appends a char
char		*ft_add_char(char **str, char c)				//void		ft_add_char(char **str, char c)
{
	char	*tmp;
	int		i;

//	printf("made it to add char 1, str: |%s|, len: %zu\n", *str, ft_fstrlen(*str));
	tmp = NULL;
	if ((!str || !*str) && !c)
		return (NULL);					// use other strlen ???
	if (!(tmp = malloc(sizeof(char) * (ft_fstrlen(*str) + 2))))
		return (NULL);
	i = 0;
//	printf("made it to add char 2, str: |%s|\n", *str);
	tmp[i] = c;
	while (*str && (*str)[i])
	{
//		printf("while in add char\n");
		tmp[i + 1] = (*str)[i];
		++i;
	}
//	printf("made it to add char 3\n");
	tmp[i + 1] = '\0';
	if (str && *str)
	{
//		printf("freeing in add char, tmp: |%s|\n", tmp);
		ft_bzero(*str, ft_fstrlen(*str));
		free(*str);
	}
//	*str = tmp;
	return (tmp);
}

int			ft_base_check(char *base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])		// more conditions ???????
				return (0);
			++j;
		}
		++i;
	}
//	printf("base check 1\n");
	return (1);
}
						// more than a long ???			// should work ????
char		*ft_any_base_convert(long nb, char *base)
{
	int		i;
	int		size;
	char	*ret;
//	char	*tmp;

	i = 0;
	ret = NULL;
	size = ft_strlen(base);
	if (!ft_base_check(base))
		return (NULL);
	while (nb >= size)
	{
//		printf("ret in base conv: |%s|\n", ret);
		ret = ft_add_char(&ret, base[nb % size]);
//		printf("ret in base 2\n");
		nb /= size;
//		ft_bzero(ret, ft_fstrlen(ret));
//		free(ret);
//		ret = tmp;
	}
	ret = ft_add_char(&ret, base[nb % size]);		// do i need to do it one last time...
	printf("base convert, ret: |%s|\n", ret);
	return (ret);
}

/*

void		ft_hex_base_convert(long nb, char **ret, t_param *p)
{
	char	s[2];
	// fill in with the other crap ....

	printf("base convert, nb: [%ld]\n", nb);

	ft_bzero(s, 2);
	if (nb >= 16)
		ft_hex_base_convert(nb / 16, ret, p);
	s[0] = base[nb % 16];
	*ret = ft_fstrjoin(*ret, s);
}
*/


/*

int			ft_base_setup(t_param *p)		// more elaborate params if decide it can be many dif bases... send the string, the size, etc...
{
	
									// could do size here
//	if (!(p->base = malloc(sizeof(char) * (16 + 1))))
//		return (-1);
//	p->base = B_16;		// im not sure that will work....

	

	// OR
				// could do size
	static char		b[16] = B_16;
	p->base = &b;					// would that even work ???

	return (0);
}


	// can i globally define the base ?
//static char		base[16] = "0123456789abcdef";

				// ret a double pointer ????
				// does it get an int ????

	// returns a string to be shoved into pfelem
int			ft_handle_int(va_list ap, t_buf *buf, t_param *p)
{
	char 	*tmp;
	long	nb;// use a long long ??? or whatever the larest is ???
	int		neg;
	int		a;


	// need to call va_list to recover the number...

	// split into signed vs unsigned, why not...

	// 



//	what is it?
//	recover it
//	prefix now ?
//	base changes now ?
//	handle width and precision



	






	a = 0;	// necessary?
	if (a = ft_findchar("uUxX", p->spec) >= 0)	// all are unsigned
		






	tmp = NULL;
	neg = 1;

//	printf("handle int test 1\n");

	buf->content = ft_itoa(va_arg(ap, int));	// start with a long to be safe ????
	printf("is buf a string? [%s]\n", buf->content);
	if (p->type == 'x')
	{
		nb = ft_atoi(buf->content);
		if (nb < 0)
		{
			neg = -1;
			nb = -nb;
		}
		ft_hint_base_convert(nb, &tmp,  p);
		free(buf->content); 	// do that ????
		if (neg < 0)
			buf->content = ft_strjoin("-", tmp);
//		printf("tmp in hex: [%s]\n", tmp);
		else
			buf->content = tmp;
	}

	if (p->prefix[0])	// shove the " " into a new elem ???
	{
		tmp = ft_strjoin(" ", buf->content);	// is it an int ???
		buf->content = tmp;
		// there have to be leaks ....
	}

	// will have to do some other things to handle param stuff...

	return(1);
}

*/





