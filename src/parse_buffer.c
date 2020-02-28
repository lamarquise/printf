/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:33:24 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/28 19:11:29 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

	// shorten... n ???

int		ft_field_parsing(char *format, va_list ap, char **tmp)
{
	int		ret;
	int		i;
	t_param	p;

	i = 0;
	ret = 0;
	
	p.flag = 0;		// else where ????
	p.width = 0;
	p.precision = 0;
	if (format[ret++] != '%')
		return (-1);

		// protect ????
	ret += ft_flag_parsing(&format[ret], &p, ap);
	
	if ((i = ft_findchar("diuoxXbBcspNn%", format[ret])) >= 0)
		p.spec = format[ret];
	else
		return (-1);

//	printf("field parsing i: %d\n", i);

	if (i <= 7)
		i = ft_handle_int(ap, tmp, &p);
	else if (i <= 9)
		i = ft_handle_str(ap, tmp, &p);
	else if (i == 10)
		i = ft_handle_pointer(ap, tmp, &p);
	else if (i == 11)		// assuming no flags, is that correct ????
	{
		*tmp = ft_strdup("");
		i = 1;
	}
/*	else if (i == 12)
	{
		*tmp = va_arg(ap, void*);
	}
*/	else if (i == 13)
		i = ft_handle_modulo(tmp, &p);

//	printf("field parsing test end\n");

//	printf("parse buff i %d\n", i);
//	printf("parse buff ret: %d\n", (i == -1) ? -1 : i + ret);

	return ((i == -1) ? -1 : i + ret);
}

