

#include "printf.h"

void	init_specs(t_spec *tab)
{
	tab[0].type = "c";
	tab[0].f = spec_c;
	tab[1].type = "s";
	tab[1].f = spec_s;
	tab[2].type = "i";
	tab[2].f = spec_i;


	// ...

}

		// different args sent???

int		flag_check(char *format, int pos)
{

	int				i;
	static t_spec	tab[15] = {{42, NULL}};

	i = 0;
	if (tab[0] == 42)
		init_specs(tab);
	while (i < 15)
	{
		if (

		if (ft_strcmp(tab[i], format[pos]))
			return (tab[i].f(something));
	}
	return (0);
}

