/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:49:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 19:07:47 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_pos_itoa(unsigned long long n)	// secure
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

int		ft_latoi(char *str, long *num)	// Secure
{
	int	a;
	int	neg;
	int	nlen;

	if (!str || !num)
		return (-8);
	a = 0;
	neg = 1;
	*num = 0;
	nlen = 0;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32)
		++a;
	if (str[a] == 43 || str[a] == 45)
	{
		if (str[a] == 45)
			neg = -1;
		++a;
	}
	while (str[a + nlen] >= 48 && str[a + nlen] <= 57)
	{
		*num = *num * 10 + (str[a + nlen] - 48);
		++nlen;
	}
	*num *= neg;
	return (nlen);
}

char	*ft_fstrjoin(char **s1, char **s2)	// Secure
{
	int		a;
	int		b;
	int		c;
	char	*ret;

	if (!*s1 && !*s2)
		return ((char*)(ft_scott_free(s1, 0) + ft_scott_free(s2, 0)));
	a = ft_fstrlen(*s1) + ft_fstrlen(*s2) + 1;
	if (!(ret = ft_memalloc(sizeof(char) * a)))
		return ((char*)(ft_scott_free(s1, 0) + ft_scott_free(s2, 0)));
	a = 0;
	b = 0;
	c = 0;
	while (*s1 && (*s1)[b])
		ret[a++] = (*s1)[b++];
	while (*s2 && (*s2)[c])
		ret[a++] = (*s2)[c++];
	ft_scott_free(s1, 0);
	ft_scott_free(s2, 0);
	return (ret);
}

char	*ft_cstrjoin(char c, char **s2)	// Secure
{
	int		a;
	int		b;
	char	*ret;

	if (!s2)
		return (NULL);
	a = ft_fstrlen(*s2) + 2;
	if (!(ret = ft_memalloc(sizeof(char) * a)))
		return ((char*)ft_scott_free(s2, 0));
	a = 0;
	b = 0;
	ret[a++] = c;
	while (*s2 && (*s2)[b])
		ret[a++] = (*s2)[b++];
	ft_scott_free(s2, 0);
	return (ret);
}

char	*ft_fill_with(char this, int len)	// secure
{
	char	*ret;
	int		i;

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
