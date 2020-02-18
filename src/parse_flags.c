/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:25:48 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/18 18:47:41 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

							// use a **format ???
int			ft_flag_parsing(char **format, t_param *p, va_list ap)
{
	int		i;

	i = 0;
		// what the fuck does & do ???
		// secure around format not being over ???

	// " ' " needs to go in here somewhere....

	while (i = ft_findchar("0#+- .123456789*hljz", **format) >= 0)
	{
		if (i <= 4)		// wait doesnt this prevent 0 from being used later ?
		{
			p->type |= (1 << i);		// also fucking clever.... this or the HEX defines ???? need both ???
			++*format;

			// something to do with bitwise
		}
		else if (i == 5)	// also store . in p->type, might as well
		{
			/* *format += */ft_get_precision(format, p, ap);
		}
		else if (i <= 15)	// cuz numbers and 0
		{	// perhaps we get 0 after other digits in the func we call ?
			// get width
			
			/* *format += */ft_get_width(format, p, ap);
		}
		else
		{
			// handle size hHlL that shit...
		}
	}


	return (0); // what do i return ????
}


	// do these need to ret ints ???
							// may not need double * for format ????
int			ft_get_precision(char **format, t_param *p, va_list ap)
{
	int		tmp;

	++*format;
	if (**format == '*')
	{
		tmp = va_arg(ap, int);
		p->precision = tmp < 0 ? 0 : tmp;
		p->flag |= tmp < 0 ? 0 : 256;	// could use a define for 256, isnt
		++*format;	// will that remain in 
	}									// that 1000 ??? in binary
	else
	{		// i don't want to copy everything but he used a special atoi
		p->precision = (tmp = ft_atoi(*format)) < 0 ? 0 : tmp;
							// atoi or a loop? this is a bit savage...
		while (*format >= '0' && *format <= '9')
			++*format;	// or count and ret number...
		p->flag |= (1 << 5);	// is the 5th space free ???
	}
	//check for * or loop through format while a digit


	return (0); // what do i return 
}


int			ft_get_width(char **format, t_param *p, va_list ap)
{
	int		tmp;
	
	// also check for * or loop

	if (**format == '*')
	{
		tmp = va_arg(ap, int);
		p->width = tmp < 0 ? 0 : tmp;
		p->flag |= tmp < 0 ? 0 : 128;	// or not 128 ???
		++*format;	// will this work ???
	}
	else if (**format >= '1' && **format <= '9')
	{
		p->width = (tmp = ft_atoi(*format)) < 0 ? 0 : tmp;
		while (*format >= '0' && *format <= '9')
			++*format;
		p->flag |= (1 << 6);
	}
	
	return (0);
}

/*

int			ft_get_size()
{
	// somehow manage the hHlL shit
}

*/




