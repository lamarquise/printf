/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:33:24 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/25 19:18:55 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

// Parse_buffer.c takes after a % and figures out where to send shit and 
// returns whatever


//static void		ft_function_factory(void)


	// returns the number of char that have been read

int		ft_field_parsing(char *format, va_list ap, char **tmp)
{
	int		ret;
	int		i;
	t_param	p;

	i = 0;
	ret = 0;
	
	p.flag = 0;
	p.width = 0;
	p.precision = 0;
	
	// check for %

	printf("pre flag parsing: format; [%c]\n", *format);

	if (format[ret] != '%')
		return (-1);
	++ret;		// maybe not this if do ++format...		// or maybe i do apparently


	ret += ft_flag_parsing(&format[ret], &p, ap);	// use ret to move *format?

//	printf("post flag parsing: format; [%c]\n", *format);


	// add some security ???
	p.spec = format[ret];

	
	i = ft_findchar("diuxXbBcspn%", format[ret]);

	printf("field parsing i: %d\n", i);

	if (i <= 6)						// or using defines ???? I guess i just need to make my own thing as some point....
		i = ft_handle_int(ap, tmp, &p);
	else if (i <= 8)
		i = ft_handle_str(ap, tmp, &p);
	else if (i == 10)
		i = ft_handle_pointer(ap, tmp, &p);
//	else if (i == 9)
		// handle nothing	// more complicated than i thought...
	else if (i == 11)
		i = ft_handle_modulo(tmp, &p);
	else
		i = -1;
//	printf("field parsing test end\n");

	printf("parse buff i %d\n", i);
//	printf("parse buff ret: %d\n", (i == -1) ? -1 : i + ret);

	return ((i == -1) ? -1 : i + ret);
}

