/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:25:48 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/28 19:12:50 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// get size needs work, secure ???

#include "printf.h"

int			ft_flag_parsing(char *format, t_param *p, va_list ap)
{
	int		i;
	int		n;
	int		ret;

	i = 0;
	n = 0;
	ret = 0;
		// secure around format not being over ???

//	printf("flag parsing test 1\n");

	while ((i = ft_findchar("0#+- .123456789*hljz", format[ret])) >= 0)
	{
//		printf("is a flag parsing test 1, format: [%c]\n", format[ret]);

		if (i <= 4)
		{
//			printf("is a flag\n");
			p->flag |= (1 << i); // also fucking clever.... this or the HEX defines ???? need both ???
			++ret;
			
//			printf("flag parsing, i = %d\n", i);
		}
		else if (i == 5)
			n = ft_get_precision(&format[ret], p, ap);
		else if (i <= 15)	// cuz numbers and 0
			n = ft_get_width(&format[ret], p, ap);
		else
			n = ft_get_size(&format[ret], p);
		if (n > 0)
			ret += n;
		else
			return (-1);		// better way of doing this ????
	}

//	printf("flag parsing test 2, format: [%c]\n", format[ret]);

	return (ret);
}

int			ft_get_precision(char *format, t_param *p, va_list ap)
{
	int		tmp;
	int		ret;

//	printf("precision parsing test 1, format: |%c|\n", *format);

	ret = 0;
	if (format[ret++] != '.')
		return (-1);
	if (format[ret] == '*')
	{
		tmp = va_arg(ap, int);
		p->precision = tmp < 0 ? 0 : tmp;
		++ret;
	}
	else
		p->precision = (tmp = ft_latoi(&format[ret], &ret)) < 0 ? 0 : tmp;
//	printf("precision parsing test 2\n");
	return (ret);
}

int			ft_get_width(char *format, t_param *p, va_list ap)
{
	int		tmp;
	int		ret;
	
	ret = 0;
	if (format[ret] == '*')
	{
		tmp = va_arg(ap, int);
		p->width = tmp < 0 ? 0 : tmp;
		++ret;
	}
	else if (format[ret] >= '1' && format[ret] <= '9')
		p->width = (tmp = ft_latoi(&format[ret], &ret)) < 0 ? 0 : tmp;
	else
		return (-1);
	return (ret);
}


	// needs lots of work....

	// 1:l 2:ll 3:h 6:hh

int			ft_get_size(char *format, t_param *p)
{
	int		ret;
	int		i;


	// l is long, also wchar_t*
	// ll is long long
	// h is short int
	// hh is signed char
	// j is intmax_t
	// z is size_t


	ret = 0;
	while ((i = ft_findchar("hl", format[ret])) >= 0)
	{
		p->size += i;			// store in end of p->flag ????
		++ret;
	}
	return (ret); 
}






