/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:56:08 by erlazo            #+#    #+#             */
/*   Updated: 2020/02/23 19:26:25 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"


	// make a function that returns a string of things to be added before or after the bit in va_list

int				ft_handle_int(va_list ap, char **str, t_param *p)
{
	char		*tmp;
	char		*pre;
	char		*post;
	char		c;
	int			num;
	size_t		len;
	size_t		wlen;
	size_t		plen;
	size_t		i;

	tmp = NULL;
	pre = NULL;
	post = NULL;
	len = 0;		// usefull ???

	i = 0;


		// diuUxX		// possibly also oO other things too ????	better way of doing this ????

	if (p->spec == 'd' || p->spec == 'i')	// regular ints i think
	{
		num = va_arg(ap, int);		// use a special itoa ???
		tmp = ft_itoa(num);

		len = ft_strlen(tmp);

	}
	else if (p->spec == 'u' || p->spec == 'U')		// could manage this by storring if there is a majuscule or nah with bitwise or something
	{

	}
	else if (p->spec == 'x' || p->spec == 'X')		// do a thing where i standardize x and X to just x but remember if it's maj, same for u and U ???
	{
		// tmp = some_function_that_changes_base( va_arg(ap, int?
	}

	if (num < 0)		// if it's neg same as if flag + so set to 1
		p->flag |= 4;		// ????		// is 4 equivalent to (1 << 3) ?????? no idea, but i hope so...


	// check flags
	// do width and precision math
	// something else ??? yea that size thing...
	// "0#+- .123456789*hljz"

	
	// Precision: pads with '0's on right, unaffected by '-', takes precedent over width.	// 0s added on left never right of num unless a float ???
	// Width: pads with ' 's on right, OR '0's if '0' flag, OR left justify with ' '  not '0' if '-'

	// signs + or - do not count in precision but do count in width...
	// 0x of # does not count in precision but does in width...


	// FLag options:
	// '-' left justify
	// '0' zeros not spaces			// ignored if there is a -
	// ' ' a space sometimes ???
	// '+' sign in front of ints
	// '#' 0x in front of hex numbers



	wlen = (p->width <= len ? 0 : p->width - len);

	plen = (p->width <= len ? 0 : p->width - len);

		// #				// + but only if not neg ???		// space but only sometimes ??? also will hex work ???
	i = (p->flag & 2) * 2 + (p->flag & 4) + (p->flag & 0x10) /*+ 1*/;	// more things that add ????
	// i is all the things that are counted by width but not by precision...



			// this may be unnecessary...
	if (!(*str = malloc(sizeof(char) * ((wlen > plen ? wlen : plen) + len /*+ i*/ + 1))))
		return (-1); 		// better return would be nice...


	// if - then all on left but precision 0s on left of num whereas width 


	// how to adapt this middle out system to other specs, like the unsigned ones ???? 

	// OK the freeing in this whole things is an absolute shit show...

	if (plen)		// adding 0s from precision
		pre = ft_fill_with('0', plen);		// could make this a sep func so that can take into acount if a num is a float or whatever....
	if ((p->spec == 'x' ||p->spec == 'X') && p->flag & 3)	// thers a # so add 0x
	{
		pre = ft_strjoin("0x", pre);
	}
	if (p->flag & 4)	// theres a + or its negative		// has to be before the - one		// adding a sign
	{
		pre = ft_strjoin((num < 0 ? '-' : '+'), pre);
	}
	if (wlen > plen)	// if - then ignor 0 meaning will put spaces on right, else puts 0s on left
	{
		c = ' ';
		if (p->flag & 1 && p->flag ! 7)	// theres a 0 and theres no -
			c = '0';
		post = ft_fill_with(c, wlen - plen - i);
		if (p->flag ! 7)    // there is not a -
			pre = ft_strjoin(post, pre);
			// bzero post and free it ???
	}


	// adding the space is prolly at the end cuz outside...
	// how does space behave, do i need to include in the i math, like about width...

	*str = ft_strjoin(ft_strjoin(pre, tmp), post);



	return (1);			// better ret ????
}


	// there has 1000% got to be a better way of doing this...

void		ft_hex_base_convert(long nb, char **ret, t_param *p)
{
	char	s[2];
	// fill in with the other crap ....

	printf("base convert, nb: [%ld]\n", nb);

	ft_bzero(s, 2);
	if (nb >= 16)
		ft_hint_base_convert(nb / 16, ret, p);
	s[0] = base[nb % 16];
	*ret = ft_fstrjoin(*ret, s);
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





