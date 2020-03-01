/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:48:29 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/27 15:45:24 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// need to double check a few things and see about more security

#include "printf.h"

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
//		printf("while in add char\n");
		tmp[i + 1] = (*str)[i];
		++i;
	}
//	printf("made it to add char 3\n");
	tmp[i + 1] = '\0';
	if (str && *str)
		ft_scott_free(str);
	return (tmp);
}

int			ft_base_check(char *base)
{
	int		i;
	int		ret;

	ret = 0;
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
//	printf("base check 1\n");
	return (ret > 1 ? ret : -1);
}
						// more than a long ???			// should work ????
char		*ft_any_base_convert(long long nb, char *base)
{
	int		size;
	char	*ret;

	ret = NULL;
	if ((size = ft_base_check(base)) == -1)
		return (NULL);
	while (nb >= size)
	{
//		printf("ret in base conv: |%s|\n", ret);
		ret = ft_add_char(base[nb % size], &ret);		// is this the right order ??
//		printf("ret in base 2\n");						// double check...
		nb /= size;
	}
	ret = ft_add_char(base[nb % size], &ret);		// do i need to do it one last time...
//	printf("base convert, ret: |%s|\n", ret);
	return (ret);
}


