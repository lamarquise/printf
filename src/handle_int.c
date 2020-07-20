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
	
	// Precision: pads with '0's on right, unaffected by '-', takes precedent over width.
	// 0s added on left never right of num unless a float ???
	// Width: pads with ' 's on right, OR '0's if '0' flag,
	// OR left justify with ' '  not '0' if '-'

	// signs + or - do not count in precision but do count in width...
	// 0x of # does not count in precision but does in width...


	// FLag options:
	// '-' left justify
	// '0' zeros not spaces			// ignored if there is a -
	// ' ' a space sometimes ???
	// '+' sign in front of ints
	// '#' 0x in front of hex numbers

	// This file is gonna need some work...




	// I don't entirely understand why these cast funcs work...
	// That said, based on some tests they work gangbusters so...
	// However, do i need to keep num as a long long? i mean, seems a bit
	// inefficent... although easier to code...


long long				ft_cast_d(va_list *ap, t_param *p)		// works for %d and %i
{
	long long	num;			// redundant declaration ?
		// do i have these declared because i need to have long long explicitly ?
	if (p->size & C_H)
		num = va_arg(*ap, int);	// short
	else if (p->size & C_HH)
		num = va_arg(*ap, int);	// signed char
	else if (p->size & C_L)
		num = va_arg(*ap, long int);
	else if (p->size & C_LL)
		num = va_arg(*ap, long long int);
	else if (p->size & C_J)
		num = va_arg(*ap, intmax_t);
	else if (p->size & C_Z)
		num = va_arg(*ap, size_t);
	else
		num = va_arg(*ap, int);			// put the most common first ???
	return (num);
}

unsigned long long		ft_cast_u(va_list *ap, t_param *p)		// works for %uoxX
{
	unsigned long long	num;	// declaring here seems redundant...

	if (p->size & C_H)
		num = va_arg(*ap, int);	// unsigned short	// make it unsigned instead ?
	else if (p->size & C_HH)
		num = va_arg(*ap, int);	// unsigned char
	else if (p->size & C_L)
		num = va_arg(*ap, unsigned long);
	else if (p->size & C_LL)
		num = va_arg(*ap, unsigned long long);		// will this work ???	may need to split handle int...
	else if (p->size & C_J)
		num = va_arg(*ap, uintmax_t);
	else if (p->size & C_Z)
		num = va_arg(*ap, size_t);
	else
		num = va_arg(*ap, unsigned int);		// put the most common first ???
	return (num);
}

	// could send the base as a str to func so as to avoid the if forest
	// but i would just have it elsewhere so might as well have it here
	// where it works now, i think...

int						ft_handle_uint(va_list *ap, char **str, t_param *p)
{
	unsigned long	num;
	size_t			len;

	if ((num = ft_cast_u(ap, p)) == 0 && p->flag & F_PREC && p->precision == 0)
	{
		*str = ft_fstrdup("");
		len = 0;				// could get rid of but would be slightly less efficient
	}
	else
	{
		if (p->spec == 'u' && !(*str = ft_pos_itoa(num)))// better way of doing that below ?
			return (-2);
		else if (p->spec == 'x' && !(*str = ft_any_base_convert(num, "0123456789abcdef")))
			return (-2);
		else if (p->spec == 'X' && !(*str = ft_any_base_convert(num, "0123456789ABCDEF")))
			return (-2);
		else if (p->spec == 'b' && !(*str = ft_any_base_convert(num, "01")))
			return (-2);
		else if (p->spec == 'o' && !(*str = ft_any_base_convert(num, "01234567")))
			return (-2);	// scott_free something???
		len = ft_fstrlen(*str);
	}
	*str = ft_gen_arg_str_i(p, str, len, 0);	// secure this shit
	return (ft_fstrlen(*str));
}


	// need to make it so when fuck up the convert base % syntax it doesn't segfault

int					ft_handle_int(va_list *ap, char **str, t_param *p)
{
	char		*base;
	long long	num;
	size_t		len;
	int			neg;

	base = NULL;	// extrememly necessary, might not be necessary if i had 
	neg = 0;
	if ((num = ft_cast_d(ap, p)) == 0 && p->flag & F_PREC && p->precision == 0)
		*str = ft_fstrdup("");
	else
	{
		if (num < 0)
		{
			p->flag |= (1 << 2);
			neg = -1;
			num = -num;		// is it a problem for long long max or min ??? seems like no
		}
		if ((p->spec == 'd' || p->spec == 'i') && !(*str = ft_pos_itoa(num)))
			return (-2);
		else if (p->spec == 'B' && !(*str = ft_any_base_convert(num, va_arg(*ap, char*))))
			return (-2);
	}
	len = ft_fstrlen(*str) - neg;
	if (!(*str = ft_gen_arg_str_i(p, str, len, neg)))	// secure now ?
		return (-1);		// is there a case where result is NULL correctly ????
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

	plen = (p->precision <= (len + neg) ? 0 : p->precision - (len + neg));
	wlen = (p->width <= len ? 0 : p->width - len);
	if (plen)
		pre = ft_fill_with('0', plen);
	if (p->flag & F_HASH && !ft_add_hash(&pre, p))	// Handles Hash
		return (NULL);
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
		if (p->flag & F_SPAC)
			pre[0] = ' ';
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

//	*tmp = ft_triple_join(pre, *tmp, post);		// no cuz need another var or leaks...


//	printf("gen arg str: |%s|\n", str);
	return (pre);		//ret tmp instead ???
//	return (ft_fstrjoin(ft_fstrjoin(pre, tmp), post));
}

