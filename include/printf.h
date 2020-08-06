/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:13:46 by erlazo            #+#    #+#             */
/*   Updated: 2020/07/22 19:01:09 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
#define PRINTF_H

//# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
//# include <unistd.h>
# include "libft.h"


# include <limits.h>	// necessary ???



	// Unused...	// also i illegal i think, but F_ and C_ are fine :)
# define BL_16		1234567890abcdef
# define BU_16		1234567890ABCDEF
	// other bases ????

	// this stuff works but is it allowed ???

# define F_ZERO		0x01
# define F_HASH		0x02
# define F_PLUS		0x04
# define F_MINU		0x08
# define F_SPAC		0x10
# define F_PREC		0x20
# define F_WIDT		0x40
# define F_NULL		0x80		// null or 0 ???

// others ???

# define C_H		0x01
# define C_HH		0x02
# define C_L		0x04
# define C_LL		0x08
# define C_Z		0x10
# define C_J		0x20


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

/*
**	Printf.c
*/

int					ft_printf(const char *format, ...);
int					ft_fdprintf(int fd, const char *format, ...);

/*
**	Parsing		// do i want the const ???
*/

int					ft_parsing_hq(char *format, va_list *ap, t_pfelem **lst);
int					ft_listify_not_spec(int i, int c, char *format, t_pfelem **lst);
int					ft_spec_parsing(char *format, va_list *ap, char **str, int *m);
int					ft_pick_handler(va_list *ap, char **str, t_param *p, int *m);
int					ft_init_param(t_param *p);
int					ft_flag_parsing(char *format, t_param *p, va_list *ap);
int					ft_get_precision(char *format, t_param *p, va_list *ap);
int					ft_get_width(char *format, t_param *p, va_list *ap);
int					ft_get_size(char *format, t_param *p);

/*
**	List stuff
*/

int					ft_print_lst(t_pfelem **lst);
t_pfelem			*ft_new_pfelem(char *str, int size);
int					ft_pflist_append(t_pfelem **lst, t_pfelem *new);
t_pfelem			*ft_str_to_elem(char *str, int size);
int					ft_pflist_del_all(t_pfelem **lst);

/*
**	Casting functions
*/

long long			ft_cast_d(va_list *ap, t_param *p);
unsigned long long	ft_cast_u(va_list *ap, t_param *p);

/*
**	Handler functions
*/

int					ft_handle_int(va_list *ap, char **str, t_param *param);
int					ft_handle_uint(va_list *ap, char **str, t_param *p);
int					ft_handle_str(va_list *ap, char **str, t_param *param);
int					ft_handle_char(va_list *ap, char **str, t_param *p);
int					ft_handle_modulo(char **str, t_param *p);
int					ft_handle_pointer(va_list *ap, char **str, t_param *p);


char				*ft_gen_arg_str_i(t_param *p, char **tmp, size_t len, int neg);
int					ft_gen_arg_str_s(t_param *p, char **str, size_t len);

/*
**	Gen Arg Str
*/

int					ft_add_hash(char **pre, t_param *p);
int					ft_prec_is_zero(char **str, size_t *len);
int					ft_h_int_wid(t_param *p, char **pre, char **tmp, int neg);

/*
**	Display
*/

int					ft_display_del(int fd, t_pfelem **lst);

/*
**	Major Extra
*/

char				*ft_pos_itoa(unsigned long long n);
int					ft_latoi(char *str, long *num);
//int					ft_latoi(char *str, int *num);
char				*ft_fstrjoin(char **s1, char **s2);
char				*ft_cstrjoin(char c, char **s2);

/*
**	Minor Extra
*/

size_t				ft_fstrlen(const char *s);
long				ft_scott_free(char **str, int ret);
char				*ft_fill_with(char this, size_t len);
char				*ft_fstrdup(char *str);
int					ft_nstrdup(char **cp, char *og);

/*
**	Base Convert
*/

int					ft_base_check(char *base);
char				*ft_any_base_convert(unsigned long long nb, char *base);

#endif
