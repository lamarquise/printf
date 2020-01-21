

#include "printf.h"

	// can do this the old way if i want, but for now...

		// displays and deletes
		// could easily add a fd arg

int		ft_display_del(t_pfelem **lst)
//int			ft_display_del(t_buf *buf)
{
	t_pfelem	*tmp;
//	t_pfelem	*lst;

	printf("display test 1\n");

//	lst = buf->lst;

//	printf("buf lst: [%s]\n", buf->lst->content);

	if (!lst)
		return (-1);
	while (*lst)	// maybe secure, if something fucks up then ret 0....
	{
//		printf("display test 2\n");
		write(1, (*lst)->content, ft_strlen((*lst)->content));
//		write(1, "\n", 1);
		tmp = (*lst)->next;
//		free(lst->content);
//		free(lst);
		*lst = tmp;
	}
//	buf->lst = NULL;
//	printf("display test 3\n");
	return (1);
}
