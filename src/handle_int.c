/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:56:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 21:41:19 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


		// Needs to be made shorter
		// Remove the few remaining redundancies, like in ft_cast's ?
		// Change ft_cast's ???
		// Get the binary print size to depend on size, ie int vs long or
		// whatever


#include "printf.h"

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

	// This file is gonna need some work...






long long				ft_cast_d(va_list ap, t_param *p)		// works for %d and %i
{
	long long	num;

	if (p->size & C_H)
		num = va_arg(ap, int);	// short
	else if (p->size & C_HH)
		num = va_arg(ap, int);	// signed char
	else if (p->size & C_L)
		num = va_arg(ap, long int);
	else if (p->size & C_LL)
		num = va_arg(ap, long long int);
	else if (p->size & C_J)
		num = va_arg(ap, intmax_t);
	else if (p->size & C_Z)
		num = va_arg(ap, size_t);
	else
		num = va_arg(ap, int);
	return (num);
}

unsigned long long		ft_cast_u(va_list ap, t_param *p)		// works for %uoxX
{
	unsigned long long	num;

	if (p->size & C_H)
		num = va_arg(ap, int);	// unsigned short	// make it unsigned instead ?
	else if (p->size & C_HH)
		num = va_arg(ap, int);	// unsigned char
	else if (p->size & C_L)
		num = va_arg(ap, unsigned long);
	else if (p->size & C_LL)
		num = va_arg(ap, unsigned long long);		// will this work ???	may need to split handle int...
	else if (p->size & C_J)
		num = va_arg(ap, uintmax_t);
	else if (p->size & C_Z)
		num = va_arg(ap, size_t);
	else
		num = va_arg(ap, unsigned int);
	return (num);
}

int						ft_handle_uint(va_list ap, char **str, t_param *p)
{
	unsigned long	num;
	size_t				len;
	char				*tmp;


//	num = ULLONG_MAX;

//	printf("num: %llu\n", num);

	tmp = NULL;
	len = 0;
	num = 1;				// did not help at all...
	if (p->spec == 'u')
	{
		num = ft_cast_u(ap, p);

//		printf("num: %llu\n", num);		

		tmp = ft_pos_itoa(num);
//		printf("tmp: %s\n", tmp);
		len = ft_fstrlen(tmp);
	}
	else if (p->spec == 'x' || p->spec == 'X')
	{
//		printf("OG num: %lu\n", num);
//		if (num < 0)
//			num = 4294967295 + num + 1;

		num = ft_cast_u(ap, p);
		if (p->spec == 'x')
			tmp = ft_any_base_convert(num, "0123456789abcdef");
		else
			tmp = ft_any_base_convert(num, "0123456789ABCDEF");

//		printf("OG: tmp |%s|\n", tmp);
		
		len = ft_fstrlen(tmp);
//		printf("its a hex, tmp: |%s|\n", tmp);
	}
	else if (p->spec == 'o')		// unsigned ocatal
	{
		num = ft_cast_u(ap, p);
		tmp = ft_any_base_convert(num, "01234567");
		len = ft_fstrlen(tmp);
	}
	if (num == 0)
		p->flag |= (1 << 7);

	*str = ft_gen_arg_str_i(p, &tmp, len, 0);
	return (ft_fstrlen(*str));
}

int					ft_handle_int(va_list ap, char **str, t_param *p)
{
	char		*tmp;
	char		*base;
	long long	num;
	size_t		len;
	int			neg;

	tmp = NULL;
	base = NULL;
	len = 0;

	num = 0;		// necessary ???
	neg = 0;

//	printf("handle int test 1\n");	

	if (p->spec == 'd' || p->spec == 'i')
	{
		num = ft_cast_d(ap, p);
		if (num == 0)
			p->flag |= (1 << 7);
		if (num < 0)
		{
			neg = -1;
			num = -num;		// is it a problem for long long max or min ???
		}
		tmp = ft_pos_itoa(num);
		len = ft_fstrlen(tmp) - neg;
//		printf("handle int test 2 its an int\n");
	}
	else if (p->spec == 'b' || p->spec == 'B')
	{
		if (p->spec == 'B')
			base = ft_fstrdup(va_arg(ap, char*));	// can not free post, not sure why, ok so can't free because its a arg passed to func, so don't worry, just set to NULL...
		else if (p->spec == 'b')	// binary
			base = ft_fstrdup("01");
		num = ft_cast_d(ap, p);
		if (!(tmp = ft_any_base_convert(num, base)))		// should do this more and securiser in parse_buffer too
			return (-1);
		len = ft_fstrlen(tmp);
		if (p->spec == 'B')
			free(base);			// do this better ????
		base = NULL;
	}

//	printf("handle int test 3\n");

	if (neg < 0)		// if it's neg same as if flag + so set to 1
		p->flag |= (1 << 2);

//	printf("handle int tmp: |%s|\n", tmp);

	*str = ft_gen_arg_str_i(p, &tmp, len, neg);
	return (ft_fstrlen(*str));
}


		// Gonna need to be shorter

char				*ft_gen_arg_str_i(t_param *p, char **tmp, size_t len, int neg)
{
	char	c;
	int		plen;
	int		wlen;
	char	*pre;
	char	*mid;
	char	*post;

	pre = NULL;
	mid = NULL;
	post = NULL;

//	printf("width: %zu, prec: %zu\n", p->width, p->precision);

//	printf("tmp: |%s|\n", *tmp);


	if (p->flag & F_NULL && p->flag & F_PREC && p->precision == 0)
	{
		if (*tmp)
			ft_scott_free(tmp);
		*tmp = ft_fstrdup("");
		len = 0;
	}

	plen = (p->precision <= (len + neg) ? 0 : p->precision - (len + neg));
	wlen = (p->width <= len ? 0 : p->width - len);
	if (plen)
		pre = ft_fill_with('0', plen);
	if (p->flag & F_HASH)
	{
		if (p->spec == 'x')
			mid = ft_fstrdup("0x");
		else if (p->spec == 'X')
			mid = ft_fstrdup("0x");
		else if (p->spec == 'o')
			mid = ft_fstrdup("0");
		if (mid)
			pre = ft_fstrjoin(&mid, &pre);
	}
	if (wlen > plen)
	{
		c = ' ';
		if (p->flag & F_ZERO && !(p->flag & F_MINU) && !(p->flag & F_PREC))
			c = '0';
		post = ft_fill_with(c, wlen - plen);
		if (!(p->flag & F_MINU))
		{
			if (c != '0' && p->flag & F_PLUS)
			{
				mid = neg < 0 ? ft_fstrdup("-") : ft_fstrdup("+");
				pre = ft_fstrjoin(&mid, &pre);
				p->flag &= (0 << 2);
			}
			pre = ft_fstrjoin(&post, &pre);
		}
	}
	if (p->flag & F_PLUS)
	{
		mid = neg < 0 ? ft_fstrdup("-") : ft_fstrdup("+");
		pre = ft_fstrjoin(&mid, &pre);
	}
	if (p->flag & F_SPAC && wlen <= plen)
	{
		mid = ft_fstrdup(" ");
		pre = ft_fstrjoin(&mid, &pre);
	}
	pre = ft_fstrjoin(&pre, tmp);
	pre = ft_fstrjoin(&pre, &post);

//	printf("gen arg str: |%s|\n", str);
	return (pre);		//ret tmp instead ???
//	return (ft_fstrjoin(ft_fstrjoin(pre, tmp), post));
}

