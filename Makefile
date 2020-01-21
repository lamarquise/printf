#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlamart <tlamart@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 15:44:24 by tlamart           #+#    #+#              #
#    Updated: 2019/08/20 19:46:42 by erlazo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = printf

SRC_PATH =	src/
SRC_NAME =	main.c \
			ft_printf.c \
			parser.c \
			parse_buffer.c \
			pfelem_list.c \
			handle_int.c \
			handle_str.c \
			display.c \
			extra.c \
			
			

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ_PATH = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))


#	// not sure this stuff is right ???

INC = -I include -I libft
HEADER = include/printf.h
LIB_PATH = -L libft
LIB = -lft


CC = clang
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
#	make -C libft
	$(CC) -o $@ $^ $(LIB_PATH) $(LIB) $(FW)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADER)
	@mkdir -p $(OBJ_PATH)
	$(CC)  $(INC) -o $@ -c $<

clean:
#	make clean -C libft
	rm -rf $(OBJ_PATH)

fclean: clean
#	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
