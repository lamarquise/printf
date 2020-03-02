/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:13:46 by erlazo            #+#    #+#             */
/*   Updated: 2020/03/02 20:57:36 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
#define PRINTF_H


# define BUFF_SIZE 12	// no idea what # it should be
						// has to be the max size of arg in format...


//# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
//# include <unistd.h>
# include "libft.h"



# define B_16			1234567890abcdef

	// other bases ????


	// here add defines for the bitwise ops, but do them in HEX like Joanne cuz that way the math is like way easier....

	// this stuff works but is it allowed ???

# define F_ZERO			0x01
# define F_HASH			0x02
# define F_PLUS			0x04
# define F_MINU			0x08
# define F_SPAC			0x10
# define F_PREC			0x20
# define F_WIDT			0x40
# define F_NULL			0x80

// others ???

# define C_H		0x01
# define C_HH		0x02
# define C_L		0x04
# define C_LL		0x08
# define C_Z		0x10
# define C_J		0x20

// there are more ...




typedef struct		s_param
{
	char		spec;
	int			flag;
	size_t		width;
	size_t		precision;
	int			size;
}					t_param;

typedef struct		s_pfelem
{
	// might be nice to have the size for display purposes
	// also how do i handle \n and the likes ????

	char			*content;	// the str
	int				size;
	struct s_pfelem	*next;
}					t_pfelem;

typedef struct		s_buf			// obsolete unless i decide to use the buffer thing
{
//	char		*content;	// do i need it at all ?
//	char		content[BUFF_SIZE];		// change to * not []
//	int			cursor;
	t_pfelem	*lst;
}					t_buf;


//typedef int		(*t_ftc)(t_buf*, va_list, t_param*);


int					ft_printf(const char *format, ...);
int					ft_fdprintf(int fd, const char *format, ...);


	// Parsing		// do i want the const ???
int					ft_hq(char *format, va_list ap, t_pfelem **lst);
int					ft_field_parsing(char *format, va_list ap, char **str, int *read);
int					ft_flag_parsing(char *format, t_param *p, va_list ap);
int					ft_get_precision(char *format, t_param *p, va_list ap);
int					ft_get_width(char *format, t_param *p, va_list ap);
int					ft_get_size(char *format, t_param *p);


	// List stuff
t_pfelem			*new_pfelem(char *str, int size);
int					pflist_append(t_pfelem **lst, t_pfelem *new);
t_pfelem			*ft_buf_to_elem(char *str, int size);


	// Casting functions
long long			ft_cast_d(long long num, t_param *p);
unsigned long long	ft_cast_u(unsigned long long num, t_param *p);


	// Handler functions
int					ft_handle_int(va_list ap, char **str, t_param *param);
int					ft_handle_uint(va_list ap, char **str, t_param *p);
int					ft_handle_str(va_list ap, char **str, t_param *param);
int					ft_handle_modulo(char **str, t_param *p);
int					ft_handle_pointer(va_list ap, char **str, t_param *p);


char				**ft_gen_arg_str(t_param *p, char **tmp, size_t len, int neg);



	// Display
int					ft_display_del(int fd, t_pfelem **lst);


	// Extra
int					ft_latoi(char *str, int *len);
//char				*ft_fstrjoin(char *s1, char *s2);
char				**ft_fstrjoin(char **s1, char **s2);
size_t				ft_fstrlen(const char *s);
char				*ft_fill_with(char this, size_t len);
void				ft_scott_free(char **str);


	// More Extra
char				**ft_fstrdup(char *str, int size);


	// Base Convert
char				*ft_add_char(char, char **str);
int					ft_base_check(char *base);
char				*ft_any_base_convert(unsigned long long nb, char *base);



#endif
