/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:29:27 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/03 15:52:39 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		is_pos(long long n)
{
	long long	nb;

	nb = n;
	if (nb < 0)
		nb = -nb;
	return (nb);
}

char			*ft_itoa(long long n)
{
	char		*ret;
	long long	nb;
	int			len;

	nb = is_pos(n);
	len = 1;
	if (n < 0)
		++len;
	while (nb >= 10)
	{
		nb /= 10;
		++len;
	}
	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[0] = '-';
	ret[len--] = '\0';
	nb = is_pos(n);
	while (len >= ((n < 0) ? 1 : 0))
	{
		ret[len] = nb % 10 + 48;
		nb /= 10;
		--len;
	}
	return (ret);
}
