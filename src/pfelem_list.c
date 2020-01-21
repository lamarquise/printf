

#include "printf.h"

t_pfelem	*new_pfelem(char *str)/*, size_t size, int pos), t_spec *spec)*/
{
	t_pfelem	*new;

//	printf("new elem test 1\n");

	if (!str)
		return (NULL);
	if (!(new = (t_pfelem*)ft_memalloc(sizeof(t_pfelem))))
		return (NULL);
	new->content = str;		// the actual contents
//	new->size = size;		// basically len
//	new->pos = pos;			// in the format string
//	new->spec = spec;		// the specifiers, 
	new->next = NULL;

//	printf("new elem test 2\n");

	return (new);
}


			// may not need a **lst,  *lst would do, i think...

int		pflist_append(t_pfelem **lst, t_pfelem *new)
{
	t_pfelem	*tmp;

	printf("append list test 1\n");

//	printf("new content: [%s]\n", new->content);


	if (!lst || !new)
		return (0);
//	printf("append list test 1.1\n");
	if (!(*lst))
	{
//		printf("append list test 1.2\n");
		*lst = new;
//		printf("append list test 1.5\n");
		return (1);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;		// necessary???

	printf("append list test 2\n");

	return (1);
}

