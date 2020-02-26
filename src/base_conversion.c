/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:48:29 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/26 14:48:55 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

	// kinda like a strjoin		// appends a char
char		*ft_add_char(char **str, char c)				//void		ft_add_char(char **str, char c)
{
	char	*tmp;
	int		i;

//	printf("made it to add char 1, str: |%s|, len: %zu\n", *str, ft_fstrlen(*str));
	tmp = NULL;
	if ((!str || !*str) && !c)
		return (NULL);					// use other strlen ???
	if (!(tmp = malloc(sizeof(char) * (ft_fstrlen(*str) + 2))))
		return (NULL);
	i = 0;
//	printf("made it to add char 2, str: |%s|\n", *str);
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
	{
//		printf("freeing in add char, tmp: |%s|\n", tmp);
		ft_bzero(*str, ft_fstrlen(*str));
		free(*str);
	}
//	*str = tmp;
	return (tmp);
}

int			ft_base_check(char *base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])		// more conditions ???????
				return (0);
			++j;
		}
		++i;
	}
//	printf("base check 1\n");
	return (1);
}
						// more than a long ???			// should work ????
char		*ft_any_base_convert(long nb, char *base)
{
	int		i;
	int		size;
	char	*ret;
//	char	*tmp;

	i = 0;
	ret = NULL;
	size = ft_strlen(base);
	if (!ft_base_check(base))
		return (NULL);
	while (nb >= size)
	{
//		printf("ret in base conv: |%s|\n", ret);
		ret = ft_add_char(&ret, base[nb % size]);
//		printf("ret in base 2\n");
		nb /= size;
//		ft_bzero(ret, ft_fstrlen(ret));
//		free(ret);
//		ret = tmp;
	}
	ret = ft_add_char(&ret, base[nb % size]);		// do i need to do it one last time...
	printf("base convert, ret: |%s|\n", ret);
	return (ret);
}


