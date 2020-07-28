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

#include "printf.h"

int			ft_flag_parsing(char *format, t_param *p, va_list *ap) // secure
{
	int		i;
	int		prev;
	int		ret;

	if (!format || !p || !ap)
		return (-8);
	i = 0;
	prev = 0;
	ret = 0;
	while ((i = ft_findchar("0#+- .123456789*hljz", format[ret])) >= 0)
	{
		if ((prev >= 5 && (i < 5 && i > 0)) || (prev >= 16 && i < 16)) // move to bot
			return (-8);								// if necessary... (# of lines)
		if (i <= 4 && ++ret) // this is cheap
			p->flag |= (1 << i);
		else if (i == 5)
			ret += ft_get_precision(&format[ret], p, ap);
		else if (i <= 15)
			ret += ft_get_width(&format[ret], p, ap);
		else
			ret += ft_get_size(&format[ret], p);
		if (ret < 1)
			return (-8);
		prev = i;
	}
	return (ret);
}

int			ft_get_precision(char *format, t_param *p, va_list *ap)	// secure
{
	int		psize;	// precision size
	int		rlen;	// read length

	if (!format || !p || !ap)
		return (-10);
	rlen = 0;
	if (format[rlen++] != '.')
		return (-10);
	if (format[rlen] == '*')
	{
		psize = va_arg(*ap, int);
		++rlen;
	}
	else if ((rlen += ft_latoi(&format[rlen], &psize)) <= -1)
		return (-10);
	if (psize < 0)		// if neg i ignore ???
		psize = 0;
	else
		p->flag |= (1 << 5);	
	p->precision = psize;
//	printf("pprec: %zu, rlen:%d, p->flag & PREC: %#x\n", p->precision, rlen, p->flag);
	return (rlen);
}

int			ft_get_width(char *format, t_param *p, va_list *ap) // secure
{
	int		wsize;	// width size
	int		rlen;	// read length

	if (!format || !p || !ap)
		return (-10);
	rlen = 0;
	wsize = 0;
	if (format[rlen] == '*')
	{
		wsize = va_arg(*ap, int);
		++rlen;
	}
	else if (format[rlen] >= '1' && format[rlen] <= '9'
			&& (rlen += ft_latoi(&format[rlen], &wsize)) <= -1) //fine if goes wrong
		return (-10);
	if (wsize < 0)
	{
		wsize = -wsize;
		p->flag |= (1 << 3);
	}
	p->width = wsize;
//	printf("pwidth: %zu, rlen:%d\n", p->width, rlen);
	p->flag |= (1 << 6);
	return (rlen);
}
	// make so can't have multiple size flags ?
int			ft_get_size(char *format, t_param *p)	// secure
{
	int		ret;
	int		i;

	if (!format || !p)
		return (-10);
	ret = 0;
	while ((i = ft_findchar("hlzj", format[ret])) >= 0)
	{
		if (i < 2)
		{
			if (p->size & (i * 3 + 1))
			{
				p->size &= (0 << (i * 2));
				p->size |= (1 << (i * 2 + 1));
			}
			else
				p->size |= ((1 << i * 2));
		}
		else
			p->size |= (1 << (i + 2));
		++ret;
	}
	return (ret); 
}
