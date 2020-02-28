/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:49:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/28 19:10:57 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_latoi(char *str, int *len)
{
	int		a;
	int		neg;
	long	ret;

	a = 0;
	ret = 0;
	neg = 1;
	if (!*len)
		*len = 0;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32)
		++a;
	if (str[a] == 43 || str[a] == 45)
	{
		if (str[a] == 45)
			neg = -1;
		++a;
	}
	while (str[a] >= 48 && str[a] <= 57)
	{
		ret = ret * 10 + (str[a] - 48);
		++a;
		++*len;
	}
	return (ret * neg);
}

void	ft_scott_free(char **str)
{
	ft_bzero(*str, ft_fstrlen(*str));
	free(*str);
	*str = NULL;
}

char	*ft_fill_with(char this, size_t len)
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

size_t	ft_fstrlen(const char *s)
{
	size_t a;

	a = 0;
	if (s)
	{
		while (s[a])
			++a;
	}
	return (a);
}

char	*ft_fstrjoin(char *s1, char *s2)
{
	int		a;
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	a = ft_fstrlen(s1) + ft_fstrlen(s2) + 1;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * a)))
		return (NULL);
	a = 0;
	while (s1 && *s1)
		ret[a++] = *s1++;
	while (s2 && *s2)
		ret[a++] = *s2++;
	ret[a] = '\0';
	return (ret);
}
