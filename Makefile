# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erlazo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 15:37:26 by erlazo            #+#    #+#              #
#    Updated: 2020/02/28 19:06:42 by erlazo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FILES =		ft_printf.c \
			parser.c \
			parse_buffer.c \
			parse_flags.c \
			pfelem_list.c \
			handle_int.c \
			handle_str.c \
			handle_modulo.c \
			handle_pointer.c \
			base_conversion.c \
			display.c \
			extra.c \

IFILES = printf.h
NAME = libftprintf.a
IDIR = include/
SDIR = src/
LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a
LIBFTINC = $(LIBFTDIR)
CFLAGS = -Wall -Wextra -Werror -I$(IDIR) -I$(LIBFTINC) #-MMD -MP

SRCS = $(addprefix $(SDIR), $(FILES))
INCS = $(addprefix $(IDIR), $(IFILES))
# OBJS = $(SRCS:.c=.o)


ODIR = obj/
OBJ_NAME = $(FILES:.c=.o)
OBJS = $(addprefix $(ODIR),$(OBJ_NAME))


all: $(NAME)

$(LIBFT):
	make bonus -C $(LIBFTDIR) libft.a

$(NAME): $(OBJS) $(LIBFT) $(IDIR)
	printf "$(_GREEN)\r\33[2K\r$(NAME) created  😎\n$(_END)"
	cp $(LIBFT) $@
	ar rsc $@ $(OBJS)



$(ODIR)%.o: $(SDIR)%.c $(IDIR)
	mkdir -p $(ODIR)
	$(CC) -o $@ -c $< $(CFLAGS)
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"




clean:
	make -C $(LIBFTDIR) $@
	rm -rf $(ODIR)

fclean: clean
	make -C $(LIBFTDIR) $@
	rm -f $(NAME)
	echo "$(_RED)$(NAME) Deleted  😱$(_END)"

re: fclean all

test: all
	gcc -L. -lftprintf -Iinclude -Ilibft ./main.c -o test

testl: all
	gcc -L. -lftprintf -Iinclude -Ilibft ./main.c -o testl -g

tests: all
	gcc -Wall -Wextra -Werror -L. -lftprintf -Iinclude -Ilibft ./main.c -o tests -g3 -fsanitize=address

.PHONY: all clean fclean re

##################
##    COLORS    ##
##################

_GREY=$ \033[30m
_RED=$ \033[31m
_GREEN=$ \033[32m
_YELLOW=$ \033[33m
_BLUE=$ \033[34m
_PURPLE=$ \033[35m
_CYAN=$ \033[36m
_WHITE=$ \033[37m
_END=$ \033[0m


.SILENT:
