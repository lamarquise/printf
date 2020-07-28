/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:29:04 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 18:35:29 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
/*
char	*ft_cprintf(const char *format, ...)
{
	int			ret;
	char		*str;
	va_list		ap;
	t_pfelem	*lst;

	str = NULL;
	lst = NULL;
	va_start(ap, format);
	if ((ret = ft_parsing_hq((char*)format, ap, &lst)) == 1)
		ret = ft_display_del(fd, &lst);	// something else that joins all
	else								// into ret
		ft_putnbr(ret);		// for now
	va_end(ap);
	return (ret);
}
*/

int		ft_fdprintf(int fd, const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_pfelem	*lst;

	lst = NULL;
	va_start(ap, format);
	if ((ret = ft_parsing_hq((char*)format, &ap, &lst)) == 1)
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
	if ((ret = ft_parsing_hq((char*)format, &ap, &lst)) == 1)
		ret = ft_display_del(1, &lst);
	else
	{
//		ft_putnbr(ret);
//		ft_putchar('\n');		
		// FREE EVERYTHING ???? like the list and stuff ????
		ret = ft_pflist_del_all(&lst);
		ft_putnbr(ret);					// necessary for testing now cuz
		ft_putchar('\n');				// no one calls print ret of printf
	}
/*	if ((ret = ft_parsing_hq((char*)format, &ap, &lst)) == -1)	// the final version?
		return (-1);
	else
		ret = ft_display_del(1, &lst);	*/
	va_end(ap);
	return (ret);
}
