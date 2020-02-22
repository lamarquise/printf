/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:56:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/21 19:04:23 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int				ft_handle_int(va_list ap, char **str, t_param *p)
{
	char		*tmp;
	size_t		len;
	size_t		wlen;
	size_t		plen;
	size_t		i;

	tmp = 0;
	len = 0;

		// diuUxX		// possibly also oO other things too ????	better way of doing this ????

	if (p->spec == 'd' || p->spec == 'i')	// regular ints i think
	{

	}
	else if (p->spec == 'u' || p->spec == 'U')		// could manage this by storring if there is a majuscule or nah with bitwise or something
	{

	}
	else if (p->spec == 'x' || p->spec == 'X')
	{

	}

	// check flags
	// do width and precision math
	// something else ??? yea that size thing...



}


/*


							// uintmax_t better ?
int				ft_calc_len(long long nb, param *p)
{
	int		tmp;	// best be a long long ???
	int		len;

	tmp = nb;
	while (tmp /= base)	// i would need to define or send base at some point
		++len;
		// more conditions ?
	p->precision = precision > len ? precision : len;
	
	// should i also be hanlding the pos of spaces and 0s and justification
	// here ?
	
	// i should prolly also take 0x and other such things into account here



	return (len);
}

int			ft_base_setup(t_param *p)		// more elaborate params if decide it can be many dif bases... send the string, the size, etc...
{
	
									// could do size here
//	if (!(p->base = malloc(sizeof(char) * (16 + 1))))
//		return (-1);
//	p->base = B_16;		// im not sure that will work....

	

	// OR
				// could do size
	static char		b[16] = B_16;
	p->base = &b;					// would that even work ???

	return (0);
}


	// can i globally define the base ?
//static char		base[16] = "0123456789abcdef";

				// ret a double pointer ????
				// does it get an int ????
void		ft_hint_base_convert(long nb, char **ret, t_param *p)
{
	char	s[2];
	// fill in with the other crap ....

	printf("base convert, nb: [%ld]\n", nb);

	ft_bzero(s, 2);
	if (nb >= 16)
		ft_hint_base_convert(nb / 16, ret, p);
	s[0] = base[nb % 16];
	*ret = ft_fstrjoin(ret, s);
}

	// returns a string to be shoved into pfelem
int			ft_handle_int(va_list ap, t_buf *buf, t_param *p)
{
	char 	*tmp;
	long	nb;// use a long long ??? or whatever the larest is ???
	int		neg;
	int		a;


	// need to call va_list to recover the number...

	// split into signed vs unsigned, why not...

	// 



//	what is it?
//	recover it
//	prefix now ?
//	base changes now ?
//	handle width and precision



	






	a = 0;	// necessary?
	if (a = ft_findchar("uUxX", p->spec) >= 0)	// all are unsigned
		






	tmp = NULL;
	neg = 1;

//	printf("handle int test 1\n");

	buf->content = ft_itoa(va_arg(ap, int));	// start with a long to be safe ????
	printf("is buf a string? [%s]\n", buf->content);
	if (p->type == 'x')
	{
		nb = ft_atoi(buf->content);
		if (nb < 0)
		{
			neg = -1;
			nb = -nb;
		}
		ft_hint_base_convert(nb, &tmp,  p);
		free(buf->content); 	// do that ????
		if (neg < 0)
			buf->content = ft_strjoin("-", tmp);
//		printf("tmp in hex: [%s]\n", tmp);
		else
			buf->content = tmp;
	}

	if (p->prefix[0])	// shove the " " into a new elem ???
	{
		tmp = ft_strjoin(" ", buf->content);	// is it an int ???
		buf->content = tmp;
		// there have to be leaks ....
	}

	// will have to do some other things to handle param stuff...

	return(1);
}

*/





