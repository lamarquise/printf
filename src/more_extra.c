/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:53:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/02 21:18:31 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

