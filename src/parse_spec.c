/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec.c                                       :+:      :+:    :+:   */
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

	// really need a return ???
int		ft_init_param(t_param *p)
{
	p->flag = 0;
	p->width = 0;
	p->precision = 0;
	p->size = 0;
	p->spec = '\0';
	return (1);
}

	// does it even need a return ?

int		ft_pick_handler(va_list *ap, char **str, t_param *p, int *m)
{
	if (*m <= 2)
		*m = ft_handle_int(ap, str, p);
	else if (*m <= 7)
		*m = ft_handle_uint(ap, str, p);
	else if (*m <= 8)
		*m = ft_handle_char(ap, str, p);
	else if (*m <= 9)
		*m = ft_handle_str(ap, str, p);
	else if (*m == 10)
		*m = ft_handle_pointer(ap, str, p);
	else if (*m == 11)		// assuming no flags, is that correct ????
	{
		*str = ft_strdup("");
		*m = 1;
	}
/*	else if (*m == 12)
	{
		*str = va_arg(ap, void*);
	}
*/	else if (*m == 13)
		*m = ft_handle_modulo(str, p);
	// do i need an else here? as a catch all ?


	return (1);		// how to use this better?
					// could ret m ?
}

	// You need m to be sent cuz it returns len of str

int		ft_spec_parsing(char *format, va_list *ap, char **str, int *m)
{
	int		ret;
	t_param	p;

	*m = 0;
	ret = 0;
	ft_init_param(&p);
	if (format[ret++] != '%')
		return (-1);
	if ((ret += ft_flag_parsing(&format[ret], &p, ap)) <= -1)
		return (-2);		// this only works cuz ret if error is much bigger than -1
	if ((*m = ft_findchar("diBbuoxXcspNn%", format[ret])) < 0)
		return (-3);		// can do this better i bet
	p.spec = format[ret];

	if (!ft_pick_handler(ap, str, &p, m))	// can also do this better...
		return (-4);

//	printf("field parsing test end\n");

//	printf("parse buff n= %d, ret=%d, str:|%s|\n", *m, ret, *str);
//	printf("parse buff ret: %d\n", (n == -1) ? -1 : n + ret);
	return ((*m <= -1) ? -4 : 1 + ret);
}

