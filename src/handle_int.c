/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:56:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/28 19:11:02 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"


	// This file is gonna need some work...


	// need to figure out how to get + or - to be joined to front of 0s if
	// there are any but not before spaces

	// also, same as for handle_str()
	// need to get precision == 0 working, and prolly also if a null sent...


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
	long long	num;		// just make it a long long ???? size_t ????
	size_t		len;
	size_t		wlen;
	size_t		plen;
	size_t		i;

	int			neg;

	tmp = NULL;
	pre = NULL;
	post = NULL;
	len = 0;		// usefull ???

	i = 0;
	num = 0;

	neg = 0;

//	printf("handle int test 1\n");


	
	


	if (p->spec == 'd' || p->spec == 'i')	// regular ints i think
	{
		num = va_arg(ap, int);		// may need to change this to cast as not an int if l or ll or h or ....	// same for all following....

		if (num < 0)
		{
			neg = -1;
			num = - num;
		}
		tmp = ft_itoa(num);		// special itoa ???

		len = ft_fstrlen(tmp) - neg;
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
	else if (p->spec == 'b' || p->spec == 'B')		// add binary here ???		// could put in seperate file ???
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

//	printf("handle int test 3\n");

	if (neg < 0)		// if it's neg same as if flag + so set to 1
		p->flag |= (1 << 2);// is 4 equivalent to (1 << 3) ?????? no idea, but i hope so...


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


	wlen = (p->width <= len ? 0 : p->width - len);


		// precision does not take + or - into acount
	plen = (p->precision <= (len + neg) ? 0 : p->precision - (len + neg));


	// how to adapt this middle out system to other specs, like the unsigned ones ???? 

	if (plen)
		pre = ft_fill_with('0', plen);
	if (p->flag & F_HASH)
	{
		if (p->spec == 'x')
			pre = ft_fstrjoin("0x", pre);
		else if (p->spec == 'X')
			pre = ft_fstrjoin("0X", pre);
		else if (p->spec == 'o')
			pre = ft_fstrjoin("0", pre);
	}
	if (p->flag & F_PLUS)	// was 4 theres a + or its negative
	{
		pre = ft_fstrjoin(neg < 0 ? "-" : "+", pre);
	}

	// if width and prec but width bigger than prec, we do spaces then 0s
	// but if no prec then only 0s if '0' flag...

	if (wlen > plen)	// if - then ignor 0 meaning will put spaces on right, else puts 0s on left
	{
//		printf("wlen > plen\n");
		c = ' ';
		if (p->flag & F_ZERO && !(p->flag & F_MINU) && !(p->flag & F_PREC))
			c = '0';
		post = ft_fill_with(c, wlen - plen - i);
		if (!(p->flag & F_MINU))
		{
			pre = ft_fstrjoin(post, pre);
			ft_scott_free(&post);
		}
	}
	else if (p->flag & F_SPAC)
	{
		pre = ft_fstrjoin(" ", pre);
	}

//	printf("handle int: pre |%s|, tmp |%s|, post |%s|\n", pre, tmp, post);
	
	*str = ft_fstrjoin(ft_fstrjoin(pre, tmp), post);

//	printf("handle int test 4, str: |%s|\n", *str);

	return (1);
}


