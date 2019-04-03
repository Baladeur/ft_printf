# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/16 17:28:51 by tferrieu          #+#    #+#              #
#    Updated: 2019/04/03 14:13:11 by tferrieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

LIB			=	./Libft/libft.a

SRC-C		=	./srcs/parsing.c \
				./srcs/ft_printf.c \
				./srcs/convert_csp.c

SRC-O		=	$(patsubst ./srcs/%.c, %.o, $(SRC-C))

FLAG		=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(SRC-C)
	make -C Libft
	gcc $(FLAG) -c $(SRC-C)
	ar rc $(NAME) $(SRC-O) $(LIB)

clean:
	make -C Libft clean
	rm -rf $(SRC-O)

fclean:
	make -C Libft fclean
	rm -rf $(SRC-O) $(NAME)

re:			fclean all

.PHONY : all clean fclean re clib fclib
