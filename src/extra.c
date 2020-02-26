/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:49:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/26 16:58:36 by erlazo           ###   ########.fr       */
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
//	if (!*len)
//		*len = 0;
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
	if (!(ret = malloc(sizeof(char) * (len + 1))))
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

	// this shit definitly lealks

char	*ft_fstrjoin(char *s1, char *s2)
{
	int		a;
	char	*ret;
	int		c;

	if (!s1 && !s2)
		return (NULL);
	a = ft_fstrlen(s1) + ft_fstrlen(s2) + 1;
	if (!(ret = (char*)malloc(sizeof(char) * a)))
		return (NULL);
	ft_bzero(ret, a);
	a = 0;
	c = 0;
	while (s1 && (s1)[c])
	{
		ret[a++] = (s1)[c];
		++c;
	}
	while (s2 && *s2)
	{
		ret[a++] = *s2;
		++s2;
	}
	ret[a] = '\0';
//	if (s1 && *s1)
//		free(*s1);
	return (ret);
}



