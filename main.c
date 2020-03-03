

#include "printf.h"

int		main(int ac, char **av)
{
	int		a;
	char	*str;
	int		b;
	long long		c;

	b = 12345;
	a = 15;
	c = 39485928374590234;
	if (ac < 0)
		return (0);

	if (ac == 2)
		str = av[1];

//	printf("testing main 1\n");


//	printf("OG: |%-*.*s|\n", -7, -3, "ahey");
//	ft_printf("mine: |%-*.*s|\n", -7, -9, "ahey");

//	printf("%s\n", "ahey   ");
//	ft_printf("%s|\n", "ahey   ");


//	printf("a number: %lld\n", c);
//	ft_printf("a number: %lld\n", c);


//	ft_printf("[a number: |%d| a number: |%d|\n]", a, b);

//	ft_printf("%s", "\xE2\x98\xA0\n");

//	ft_printf("test bina: |%B|\n", c);

//	ft_printf("left justify: |%-5d|\n", a);
//	ft_printf("no left justify: |%5d|\n", a);

//	ft_printf("%%");
//	ft_printf("modulo: |%%|, |%5%|, |%-5%|\n");
//	ft_printf("modulo testing: |%-5%|\n");


//	ft_printf("test n: |%N|\n");

//	ft_printf("testing precision: |%.8d|\n", b);

//	printf("|%-5c|\n", 0);
//	ft_printf("|%-5c|\n", 0);
	printf("OG: |%.5s|\n", "hi there");
	ft_printf("|%.5s|\n", "hi there");



//	ft_printf("test n: |%N| again |%N|\n");
//	printf("test n: |%N| again |%N|\n");

//	printf("print c :|%c|\n", 0);
//	ft_printf("ftprint c :|%c|\n", 0);

//	ft_printf("test poin: |%-20p|\n", &b);
//	printf("OG pointer: |%-20p|\n", &b);

//	ft_printf("test modu: |%%|\n");

//	ft_printf("test unsi: |%u|\n", b);
//	ft_printf("test octa: |%o|\n", b);
//	ft_printf("test octa: |%#o|\n", b);
//	ft_printf("test hexs: |%#10x|\n", b);
//	ft_printf("test base: |%b|\n", "0123456789abcdef", b);
//	ft_printf("test stri: |%*s|\n", a, "hi there");
//	ft_printf("test bad base: |%b|\n", "0123455", b);

//	printf("[OG the start, |%s|\n", NULL);
//	ft_printf("[the start, |%s|\n", NULL);

//	printf("[OG the start, |%10.s|\n", NULL);
//	ft_printf("[the start, |%10.s|\n", NULL);

//	printf("|%lx|\n", 4294967295);
//	ft_printf("|%x|\n", 4294967295);
	


//	printf("[OG the start, |%.s|\n", "the end");
//	ft_printf("[the start, |%s|\n", "the end");

//	ft_printf("%.s", "the end");

	
//	ft_printf("[the start, |%-32s|\n]", "the end");

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

