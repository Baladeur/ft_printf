# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 13:50:26 by tferrieu          #+#    #+#              #
#    Updated: 2019/04/04 19:19:23 by tferrieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC-C	=	./libft/biggest_int.c \
			./libft/ft_abs.c \
			./libft/ft_atoi.c \
			./libft/ft_getbase.c \
			./libft/ft_getpow.c \
			./libft/ft_isdigit.c \
			./libft/ft_itobase.c \
			./libft/ft_strchr.c \
			./libft/ft_strcpy.c \
			./libft/ft_strdup.c \
			./libft/ft_strnew.c \
			./libft/ft_strnset.c \
			./srcs/ft_printf.c \
			./srcs/parsing.c \
			./srcs/convert_csp.c \
			./srcs/convert_int.c \
			./srcs/convert_oux.c 

SRC-O	=	biggest_int.o \
			ft_abs.o \
			ft_atoi.o \
			ft_getbase.o \
			ft_getpow.o \
			ft_isdigit.o \
			ft_itobase.o \
			ft_strchr.o \
			ft_strcpy.o \
			ft_strdup.o \
			ft_strnew.o \
			ft_strnset.o \
			ft_printf.o \
			parsing.o \
			convert_csp.o \
			convert_int.o \
			convert_oux.o

NAME	=	libftprintf.a

FLAG	=	-c -Wall -Werror -Wextra

all :		$(NAME)

$(NAME) :
			gcc $(FLAG) $(SRC-C)
			ar rc $(NAME) $(SRC-O)

clean :
			rm -rf $(SRC-O)

fclean :	clean
			rm -rf $(NAME)

re :		fclean all
