/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:49:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 19:10:57 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

		// double check strjoin freeing
		// remove comments...

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

int		ft_scott_free(char **str)
{
	ft_bzero(*str, ft_fstrlen(*str));
	free(*str);
	*str = NULL;
	return (-1);
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

	// double check that free is fine

char	*ft_fstrjoin(char **s1, char **s2)
{
	int		a;
	int		b;
	int		c;
	char	*ret;


//	printf("strjoin 1, s1: |%s| s2: |%s|\n", *s1, *s2);

//	printf("strjoin 1.5\n");

//	if ((!s1 || !*s1) && (!s2 || !*s2))		// better ???
	if (!*s1 && !*s2)
		return (NULL);
//	printf("strjoin 2\n");
	a = ft_fstrlen(*s1) + ft_fstrlen(*s2) + 1;
//	printf("strjoin 3\n");

	if (!(ret = ft_memalloc(sizeof(char) * a)))
		return (NULL);
	a = 0;
	b = 0;
	c = 0;
//	printf("strjoin 7\n");
	while (*s1 && (*s1)[b])
		(ret)[a++] = (*s1)[b++];
	while (*s2 && (*s2)[c])
		(ret)[a++] = (*s2)[c++];
//	printf("strjoin 8\n");
	if (s1 && *s1 )//&& **s1)		// i think this solved my problem... but is it secure ???
	{
//		printf("in free 1, s1: |%s|\n", *s1);
		ft_scott_free(s1);
//		printf("in here, s1: |%s|\n", *s1);
	}
//	printf("strjoin 8.5\n");
	if (s2 && *s2 )//&& **s2)
	{
//		printf("in free 2, s2: |%s|\n", *s2);
		ft_scott_free(s2);
	}
//	printf("strjoin 9, ret: |%s|\n", ret);
	
	return (ret);
}










