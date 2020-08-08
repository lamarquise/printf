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

int		ft_fdprintf(int fd, const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_pfelem	*lst;

	lst = NULL;
	va_start(ap, format);
	if ((ret = ft_parsing_hq((char*)format, &ap, &lst)) == 1)
		ret = ft_display_del(fd, &lst);
	if (ret == -1)
		ret = ft_pflist_del_all(&lst);
	va_end(ap);
	return (ret);
}


	// secure except pflist_del_all (not sure possible to secure...)
int		ft_printf(const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_pfelem	*lst;

	lst = NULL;
	va_start(ap, format);
//	if ((ret = ft_parsing_hq((char*)format, &ap, NULL)) == 1)
	if ((ret = ft_parsing_hq((char*)format, &ap, &lst)) == 1)
	{
//		ret = ft_display_del(1, NULL);
		ret = ft_display_del(1, &lst);
	}
	if (ret == -1)
	{
		write(1, "-1\n", 3);
//		ret = ft_pflist_del_all(NULL);		// if this fails, we have a leak
		ret = ft_pflist_del_all(&lst);
	}
	va_end(ap);
	return (ret);
}
