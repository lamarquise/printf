/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:21 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 15:54:18 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_listify_not_spec(int i, int c, char *format, t_pfelem **lst)//secure
{
	char	*str;

	str = NULL;
	if (!format || !lst || c < 0 || c > i)
		return (-1);
	if (!(str = ft_substr(format, c, i - c)))
		return (-1);
	if (!ft_pflist_append(lst, ft_str_to_elem(str, i - c)))
		return (ft_scott_free(&str, -1));
	ft_scott_free(&str, 0);
	return (1);
}

int		ft_parsing_hq(char *format, va_list *ap, t_pfelem **lst) // secure
{
	int		i;
	int		c;
	int		m;
	char	*str;

	if (!format || !ap || !lst)
		return (-1);
	i = 0;
	str = NULL;
	while (format[i])
	{
		if ((m = ft_findchar(&format[i], '%')) != -1)
		{
			i += m;
			if ((m > 0 && ft_listify_not_spec(i, i - m, format, lst) == -1)
				|| (c = ft_spec_parsing(&format[i], ap, &str, &m)) == -1
				|| ft_pflist_append(lst, ft_str_to_elem(str, m)) == -1)
				return (ft_scott_free(&str, -1));
			i += ft_scott_free(&str, c);
		}
		else
			return (ft_listify_not_spec(ft_fstrlen(format), i, format, lst));
	}
	return (1);
}
