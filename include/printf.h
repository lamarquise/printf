


#ifndef PRINTF_H
#define PRINTF_H


# define BUFF_SIZE 12	// no idea what # it should be
						// has to be the max size of arg in format...


# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"


typedef struct	s_param
{
	char	spec;			// flag contains - + space #
					// fuck, where do we store 0 or no
	int		flag;	// this is where the bitwise comes in i think
	size_t	width;
	size_t	precision;

	// could add int base...

	char	prefix[3];		// 0 here ??? what is it for again ???
	
}				t_param;

typedef struct	s_pfelem
{
	// might be nice to have the size for display purposes
	// also how do i handle \n and the likes ????

	char			*content;	// the str
	struct s_pfelem	*next;
}				t_pfelem;

typedef struct	s_buf
{
//	char		*content;	// do i need it at all ?
//	char		content[BUFF_SIZE];		// change to * not []
//	int			cursor;
	t_pfelem	*lst;
}				t_buf;


typedef int		(*t_ftc)(t_buf*, va_list, t_param*);


int			ft_printf(const char *format, ...);

	// Parsing		// do i want the const ???
int			ft_hq(/*const */char *format, va_list ap, t_buf *buf);
int			ft_field_parsing(char *format, va_list ap, char **tmp);

int			ft_flag_parsing(char **format, t_param *p, va_list ap);
int			ft_get_precision(char **format, t_param *p, va_list ap);
int			ft_get_width(char **format, t_param *p, va_list ap);


	// List stuff
t_pfelem	*new_pfelem(char *str/*, size_t size, int pos, t_param *param*/);
int			pflist_append(t_pfelem **lst, t_pfelem *new);


	// Handler functions
int			ft_handle_int(va_list ap, char **tmp, t_param *param);
int			ft_handle_str(va_list ap, char **tmp, t_param *param);


	// Display
//int				ft_display_del(t_buf *buf);
int			ft_display_del(t_pfelem **lst);


	// Extra
char		*ft_fstrjoin(char **s1, char *s2);

/*
	// List stuff
t_felem	*new_felem(char *str, size_t size, int pos, int type);
int		flist_append(t_felem **lst, t_felem *new);
*/




#endif
