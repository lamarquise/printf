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

int		ft_fstrlen(const char *s)	// secure
{
	int		a;

	a = 0;
	if (s)
	{
		while (s[a])
			++a;
	}
	return (a);
}

int		ft_nstrlen(char *s, int ret)
{
	int		a;

	a = 0;
	if (!s)
		return (ret);
	while (s[a])
		++a;
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

char	*ft_fstrdup(char *str)	// secure.
{
	char	*ret;
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

int		ft_nstrdup(char **cp, char *og)		// secure
{
	int		a;

	if (!og)
		return (1);
	if (!cp)
		return (0);
	a = 0;
	while (og[a])
		++a;
	if (!(*cp = ft_memalloc(sizeof(char) * (a + 1))))
		return (0);
	a = 0;
	while (og[a])
	{
		(*cp)[a] = og[a];
		++a;
	}
	return (1);
}
