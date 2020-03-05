/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:33:24 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 21:41:15 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// needs to be much shorter...
	// fix %n or is it %N

#include "printf.h"

	// shorten... n ???

int		ft_field_parsing(char *format, va_list ap, char **str, int *i)
{
	int		ret;
	t_param	p;

	*i = 0;
	ret = 0;
	p.flag = 0;
	p.width = 0;
	p.precision = 0;
	p.size = 0;
	if (format[ret++] != '%')
		return (-1);
//	printf("field parsing\n");
	if ((*i = ft_flag_parsing(&format[ret], &p, ap)) == -1)
		return (-2);
	ret += *i;
	if ((*i = ft_findchar("dibBuoxXcspNn%", format[ret])) >= 0)
		p.spec = format[ret];
	else
		return (-3);
//	printf("field parsing i: %d\n", *i);
	if (*i <= 3)
		*i = ft_handle_int(ap, str, &p);
	else if (*i <= 7)
		*i = ft_handle_uint(ap, str, &p);
	else if (*i <= 8)
		*i = ft_handle_char(ap, str, &p);
	else if (*i <= 9)
		*i = ft_handle_str(ap, str, &p);
	else if (*i == 10)
		*i = ft_handle_pointer(ap, str, &p);
	else if (*i == 11)		// assuming no flags, is that correct ????
	{
		*str = ft_strdup("");
		*i = 1;
	}
/*	else if (*i == 12)
	{
		*str = va_arg(ap, void*);
	}
*/	else if (*i == 13)
		*i = ft_handle_modulo(str, &p);

//	printf("field parsing test end\n");

//	printf("parse buff i %d\n", i);
//	printf("parse buff ret: %d\n", (i == -1) ? -1 : i + ret);
	return ((*i <= -1) ? -4 : 1 + ret);
}

