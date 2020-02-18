/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:33:24 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/18 20:16:05 by erlazo           ###   ########.fr       */
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


	// check for %

	if (*format != '%')
		return (-1);
	++format;
	++ret;


	ft_flag_parsing(&format, &p, ap);	// use ret to move *format?

	// in theory params are set now, we know what the flags are...



	// check for 0	-> has to be first !!!
	// check for .	-> precition, either number of *
	// check for *	-> width
	// check for number -> width

	// if it's a * get size, then based off what had before either 
	// precition or width

	
	// check other flags after ????
	// - + # space %
	// or % is checked with specs...
	// does the pos of space make a dif relative to other flags ???
	// space should be checked first too


	// handle the printing of shit like vis a vis the dif btw width and prec
	// in this func, like after the number or whatever has been produced.


	p.spec = *format;

	// change all this, spec caller
	
	i = ft_findchar("diuUxXcspn%", *format);

	printf("field parsing i: %d\n", i);

	if (i <= 5)						// or using defines ???? I guess i just need to make my own thing as some point....
		// handle int
	else if (i <= 7)
		// handle string
	else if (i == 8)
		// handle pointer
	else if (i == 9)
		// handle nothing
	else if (i == 10)
		// handle %
	else
		// the thing where its not defined properly

	if (i == 6)
	{
		ret += ft_handle_int(ap, tmp, &p);
		// also handle int ????
	}	

/*	if (i == 8)
		ret += ft_handle_perc(ap, buf, &p);
*/
	if (i == 3)
		ret += ft_handle_int(ap, tmp, &p);

	if (i == 1)
		ret += ft_handle_str(ap, tmp, &p);

	// copy into buf->content ???
		// OR ret a str ???
//	ret += i;

	printf("field parsing test end\n");

	printf("ret %d\n", ret);

	return (ret);		// -1 if failure... ???
}

