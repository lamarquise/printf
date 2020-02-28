/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:29:04 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/28 19:10:40 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// the else ????

#include "printf.h"

int		ft_fdprintf(int fd, const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_pfelem	*lst;

	lst = NULL;
	va_start(ap, format);
	if ((ret = ft_hq((char*)format, ap, &lst)) == 1)
		ret = ft_display_del(fd, &lst);
	else
		ft_putnbr(ret);		// for now
	va_end(ap);
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_pfelem	*lst;

//	printf("main test\n");
	
	lst = NULL;
	va_start(ap, format);
	if ((ret = ft_hq((char*)format, ap, &lst)) == 1)
		ret = ft_display_del(1, &lst);
	else
	{
		ft_putnbr(ret);		// leave else for now
		
		// FREE EVERYTHING ???? like the list and stuff ????

	}
	va_end(ap);
	return (ret);
}
