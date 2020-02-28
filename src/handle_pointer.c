/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:51:45 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/26 14:57:22 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// protection ??? all flags ???

#include "printf.h"

int			ft_handle_pointer(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	void	*nb;
	size_t	len;

	// 0x0 is address null

	// petite protection ???		// necessary ????

//	printf("pointer test 1\n");

	nb = va_arg(ap, void*);
//	printf("pointer test 2\n");

//	printf("pointer test 3 ptr: |%p|\n", tmp);


	tmp = ft_any_base_convert((long)nb, "0123456789abcdef");		// what happens if pointer is NULL ??? it should make 0 to then make 0x0

	// more flags ???

	tmp = ft_fstrjoin("0x", tmp);	// handle freeing...	// that can't possibly be
	len = ft_fstrlen(tmp);									// freed ...
	
	if (p->width > len)
	{
		if (p->flag & 7)
			tmp = ft_fstrjoin(tmp, ft_fill_with(' ', p->width - len));
		else
			tmp = ft_fstrjoin(ft_fill_with(' ', p->width - len), tmp);
	}
//	printf("pointer test 2, tmp: |%s|\n", tmp);

	*str = tmp;		// make this better... more elegant...

	return (1);
}
