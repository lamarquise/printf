/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:25:48 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/02 18:06:15 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// pretty close, like not much needs to be shortend
	// redundantly secure ???	

#include "printf.h"

	// break into 2 funcs ?
	// needs to be 2 lines shorter
int			ft_flag_parsing(char *format, t_param *p, va_list *ap)
{
	int		i;
	int		prev;
	int		n;
	int		ret;

	i = 0;
	prev = 0;
	ret = 0;
	while ((i = ft_findchar("0#+- .123456789*hljz", format[ret])) >= 0)
	{
		if ((prev >= 5 && (i < 5 && i > 0)) || (prev >= 16 && i < 16))
			return (-8);
		n = 0;
		if (i <= 4 && ++n == 1)		// this is cheap
			p->flag |= (1 << i);
		else if (i == 5)
			n = ft_get_precision(&format[ret], p, ap);
		else if (i <= 15)	// cuz numbers and 0
			n = ft_get_width(&format[ret], p, ap);
		else
			n = ft_get_size(&format[ret], p);
		if (n < 1)
			return (-8);
		ret += n;
		prev = i;
	}
	return (ret);
}

int			ft_get_precision(char *format, t_param *p, va_list *ap)
{
	int		tmp;
	int		ret;

	ret = 0;
	if (format[ret++] != '.')
		return (-1);
	if (format[ret] == '*')
	{
		tmp = va_arg(*ap, int);
		++ret;
	}
	else
		tmp = ft_latoi(&format[ret], &ret);		// don't think i need to worry about ret being dif if tmp is neg...
	if (tmp < 0)		// if neg i ignore ???
		tmp = 0;
	else
		p->flag |= (1 << 5);	
	p->precision = tmp;
	return (ret);
}

int			ft_get_width(char *format, t_param *p, va_list *ap)
{
	int		tmp;
	int		ret;

	ret = 0;
	if (format[ret] == '*')
	{
		tmp = va_arg(*ap, int);
		++ret;
	}
	else if (format[ret] >= '1' && format[ret] <= '9')
		tmp = ft_latoi(&format[ret], &ret);
	else
		return (-1);
	if (tmp < 0)
	{
		tmp = -tmp;
		p->flag |= (1 << 3);
	}
	p->width = tmp;
	p->flag |= (1 << 6);
	return (ret);
}

	// 1:l 2:ll 3:h 6:hh	// clever but didn't really do the doubling tthing

	// my solution is declare everything as long long, hten cast if necessary

	// Shorten ???
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

	// do i handle intmax? size_t?


	ret = 0;
	while ((i = ft_findchar("hlzj", format[ret])) >= 0)
	{
		if (i == 0)
		{
			if (p->size & C_H)
			{
				p->size &= (0 << 0);
				p->size |= (1 << 1);
			}
			else
				p->size |= (1 << 0);
//			++ret;
		}
		else if (i == 1)
		{
			if (p->size & C_L)
			{
				p->size &= (0 << 2);
				p->size |= (1 << 3);
			}
			else
				p->size |= (1 << 2);
//			++ret;		// why are these commented? why not necessary???
		}
		else if (i == 2)
			p->size |= (1 << 4);
		else if (i == 3)
			p->size |= (1 << 5);
		else
			return (-1);
		++ret;
	}
	return (ret); 
}






