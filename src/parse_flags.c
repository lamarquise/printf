/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:25:48 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/23 18:18:40 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

							// use a **format ???
int			ft_flag_parsing(char *format, t_param *p, va_list ap)
{
	int		i;
	int		n;
	int		ret;

	i = 0;
	n = 0;
	ret = 0;
		// what the fuck does & do ???
		// secure around format not being over ???

	// " ' " needs to go in here somewhere....


	printf("flag parsing test 1\n");


	while ((i = ft_findchar("0#+- .123456789*hljz", format[ret])) >= 0)
	{

//		printf("is a flag parsing test 1, format: [%c]\n", format[ret]);

		if (i <= 4)
		{
			printf("is a flag\n");
			p->flag |= (1 << i);		// also fucking clever.... this or the HEX defines ???? need both ???
			++ret;
			
			printf("flag parsing, i = %d\n", i);
		}
		else if (i == 5)
		{
			printf("flag parsing going to precision\n");
			ret += ft_get_precision(&format[ret], p, ap);
		}
		else if (i <= 15)	// cuz numbers and 0
		{	// perhaps we get 0 after other digits in the func we call ?
			// get width
		
			ret += ft_get_width(&format[ret], p, ap);
//			printf("width gotten, format: [%c]\n", **format);
		}
//		else
//		{
			// handle size hHlL that shit...
//		}
//		++n;
	}

	printf("flag parsing test 2, format: [%c]\n", format[ret]);

	return (ret); // what do i return ????
}


	// do these need to ret ints ???
							// may not need double * for format ????
int			ft_get_precision(char *format, t_param *p, va_list ap)
{
	int		tmp;
	int		ret;

	printf("precision parsing test 1, format: |%c|\n", *format);

	ret = 0;
	// double check that theres a . then ++
	++ret;
	++format;
	if (*format == '*')
	{
		printf("star precision 1\n");
		tmp = va_arg(ap, int);
		p->precision = tmp < 0 ? 0 : tmp;
		p->flag |= tmp < 0 ? 0 : 256;	// could use a define for 256, isnt
//		++format;	// will that remain in 
		++ret;
		printf("star precision 1\n");
	}									// that 1000 ??? in binary
	else
	{		// i don't want to copy everything but he used a special atoi
		p->precision = (tmp = ft_atoi(format)) < 0 ? 0 : tmp;
							// atoi or a loop? this is a bit savage...
		while (*format >= '0' && *format <= '9')
		{
			++ret;
			++format;	// or count and ret number...
		}
		p->flag |= (1 << 5);	// is the 5th space free ???
	}
	//check for * or loop through format while a digit

	printf("precision parsing test 2\n");

	return (ret); // what do i return 
}


int			ft_get_width(char *format, t_param *p, va_list ap)
{
	int		tmp;
	int		ret;
	
	ret = 0;
	// also check for * or loop

	printf("width parsing test 1, format: |%c|\n", *format);


	if (*format == '*')
	{
		printf("star width 1\n");
		tmp = va_arg(ap, int);
		p->width = tmp < 0 ? 0 : tmp;
//		p->flag |= tmp < 0 ? 0 : 128;	// or not 128 ???
//		++format;	// will this work ???
		++ret;
		printf("star width 2\n");
	}
	else if (*format >= '1' && *format <= '9')
	{
		p->width = (tmp = ft_atoi(format)) < 0 ? 0 : tmp;
		while (*format >= '0' && *format <= '9')
		{
			++ret;
			++format;
		}
		p->flag |= (1 << 6);
	}
	
//	printf("width parsing test 2, width = %zu\n", p->width);
//	printf("width parsing test 2, format: [%c]\n", **format);
	return (ret);
}

/*

int			ft_get_size()
{
	// somehow manage the hHlL shit
}

*/




