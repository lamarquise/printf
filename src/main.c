

#include "printf.h"

int		main(int ac, char **av)
{
	int		a;
	char	*str;
	int		b;

	b = 12345;
	a = 30;
	if (ac < 0)
		return (0);

	if (ac == 2)
		str = av[1];

	ft_printf("test 1");
	
//	ft_printf("[the start, |%*s|\n]", 10, "the end");

	printf("\n\nOG printf:\n[a number: |%-10.7d|\n]", b);

	printf("\n\nOG printf:\n[a number: |%-.7d|\n]", b);

//	ft_printf("%s\n", "the end");

//	ft_printf("[just a char, %c\n]", 'c');

//	ft_printf("the start, [%    s] [%   d] the end\n", "a number:", ft_atoi("16"));

//	ft_printf("printing hex: %x\n", ft_atoi(av[1]));

	return (0);
}

