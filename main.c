

#include "printf.h"

int		main(int ac, char **av)
{
	int		ret1;
	int		ret2;
	int		a;
	int		imin;
	int		imax;
	char	*str;
	int		b;
	long long		c;
	long long		llmax;
	long long		llmin;
	unsigned long long	ullmax;

	ret1 = 0;
	ret2 = 0;
	llmax = 0;
	llmin = 0;
	ullmax = 0;

//	ullmax = 18446744073709551615;
	llmax = 9223372036854775807;
//	llmin = -9223372036854775808;
	imin = -2147483648;
	imax = 2147483647;
	b = 12345;
	a = 15;
	c = 39485928374590234;
	if (ac < 0)
		return (0);

	if (ac == 2)
		str = av[1];

//	ret1 = printf(
//	printf("\nret1: %d\n", ret1);
//	ret2 = ft_printf(
//	printf("\nret2: %d\n", ret2);


//	ret1 = printf("sWrHOY%0.*ixOB%*c%0.1i%i1Y4cs", -3, -52610042, -6, '\0', 0, 0);
//	printf("\nret1: %d\n", ret1);
//	ret2 = ft_printf("sWrHOY%0.*ixOB%*c%0.1i%i1Y4cs", -3, -52610042, -6, '\0', 0, 0);
//	printf("\nret2: %d\n", ret2);



//	ft_printf("number|%d| |%ld| |%lld| |%d| |%zu| |%ld| |%d| |%ld| |%lld| |%d| |%zu| |%ld|\n", b, (long)b, (long long)c, a, (size_t)b, (long)a, b, (long)b, (long long)c, a, (size_t)b, (long)a);


//	printf("|%c%c%c%c%c%c%c%c%c%c%c%c%c|\n", 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52);
//	ft_printf("|%c%c%c%c%c%c%c%c%c%c%c%c%c|\n", 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52);


//	printf("%-*.5u%1.5s%-5.0X%-18d%0.3X%-c%-ca4wRrX6zy\n", 1, -2147483647, "", -2147483647, -2147483647, -1696667795, 'g', 'd');
//	ft_printf("%-*.5u%1.5s%-5.0X%-18d%0.3X%-c%-ca4wRrX6zy\n", 1, -2147483647, "", -2147483647, -2147483647, -1696667795, 'g', 'd');


//	ft_putnbr(printf("kXF%-.0u%-X%-*s%0.*x", -2147483647, 0, 10, NULL, -2, -2091222346));
//	ft_putchar('\n');
//	ft_putnbr(ft_printf("kXF%-.0u%-X%-*s%0.*x", -2147483647, 0, 10, NULL, -2, -2091222346));

//	printf("OG testing c: |%-5c|\n", 0);
//	ft_printf("testing c: |%-5c|\n", 0);
	

//	printf("%0.*x%sf9%15.*u%.5x\n", 9, 2147483647, "", -9, 0, -2147483647);
//	ft_printf("%0.*x%sf9%15.*u%.5x\n", 9, 2147483647, "", -9, 0, -2147483647);

//	printf("%0*.3X", -1, 0);
//	printf("\n");
//	ft_printf("%0*.3X", -1, 0);
//	printf("\n");

//	printf("OG testing c: |%05s|\n", "hi");
//	ft_printf("testing c: |%05c|\n", 53);
//	printf("OG testing c: |%c|\n", 48);
//	ft_printf("testing c: |%c|\n", 48);


//	printf("OG: |%s|\n", "hi there");
//	ft_printf("OG: |%s|\n", "hi there");
//	printf("OG: |%.s|\n", "hi there");
//	ft_printf("OG: |%.s|\n", "hi there");


//	printf("OG: |%-*.*s|\n", -7, -3, "ahey");
//	ft_printf("mine: |%-*.*s|\n", -7, -9, "ahey");


//	ft_printf("The weird case: |%-5c|\n", 0);		// figure this weird case out later, still leaks


	// Tested:
//	ft_printf("%s|\n", NULL);
//	ft_printf("short prec string|%.5s|\n", "hi there");
//	ft_printf("modulo: |%%|, |%5%|, |%-5%|\n");

//	ft_printf("a simple long long: %lld\n", LLONG_MIN);
//	printf("a simple long long: %lld\n", LLONG_MIN);

//	ft_printf("%cSEIUF", 'D');
//	printf("%cSEIUF", 'D');

//	printf("int min: %.12d\n", b);
//	ft_printf("int min: %.12d\n", b);
	
//	printf("int : %.d\n", 0);
//	ft_printf("int : %.d\n", 0);


//	printf("%.0dXAL%-cz5u%17c%0d%0*xIl \n", 2147483647, '\0', '\0', 0, -7, 0);
//	ft_printf("%.0dXAL%-cz5u%17c%0d%0*xIl \n", 2147483647, '\0', '\0', 0, -7, 0);
	
//	printf("%.0X%01X%-*.*xdCw4acu1L7pL6\n", -2147483647, -2147483647, 9, -1, 0);
//	ft_printf("%.0X%01X%-*.*xdCw4acu1L7pL6\n", -2147483647, -2147483647, 9, -1, 0);




//	ft_printf("left justify: |%-5d|\n", a);
//	ft_printf("test poin: |%-20p|\n", &b);
//	ft_printf("test unsi: |%u|\n", b);
//	ft_printf("test octa: |%o|\n", b);
//	ft_printf("test octa: |%#o|\n", b);
//	ft_printf("test hexs: |%#10x|\n", b);

//	ft_printf("test base: |%B|\n", "0123456789abcdef", b);



//	ft_printf("test n: |%N| again |%N|\n");
//	printf("test n: |%N| again |%N|\n");


//	printf("|%lx|\n", 4294967295);
//	ft_printf("|%x|\n", 4294967295);
	




//	system("leaks test");
	return (0);

}

