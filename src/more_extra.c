/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:53:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 20:57:10 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// where does ft_fstrncpy() get called ??? do i still need it ???

#include "printf.h"

char		*ft_fstrdup(char *str)
{
	char 	*ret;
	int		a;

	if (!str)
		return (NULL);
	a = 0;
	while (str[a])
		++a;
	if (!(ret = ft_memalloc(sizeof(char) * (a + 1))))
		return (NULL);
	a = 0;
	while (str[a])
	{
		ret[a] = str[a];
		++a;
	}
	return (ret);
}

		// different return ???
char		*ft_fstrncpy(char *dst, char *src, int size)
{
	int		a;

	a = 0;
	if (!dst || !src)
		return (NULL);
	while (*src && a < size)
		dst[a++] = *src++;
	dst[a] = '\0';
	return (dst);
}

		// assuming positive n
char		*ft_pos_itoa(unsigned long long n)
{
	unsigned long long	nb;
	char				*ret;
	int					len;

	nb = n;
	len = 1;
	while (nb >= 10)
	{
		nb /= 10;
		++len;
	}
	if (!(ret = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len--] = '\0';
	nb = n;
	while (len >= 0)
	{
		ret[len] = nb % 10 + 48;
		nb /= 10;
		--len;
	}
	return (ret);
}
