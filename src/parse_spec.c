/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:33:24 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 19:07:32 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


	// needs to be much shorter...
	// fix %n or is it %N

#include "printf.h"

int		ft_init_param(t_param *p)	// secure
{
	if (!p)
		return (-1);
	p->flag = 0;
	p->width = 0;
	p->precision = 0;
	p->size = 0;
	p->spec = '\0';
	return (1);
}

	// does it even need a return ?

	// in theory m is only -1 if error

int		ft_pick_handler(va_list *ap, char **str, t_param *p, int *m)
{
	if (!ap || !str || !p || !m)
		return (-1);
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
	else if (*m == 11)	// %N	//prints # char counted
	{
		if (ft_nstrdup(str, "") == -1)	// test error case
			return (-1);
		*m = -2;
	}
	else if (*m == 12)	// %n	// # up to char passed to pointer
	{
		if (!(*str = ft_pos_itoa(va_arg(*ap, long))))	// test error case
			return (-1);
		*m = -3;
	}
	else if (*m == 13)
		*m = ft_handle_modulo(str, p);
	// do i need an else here? as a catch all ?
	if (*m == -1)
		return (-1);
	return (1);		// don't ret m, no need
}

	// You need m to be sent cuz it returns len of str

int		ft_spec_parsing(char *format, va_list *ap, char **str, int *m)
{
	int		ret;
	t_param	p;

	if (!format || !ap || !str || !m)
		return (-1);
	*m = 0;
	ret = 0;
	if (ft_init_param(&p) == -1)
		return (-2);
	if (format[ret++] != '%')
		return (-3);
	if ((ret += ft_flag_parsing(&format[ret], &p, ap)) <= -1)
		return (-4);
	if ((*m = ft_findchar("diBbuoxXcspNn%", format[ret])) < 0)
		return (-5);
	p.spec = format[ret];
	if (ft_pick_handler(ap, str, &p, m) == -1)
		return (-6);
	return ((*m == -1) ? -7 : 1 + ret);
}

