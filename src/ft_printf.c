/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:29:04 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/27 19:02:04 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "printf.h"

/*

static t_ftc	g_ftable[127] = {NULL};

static void		ft_funcfactory(void)
{
	g_ftable['d'] = ft_handle_int;
	g_ftable['D'] = ft_handle_int;
	
	g_ftable['c'] = ft_handle_char;
	g_ftable['p'] = ft_handle_ptr;
	g_ftable['s'] = ft_handle_str;
	g_ftable['u'] = ft_handle_int;
	g_ftable['U'] = ft_handle_int;
	g_ftable['x'] = ft_handle_int;
	g_ftable['X'] = ft_handle_int;
	g_ftable['o'] = ft_handle_int;
	g_ftable['O'] = ft_handle_int;
//	g_ftable['d'] = ft_handle_int;
//	g_ftable['d'] = ft_handle_int;

}

*/


	// ok so using my system might not be so bad regarding error management, read all before print
	// and also pretty good for unicode, which is a bonus but a pretty good idea cuz not too hard aparenly....
	// also for dif outputs my way is pretty good


	// we are going to start by assuming all printing happens on Stdout


int		ft_fdprintf(int fd, const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_pfelem	*lst;

	lst = NULL;
	va_start(ap, format);
	if ((ret = ft_hq((char*)format, ap, &/*buf*/lst)) == 1)
		ret = ft_display_del(fd, &lst);	// fd_display ????
//	else
		// error ???

	va_end(ap);
	return (ret);

}

int		ft_printf(const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_pfelem	*lst;

	printf("main test\n");
	
	lst = NULL;
	va_start(ap, format);
	if ((ret = ft_hq((char*)format, ap, &/*buf*/lst)) == 1)
		ret = ft_display_del(1, &lst);
	else
		ft_putnbr(ret);
	va_end(ap);
	return (ret);
}





