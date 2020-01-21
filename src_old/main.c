

#include "printf.h"


/*

void	test_func(int n, ...)
{
	va_list		ap;
	int			d;
	int			i;
	char		c;
	char		*s;

	va_start(ap, n);
	i = 0;
	while (i < n)
	{
		if (n
	}
	va_end(ap);
}

*/


	// so far just testing things

int		main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	printf("%c \n", av[1][0]);
	
	return (0);
}
