/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:56:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/26 16:57:24 by erlazo           ###   ########.fr       */
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
	else if (p->spec == 'b' || p->spec == 'B')		// add binary here ???
	{
		if (p->spec == 'b')
			post = va_arg(ap, char*);	// can not free post, not sure why, ok so can't free because its a arg passed to func, so don't worry, just set to NULL...
		else if (p->spec == 'B')	// binary
			post = ft_strdup("01");
		num = va_arg(ap, int);
		if (!(tmp = ft_any_base_convert(num, post)))		// should do this more and securiser in parse_buffer too
			return (-1);
		len = ft_fstrlen(tmp);
		if (p->spec == 'B')
			free(post);			// do this better ????
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

		// # was 2			// + but only if not neg ???		// space but only sometimes ??? also will hex work ???
	i = (p->flag & F_HASH) /* * 2 + (p->flag & 4) + (p->flag & 0x10)*/ /*+ 1*/;	// more things that add ????

	printf("the mysterious i: %zu\n", i);

	// i is all the things that are counted by width but not by precision...

	// how to adapt this middle out system to other specs, like the unsigned ones ???? 

	if (plen)		// adding 0s from precision
		pre = ft_fill_with('0', plen);		// could make this a sep func so that can take into acount if a num is a float or whatever....
	if (p->flag & F_HASH)	// was 3 thers a # so add 0x
	{
		if (p->spec == 'x')
			pre = ft_fstrjoin("0x", pre);
		else if (p->spec == 'X')
			pre = ft_fstrjoin("0X", pre);
		else if (p->spec == 'o')
			pre = ft_fstrjoin("0", pre);
	}
	if (p->flag & F_PLUS)	// was 4 theres a + or its negative		// has to be before the - one		// adding a sign
	{
//		pre = ft_fstrjoin((num < 0 ? '-' : '+'), pre);
	}
	if (wlen > plen)	// if - then ignor 0 meaning will put spaces on right, else puts 0s on left
	{
		printf("wlen > plen\n");
		c = ' ';
		if (p->flag & F_ZERO && !(p->flag & F_MINU))	// was 1 and 7theres a 0 and theres no -
			c = '0';
		post = ft_fill_with(c, wlen - plen - i);
		if (!(p->flag & F_MINU))    // there is not a -
		{
			pre = ft_fstrjoin(post, pre);
			ft_scott_free(&post);
			//bzero post and free it ???
		}
	}
	else if (p->flag & F_SPAC)
	{
		pre = ft_fstrjoin(" ", pre);
	}

	printf("handle int: pre |%s|, tmp |%s|, post |%s|\n", pre, tmp, post);
	
	*str = ft_fstrjoin(ft_fstrjoin(pre, tmp), post);

	printf("handle int test 4, str: |%s|\n", *str);

	return (1);			// better ret ????
}


