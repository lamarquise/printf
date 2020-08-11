/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_arg_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:20:16 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 19:11:49 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_add_hash(char **pre, t_param *p)	// secure ? i think so but test
{
	char *mid;

	mid = NULL;
	if (!pre || !p)
		return (ft_scott_free(pre, -1));
	if (p->spec == 'x' && !(mid = ft_fstrdup("0x")))
		return (ft_scott_free(pre, -1));
	else if (p->spec == 'X' && !(mid = ft_fstrdup("0X")))
		return (ft_scott_free(pre, -1));
	else if (p->spec == 'o' && !(mid = ft_fstrdup("0")))
		return (ft_scott_free(pre, -1));
	else if (p->spec == 'b' && !(mid = ft_fstrdup("0b")))
		return (ft_scott_free(pre, -1));
	if (mid && !(*pre = ft_fstrjoin(&mid, pre))) // fjoin handles our frees
		return (-1);
	return (1);
}


// don't worry about freeing str, gets handled after
// free everything created and pre

// secure i think but double check...
// not sure about the last if... test errors
int		ft_h_int_wid(t_param *p, char **pre, char **str, int neg)
{
	char	c;
	char	*post;

	if (!p || !pre || !str)
		return (ft_scott_free(pre, -1));
	c = ' ';
	post = NULL;
	if (p->flag & F_ZERO && !(p->flag & F_MINU) && !(p->flag & F_PREC))
		c = '0';
	if (!(post = ft_fill_with(c, p->width - p->precision)))
		return (ft_scott_free(pre, -1));
	if (!(p->flag & F_MINU))
	{
		if (c != '0' && p->flag & F_PLUS)
		{
			//	printf("hint post: |%s|\n", post);
			if (!(*pre = ft_cstrjoin((neg < 0 ? '-' : '+'), pre)))
				return (ft_scott_free(&post, -1));
			p->flag &= (0 << 2);
		}
		if (!(*pre = ft_fstrjoin(&post, pre)))	// fjoin handles free
			return (-1);
	}
	else if (!(*str = ft_fstrjoin(str, &post)))
		return (ft_scott_free(pre, -1));
	//	printf("hing end pre: |%s|\n", *pre);
	if (p->flag & F_SPAC && !(p->flag & F_PLUS) && *pre) // last condition ??
		(*pre)[0] = ' ';	// not sure about this one
	return (1);
}


// Seriously Double check that this shit does what i want it to, like leaks and such

int		ft_prec_is_zero(char **str, size_t *len)
{	// i think secure cuz in theory str doesn't exist yet, but not sure...
	if (!str || !len)
		return (-1);	// do we want this ???
	if (*str)			// useful ???
		free(*str);
	if (!(*str = ft_fstrdup("")))
		return (-1);	// free str here ? or above ?
	*len = 0;
	return (1);
}

	// secure but test
int		ft_h_str_prec(t_param *p, char **str, size_t *len)
{
	int		n;
	char	*pre;

	if (!p || !str || !len)
		return (-1);
	pre = NULL;
	if (p->precision == 0 && ft_prec_is_zero(str, len) == -1)
		return (-1);
	else if ((n = (p->precision < *len ? p->precision : 0)) > 0)
	{
		if (!(pre = ft_substr(*str, 0, n)))
			return (-1);
		ft_scott_free(str, 0);
		*str = pre;
		pre = NULL;	// necessary ?
		*len = n;
	}
	return (1);
}

	// may need to be shorter...
	// str gets freed above in all error cases

int		ft_h_str_wid(t_param *p, char **str, size_t len)
{
	char	c;
	char	*pre;

	if (!p || !str)
		return (-1);
	c = ' ';
	pre = NULL;
	p->width = (p->width <= len ? 0 : p->width - len);
	if (p->width)	// double check what happens when p->wid = 0
	{
		if (!(p->flag & F_MINU))
		{
			if (p->flag & F_ZERO)
				c = '0';
			if (!(pre = ft_fill_with(c, p->width)) || !(*str = ft_fstrjoin(&pre, str)))
				return (-1);		// secures it self
		}
		else if (!(pre = ft_fill_with(c, p->width)) || !(*str = ft_fstrjoin(str, &pre)))
			return (-1);	// pretty sure is secure
	}
	else if (p->flag & F_SPAC)
	{
		if (!(pre = ft_cstrjoin(' ', &pre)) || !(*str = ft_fstrjoin(&pre, str)))
			return (-1);	// secures it self
		++len;
	}
	return (len + p->width);
}





