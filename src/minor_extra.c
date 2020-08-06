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

long	ft_scott_free(char **str, int ret)	// Secure
{
	if (str && *str)
	{
		ft_bzero(*str, ft_fstrlen(*str));
		free(*str);
		*str = NULL;
	}
	return (ret);
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

char	*ft_fstrdup(char *str)	// secure.
{
	char	*ret;
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

	// this is for those times when you need to verify with a number..
	// add to lib ?
	// Don't add to lib, the if (!og) ret(1) is my printf specific,
	// good idea to have one like this in lib, but not this one.


int		ft_nstrdup(char **cp, char *og)		// secure but gross
{
	int             a;

	ft_scott_free(cp, 0);	// still want this here ?
	if (!og)
		return (1);
	if (!cp)
		return (-1);
	a = 0;
	while (og[a])
		++a;
	if (!(*cp = ft_memalloc(sizeof(char) * (a + 1))))
		return (-1);
	a = 0;
	while (og[a])
	{
		(*cp)[a] = og[a];
		++a;
	}
	return (1);
}




