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


	// need to rename cuz there isn't a buffer any more...

	// needs to be much shorter...
	// fix %n or is it %N

#include "printf.h"

	// You need m to be sent cuz it returns len of str

int		ft_field_parsing(char *format, va_list ap, char **str, int *m)
{
	int		ret;
	t_param	p;

	*m = 0;
	ret = 0;
	p.flag = 0;			// do this stuff elsewhere ?
	p.width = 0;
	p.precision = 0;
	p.size = 0;
	if (format[ret++] != '%')
		return (-1);
//	printf("field parsing\n");
	if ((*m = ft_flag_parsing(&format[ret], &p, ap)) == -1)
		return (-2);
	ret += *m;
	if ((*m = ft_findchar("dibBuoxXcspNn%", format[ret])) >= 0)
		p.spec = format[ret];
	else
		return (-3);
//	printf("field parsing n: %d\n", n);
	if (*m <= 3)
		*m = ft_handle_int(ap, str, &p);
	else if (*m <= 7)
		*m = ft_handle_uint(ap, str, &p);
	else if (*m <= 8)
		*m = ft_handle_char(ap, str, &p);
	else if (*m <= 9)
		*m = ft_handle_str(ap, str, &p);
	else if (*m == 10)
		*m = ft_handle_pointer(ap, str, &p);
	else if (*m == 11)		// assuming no flags, is that correct ????
	{
		*str = ft_strdup("");
		*m = 1;
	}
/*	else if (n == 12)
	{
		*str = va_arg(ap, void*);
	}
*/	else if (*m == 13)
		*m = ft_handle_modulo(str, &p);
	// do i need an else here? as a catch all ?

//	printf("field parsing test end\n");

//	printf("parse buff n= %d, ret=%d, str:|%s|\n", *m, ret, *str);
//	printf("parse buff ret: %d\n", (n == -1) ? -1 : n + ret);
	return ((*m <= -1) ? -4 : 1 + ret);
}

