

#include "printf.h"

	// eventually add spec struct to args...

int			ft_handle_str(va_list ap, t_buf *buf, t_param *p)
{
	char	*tmp;

	tmp = NULL;
	if (p->type == 'c')
		// do the char thing
	else
		// string




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
