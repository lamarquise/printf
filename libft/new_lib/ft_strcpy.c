/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:54:13 by erlazo            #+#    #+#             */
/*   Updated: 2019/11/16 17:18:48 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int		a;

	a = 0;
	while (src[a])
	{
		dst[a] = src[a];
		++a;
	}
	dst[a] = '\0';
	return (dst);
}
