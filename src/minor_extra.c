/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:53:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 19:07:45 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// where does ft_fstrncpy() get called ??? do i still need it ???

#include "printf.h"

size_t	ft_fstrlen(const char *s)	// secure, returns 0 if NULL input
{
	size_t	a;

	a = 0;
	if (s)
	{
		while (s[a])
			++a;
	}
	return (a);
}

// would it be better to secure in scott_free ???
int		ft_scott_free(char **str)
{
	if (str && *str)			// this version seems fine
	{
		ft_bzero(*str, ft_fstrlen(*str));
		free(*str);
		*str = NULL;
	}
	return (-1);
}

char	*ft_fill_with(char this, size_t len)	// secure
{
	char	*ret;
	size_t	i;

	if (!this || len < 1)
		return (NULL);
	if (!(ret = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
		ret[i++] = this;
	ret[i] = '\0';
	return (ret);
}

char	*ft_fstrdup(char *str)		// secure.
{
	char 	*ret;
	int	a;

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
char	*ft_fstrncpy(char *dst, char *src, int size)
{
	int	a;

	a = 0;
	if (!dst || !src)
		return (NULL);
	while (*src && a < size)
		dst[a++] = *src++;
	dst[a] = '\0';
	return (dst);
}
