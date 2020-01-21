

#include "printf.h"


/*		// all this stuff is now obsolete...

	// returns ints based on which flag it has come accross...

	// not sure this func is gonna be necessary
char	*list_join_del(t_arg **lst)
{
	char	*ret;
	t_arg	*tmp;		// not sure ill need tmp, but use for now

	if (!lst || !*lst)
		return (0);
	while (*lst)
	{
		tmp = (*lst);
		ft_strjoin(ret, (*lst)->content);
		(*lst) = (*lst)->next;
		free(tmp);
	}
//	free(lst);		// do i need this???
	return (ret);
}

	// reads through format and sorts out strings from specifiers

t_felem	*format_seperator(char *str, int start)	// and args??? or next arg?
{
	char	*ret;
	int		i;
	int		c;

	i = 0;
	ret = NULL;

	// check for % then see about specifiers
	if (str[start] == '%')
	{
		// need to check if there are still args passed to printf
		// then, ???
		
		// specefier check function
		// create new felem with all info
	}
	else
	{
		while (str[start + i] && str[start + i] != '%')
			++i;
		if (i > 0)
		{
			if (!(ret = (char *)ft_memalloc(sizeof(char) * (i + 1))))
				return (0);
			c = 0;
			while (c < i)
			{
				ret[c] = str[start + c];
				++c;
			}
			return (ft_new_felem(ret, (size_t)i, start, 0));
		}
	}
	return (0);
}
*/


/*		// old version...

int		ft_printf(const char *format, ...)
{
	int		i;
	t_felem	*tmp;
	t_felem	*flst;		// or a pointer ???


	// need to initialize the t_spec's
	// no i don't it will be initialized when the first is called.
	


	i = 0;
	// should i instead do some init stuff in here???
	while (format[i])
	{

		// ok so here only hanlde string seperation into elem

		if ((tmp = format_seperator(format, i)))	// if its 1, right ???
		{

			// here we apend the list of felems
			flist_append(&flst, tmp);
			i += tmp->size;
		}
		else
		{
			//something has gone wrong, handle error cases

		}
	}

	// call func that prints whole list...



	return (0);		// what the hell am i retruning???
}
*/

/*

static t_ftc	g_ftable[127] = {NULL};

static void		ft_funcfactory(void)
{
	g_ftable['d'] = ft_handle_int;
	g_ftable['D'] = ft_handle_int;
	
	g_ftable['c'] = ft_handle_char;
	g_ftable['p'] = ft_handle_ptr;
	g_ftable['s'] = ft_handle_str;
	g_ftable['u'] = ft_handle_int;
	g_ftable['U'] = ft_handle_int;
	g_ftable['x'] = ft_handle_int;
	g_ftable['X'] = ft_handle_int;
	g_ftable['o'] = ft_handle_int;
	g_ftable['O'] = ft_handle_int;
//	g_ftable['d'] = ft_handle_int;
//	g_ftable['d'] = ft_handle_int;


}


*/


	// we are going to start by assuming all printing happens on Stdout

int		ft_printf(const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_buf		buf;
	t_pfelem	*lst;

	printf("main test\n");
	
	lst = NULL;
	ft_memset(&buf, 0, sizeof(buf));
	buf.lst = lst;
	buf.content = NULL;
	va_start(ap, format);
	if ((ret = ft_hq((char*)format, ap, &buf)) == 1)
		ret = ft_display_del(&buf.lst);
//		ret = ft_display_del(&buf);// or do i have to link through buf ???
							// call &buf.lst if want to do the old way...

	va_end(ap);
	return (ret);
}





