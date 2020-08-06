/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:56:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 19:07:30 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


		// Needs to be made shorter
		// Remove the few remaining redundancies, like in ft_cast's ?

#include "printf.h"

	// "0#+- .123456789*hljz"
	
	// Precision: pads with '0's on right, unaffected by '-', takes precedent over width.
	// 0s added on left never right of num unless a float ???
	// Width: pads with ' 's on right, OR '0's if '0' flag,
	// OR left justify with ' '  not '0' if '-'

	// signs + or - do not count in precision but do count in width...
	// 0x of # does not count in precision but does in width...


long long			ft_cast_d(va_list *ap, t_param *p)	// works for %d and %i
{
	if (p->size & C_H)
		return (va_arg(*ap, int));	// short
	else if (p->size & C_HH)
		return (va_arg(*ap, int));	// signed char
	else if (p->size & C_L)
		return (va_arg(*ap, long int));
	else if (p->size & C_LL)
		return (va_arg(*ap, long long int));
	else if (p->size & C_J)
		return (va_arg(*ap, intmax_t));
	else if (p->size & C_Z)
		return (va_arg(*ap, size_t));
	else
		return (va_arg(*ap, int));			// put the most common first ???
}

	// not secure ? i mean it just returns a number, how can it be secured?
	// technically insecure, I know how i could secure it, but seems worse,
	// and i check it like right before this appel...
unsigned long long	ft_cast_u(va_list *ap, t_param *p)		// works for %uoxX
{
	if (p->size & C_H)
		return (va_arg(*ap, int));	// unsigned short	// make it unsigned instead ?
	else if (p->size & C_HH)
		return (va_arg(*ap, int));	// unsigned char
	else if (p->size & C_L)
		return (va_arg(*ap, unsigned long));
	else if (p->size & C_LL)
		return (va_arg(*ap, unsigned long long));		// will this work ???	may need to split handle int...
	else if (p->size & C_J)
		return (va_arg(*ap, uintmax_t));
	else if (p->size & C_Z)
		return (va_arg(*ap, size_t));
	else
		return (va_arg(*ap, unsigned int));		// put the most common first ???
}

	// Str is secure till it gets to gen_arg, in gen_arg str needs to be freed if
	// anything fails
int					ft_handle_uint(va_list *ap, char **str, t_param *p)
{
	unsigned long	num;

	if (!ap || !str || !p)
		return (-1);
	if ((num = ft_cast_u(ap, p)) == 0 && p->flag & F_PREC
		&& p->precision == 0)
	{
		if (!(*str = ft_fstrdup("")))		// secure but ought to be done better
			return (-1);					// same below
	}
	else
	{
		if (p->spec == 'u' && !(*str = ft_pos_itoa(num)))// better way of doing that below ?
			return (-1);
		else if (p->spec == 'x' && !(*str = ft_any_base_convert(num, "0123456789abcdef")))
			return (-1);
		else if (p->spec == 'X' && !(*str = ft_any_base_convert(num, "0123456789ABCDEF")))
			return (-1);
		else if (p->spec == 'b' && !(*str = ft_any_base_convert(num, "01")))
			return (-1);
		else if (p->spec == 'o' && !(*str = ft_any_base_convert(num, "01234567")))
			return (-1);	// scott_free something???	// I don't think so...
	}
	*str = ft_gen_arg_str_i(p, str, ft_fstrlen(*str), 0);	// secure this shit
	return (ft_fstrlen(*str));
}

	// Secure except gen_arg ? like do it better
	// also same problem as unsigned, gen_arg needs to free str if anything goes awry

int					ft_handle_int(va_list *ap, char **str, t_param *p)
{
	char		*base;
	long long	num;
	int			neg;

	if (!ap || !str || !p)	// free str just in case ? i think no
		return (-1);
	base = NULL;
	neg = 0;
	if ((num = ft_cast_d(ap, p)) == 0 && p->flag & F_PREC && p->precision == 0)
	{
//		printf("test\n");
		if (!(*str = ft_fstrdup("")))
			return (-1);
	}
	else
	{
		if (num < 0)
		{
			p->flag |= (1 << 2);
			neg = -1;
			num = -num;		// is it a problem for long long max or min ??? seems like no
		}
		if ((p->spec == 'd' || p->spec == 'i') && !(*str = ft_pos_itoa(num)))
			return (-1);
		else if (p->spec == 'B' && !(*str = ft_any_base_convert(num, va_arg(*ap, char*))))
			return (-1);
	}
	if (!(*str = ft_gen_arg_str_i(p, str, ft_fstrlen(*str), neg)))	// len had - neg// secure now ?
		return (-1);		// is there a case where result is NULL correctly ????
	return (ft_fstrlen(*str));
}


		// Expect to be secure but test
	// also
		// free str if anything goes wrong

char				*ft_gen_arg_str_i(t_param *p, char **str, size_t len, int neg)
{
	char	*pre;

//	printf("str:|%s|\n", *str);

	pre = NULL;
	p->precision = (p->precision <= len ? 0 : p->precision - len);
	len += (p->flag & F_PLUS ? 1 : 0);
	p->width = (p->width <= len ? 0 : p->width - len);
	if (p->precision && !(pre = ft_fill_with('0', p->precision)))
		return ((char*)ft_scott_free(str, 0));
	if (p->flag & F_HASH && ft_add_hash(&pre, p) == -1)
		return ((char*)ft_scott_free(str, 0));
//	printf("pre:|%s|\n", pre);
	if (p->width > p->precision && (ft_h_int_wid(p, &pre, str, neg)) == -1)
		return ((char*)ft_scott_free(str, 0));
	if (p->flag & F_PLUS && !(pre = ft_cstrjoin((neg < 0 ? '-' : '+'), &pre)))
		return ((char*)ft_scott_free(str, 0));
	if (!(p->flag & F_PLUS) && p->flag & F_SPAC && p->width <= p->precision
		&& !(pre = ft_cstrjoin(' ', &pre)))
		return ((char*)ft_scott_free(str, 0));
	return (ft_fstrjoin(&pre, str));	// secures itself ?
}

