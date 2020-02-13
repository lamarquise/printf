

#include "printf.h"

	// eventually move this to another file
	// just for char * for now
char	*ft_salloc(size_t len, char fill)
{
	char	*ret;
	int		i;

	if (len < 1)		// other conditions ???
		return (NULL);
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len + 1] = '\0';
	ft_memset(ret, fill, len);
	return (ret);
}	// string alloc



	// eventually add spec struct to args...

int			ft_handle_str(va_list ap, char **str, t_param *p)
{
	char	*tmp;
	char	*pre;
	char	*post;
	int		len;

	tmp = NULL;
	// OR
//	tmp = va_arg(ap, char*);	take both and sort out later... ?

	if (p->type == 'c')
	{
		// do the char thing
		*tmp = va_arg(ap, char);
		len = 1;
//			p->width > 1 ? p->width : 1;	// i think, there might be a
	}										// special case for 0
	else
	{
		// string
		tmp = va_arg(ap, char*);
		while (tmp[len])
			++len;
//		len = p->width > len ? p->width : len;
	}
	// now what ???

	if (p->width > len)		// i think, but low key no idea need to test
	{
		len = p->width - len;		// use calloc ??? could actually be dope
				// make my own function that allocates and fills but null 
				// terminates
		
		if ((p->flag & 7) == 1)
		{
			// len spaces after string
			post = ft_salloc(len, ' ');		//secure ???
		}
		else if ((p->flag & 1) == 1)
		{
			// len 0's before string
			pre = ft_salloc(len, '0');
		}
		else
		{
			// len spaces before string
			pre = ft_salloc(len, ' ');
		}

	}

	if ((p->flag & 1) == 1)		// means there is a 0 ???
								// if width and no -
	if ((p->flag & 7) == 1)		// there is a -		// most important
	if ((p->flag & 15) == 1)	// there is a space	// only applies if 
								// width too small
						// wait no, it's irrelevant ???

	// precision is meaningless to strings

	// is width bigger
	// if yes, by how much
	// is there a 0
	// is there a -


	// 0's only if before not if - flag, otherwise spaces	


	// use p->type which is the int, to do shit, a generic function that could be applied to all handles would be nice...

	// need to create what comes before and what comes after...


		// OR i write a func that takes 3 param and smashes them together, also frees them ???
	*str = ft_str(ft_strjoin(pre, tmp), post);



	buf->content = va_arg(ap, char*);
	// same as handle int need more conditions as progress

	if (param->prefix[0])
	{		// use new gnl version of join ???
		tmp = ft_strjoin(" ", buf->content);
//		free(buf->content);
		buf->content = tmp;
	}

	return (1);
}
