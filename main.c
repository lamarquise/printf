

#include "printf.h"

int		main(int ac, char **av)
{
	int		a;
	char	*str;
	int		b;
	int		c;

	b = 12345;
	a = 30;
	c = 3;
	if (ac < 0)
		return (0);

	if (ac == 2)
		str = av[1];


//	ft_printf("[n: |%d|m: |%d|\n]", a, b);

//	printf("%s", "\x98\xA0\n");

	ft_printf("test bina: |%B|\n", c);

//	ft_printf("test n: |%N|\n");

	ft_printf("test n: |%N| again |%N|\n");
//	printf("test n: |%N| again |%N|\n");

	ft_printf("test poin: |%20p|\n", &b);
//	printf("OG pointer: |%20p|\n", &b);

	ft_printf("test modu: |%%|\n");

	ft_printf("test unsi: |%u|\n", b);
//	ft_printf("test octa: |%o|\n", b);
	ft_printf("test octa: |%#o|\n", b);
	ft_printf("test hexs: |%#10x|\n", b);
//	ft_printf("test base: |%b|\n", "0123456789abcdef", b);
	
	ft_printf("[the start, |%*s|\n]", 10, "the end");

//	printf("OG a |% 010%|\n");

//	printf("OG a number: |%o|\n", b);
//	printf("OG a number: |%#o|\n", b);

//	printf("pointer: |%p|\n", &a);
//	printf("pointer: |%-5p|\n", NULL);
//	printf("pointer: |%5p|\n", NULL);

//	printf("OG a number: |%.0d|\n", b);


//	printf("\n\nOG printf:\n[a number: |%-10.7d|\n]", b);

//	printf("\n\nOG printf:\n[a number: |%-.7d|\n]", b);



//	ft_printf("%s\n", "the end");

//	ft_printf("[just a char, %c\n]", 'c');

//	ft_printf("the start, [%    s] [%   d] the end\n", "a number:", ft_atoi("16"));

//	ft_printf("printing hex: %x\n", ft_atoi(av[1]));
//	system("leaks tests");
	return (0);
}

