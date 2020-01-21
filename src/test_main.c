

#include <stdio.h>
#include <stdlib.h>


int		main(int ac, char **av)
{
	int				a;
	int				a1;
	unsigned int	b;


	if (ac == 3)
		printf("testing: [%-d][%+d]\n", atoi(av[1]), atoi(av[2]));

	a = -765;
	a1 = -765;
	b = 987;

//	printf("test: [% +d]\n", b);

	printf("test: [%d][% x]\n", a, a1);
	
	return (0);
}
