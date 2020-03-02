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

char		**ft_fstrdup(char *str, int size)
{
	char 	**ret;
	int		a;

	if (!(ret = malloc(sizeof(char*))))
		return (NULL);
	if (!str)
		return (NULL);
	if (!((*ret) = ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	a = 0;
	while (*str && a < size)
		(*ret)[a++] = *str++;
	return (ret);
}
