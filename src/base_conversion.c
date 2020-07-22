/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:48:29 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 17:20:09 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"


	// what if insead i did a single huge allocation and put everything to the
	// right end and added towards the left. then chop off the front for the
	// return ... would that be more efficient ?

char		*ft_add_char(char c, char **str)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	if ((!str || !*str) && !c)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(char) * (ft_fstrlen(*str) + 2))))
		return (NULL);
	i = 0;
	tmp[i] = c;
	while (*str && (*str)[i])
	{
		tmp[i + 1] = (*str)[i];
		++i;
	}
	tmp[i + 1] = '\0';
	if (str && *str)		// redundant if ?
		ft_scott_free(str);
	return (tmp);
}

int			ft_base_check(char *base)
{
	int		i;
	int		ret;

	ret = 0;
	if (!base)			// want so doesnt seg fault below
		return (-1);
	while (base[ret])
	{
		i = ret + 1;
		while (base[i])
		{
			if (base[ret] == base[i])		// more conditions ???????
				return (-1);
			++i;
		}
		++ret;
	}
	return (ret > 1 ? ret : -1);
}

	// better way of doing add_char, like only 1 appel ?
char		*ft_any_base_convert(unsigned long long nb, char *base)
{
	int		size;
	char	*ret;

	ret = NULL;
	if ((size = ft_base_check(base)) == -1)
		return (NULL);
	while (nb >= (unsigned int)size)	// better cast ?
	{
		if (!(ret = ft_add_char(base[nb % size], &ret)))
			return (ft_scott_free(&ret) == -1 ? NULL : NULL);		//ghetto af
		nb /= size;
	}
	if (!(ret = ft_add_char(base[nb % size], &ret)))
		return (ft_scott_free(&ret) == -1 ? NULL : NULL);	// kinda janky...
	return (ret);
}


