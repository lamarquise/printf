

#include "printf.h"

	// eventually add spec struct to args...

int			ft_handle_str(va_list ap, char **str, t_param *p)
{
	char	*tmp;

	tmp = NULL;
	// OR
//	tmp = va_arg(ap, char*);	take both and sort out later... ?

	if (p->type == 'c')
	{
		// do the char thing
		*tmp = va_arg(ap, char);
	}
	else
	{
		// string
		tmp = va_arg(ap, char*);


	}
	// now what ???

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
