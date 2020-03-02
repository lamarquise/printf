/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:56:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/02 21:28:15 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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










long long				ft_cast_d(long long num, t_param *p)		// works for %d and %i
{
	if (p->size & C_H)
		num = (short)num;
	else if (p->size & C_HH)
		num = (signed char)num;
	else if (p->size & C_L)
		num = (long)num;
	else if (p->size & C_LL)
		num = (long long)num;
	else if (p->size & C_J)
		num = (intmax_t)num;
	else if (p->size & C_Z)
		num = (size_t)num;
	else
		num = (int)num;
	return (num);
}

unsigned long long		ft_cast_u(unsigned long long num, t_param *p)		// works for %uoxX
{
	if (p->size & C_H)
		num = (unsigned short)num;
	else if (p->size & C_HH)
		num = (unsigned char)num;
	else if (p->size & C_L)
		num = (unsigned long)num;
	else if (p->size & C_LL)
		num = (unsigned long long)num;		// will this work ???	may need to split handle int...
	else if (p->size & C_J)
		num = (uintmax_t)num;
	else if (p->size & C_Z)
		num = (size_t)num;
	else
		num = (unsigned int)num;
	return (num);
}

int						ft_handle_uint(va_list ap, char **str, t_param *p)
{
	unsigned long long	num;
	size_t				len;
	char				*tmp;


	tmp = NULL;
	len = 0;
	if (p->spec == 'u')
	{
		num = va_arg(ap, unsigned long long);		// not num, dif var ???
		num = ft_cast_u(num, p);
		tmp = ft_itoa(num);
		len = ft_fstrlen(tmp);
	}
	else if (p->spec == 'x' || p->spec == 'X')
	{
		num = va_arg(ap, unsigned long long);		// will this work...
		num = ft_cast_u(num, p);
//		printf("is a hex, num: %d\n", num);
		if (p->spec == 'x')
			tmp = ft_any_base_convert((long)num, "0123456789abcdef");
		else
			tmp = ft_any_base_convert((long)num, "0123456789ABCDEF");
		len = ft_fstrlen(tmp);
//		printf("its a hex, tmp: |%s|\n", tmp);
	}
	else if (p->spec == 'o')		// unsigned ocatal
	{
		num = va_arg(ap, unsigned long long);
		num = ft_cast_u(num, p);
		tmp = ft_any_base_convert((long)num, "01234567");		// more than a long ???
		len = ft_fstrlen(tmp);
	}

	str = ft_gen_arg_str(p, &tmp, len, 0);
	return (ft_fstrlen(*str));
}

int					ft_handle_int(va_list ap, char **str, t_param *p)
{
	char		*tmp;
	char		*base;
	long long	num;		// just make it a long long ???? size_t ????
	size_t		len;
	int			neg;

	tmp = NULL;
	base = NULL;
	len = 0;

	num = 0;
	neg = 0;

//	printf("handle int test 1\n");	

	if (p->spec == 'd' || p->spec == 'i')
	{
		num = va_arg(ap, long long);
		num = ft_cast_d(num, p);		// do the va_arg in the cast func ????
		if (num < 0)
		{
			neg = -1;
			num = - num;
		}
		tmp = ft_itoa(num);		// special itoa ???		litoa ????

		len = ft_fstrlen(tmp) - neg;
//		printf("handle int test 2 its an int\n");
	}
	else if (p->spec == 'b' || p->spec == 'B')
	{
		if (p->spec == 'B')
			base = va_arg(ap, char*);	// can not free post, not sure why, ok so can't free because its a arg passed to func, so don't worry, just set to NULL...
		else if (p->spec == 'b')	// binary
			base = ft_strdup("01");
		num = va_arg(ap, long long);		// not an int ????
		num = ft_cast_d(num, p);
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

/*	if (p->flag & F_PREC && p->precision == 0)
	{
		tmp = ft_strdup("");
		len = 0;
	}
*/
//	printf("handle int tmp: |%s|\n", tmp);

	str = ft_gen_arg_str(p, &tmp, len, neg);
	return (ft_fstrlen(*str));
}


char				**ft_gen_arg_str(t_param *p, char **tmp, size_t len, int neg)
{
	char	c;
	int		plen;
	int		wlen;
	char	**pre;
	char	**post;

	pre = malloc(sizeof(char*));
	post = malloc(sizeof(char*));

	if (p->flag & F_PREC && p->precision == 0)
	{
		*tmp = ft_strdup("");
		len = 0;
	}



	plen = (p->precision <= (len + neg) ? 0 : p->precision - (len + neg));
	wlen = (p->width <= len ? 0 : p->width - len);
	if (plen)
		*pre = ft_fill_with('0', plen);
	if (p->flag & F_HASH)
	{
		if (p->spec == 'x')
			pre = ft_fstrjoin(ft_fstrdup("0x", 2), pre);
		else if (p->spec == 'X')
			pre = ft_fstrjoin(ft_fstrdup("0x", 2), pre);
		else if (p->spec == 'o')
			pre = ft_fstrjoin(ft_fstrdup("0", 1), pre);
	}
	if (wlen > plen)
	{
		c = ' ';
		if (p->flag & F_ZERO && !(p->flag & F_MINU) && !(p->flag & F_PREC))
			c = '0';
		*post = ft_fill_with(c, wlen - plen);
		if (!(p->flag & F_MINU))
		{
			if (c != '0' && p->flag & F_PLUS)
			{
				pre = ft_fstrjoin(neg < 0 ? ft_fstrdup("-", 1) : ft_fstrdup("+", 1), pre);
				p->flag &= (0 << 2);
			}
			pre = ft_fstrjoin(post, pre);
//			ft_scott_free(&post);
		}
	}
	if (p->flag & F_PLUS)
		pre = ft_fstrjoin(neg < 0 ? ft_fstrdup("-", 1) : ft_fstrdup("+", 1), pre);
	if (p->flag & F_SPAC && wlen <= plen)
		pre = ft_fstrjoin(ft_fstrdup(" ", 1), pre);

	char	**str;

	str = ft_fstrjoin(ft_fstrjoin(pre, tmp), post);

//	printf("gen arg str: |%s|\n", str);

	return (str);


//	return (ft_fstrjoin(ft_fstrjoin(pre, tmp), post));
}

