# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 13:50:26 by tferrieu          #+#    #+#              #
#    Updated: 2019/04/09 21:24:18 by tferrieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC-C	=	./libft/biggest_int.c \
			./libft/ft_abs.c \
			./libft/ft_atoi.c \
			./libft/ft_getbase.c \
			./libft/ft_getpow.c \
			./libft/ft_isdigit.c \
			./libft/ft_itobase.c \
			./libft/ft_pow.c \
			./libft/ft_strchr.c \
			./libft/ft_strcpy.c \
			./libft/ft_strdup.c \
			./libft/ft_strlen.c \
			./libft/ft_strmake.c \
			./libft/ft_strnew.c \
			./libft/ft_strncpy.c \
			./libft/ft_strndup.c \
			./libft/ft_strnset.c \
			./srcs/ft_printf.c \
			./srcs/parsing.c \
			./srcs/convert_cs.c \
			./srcs/convert_float.c \
			./srcs/convert_int.c \
			./srcs/convert_oux.c \
			./srcs/convert_p.c \
			./srcs/scanning.c

SRC-O	=	biggest_int.o \
			ft_abs.o \
			ft_atoi.o \
			ft_getbase.o \
			ft_getpow.o \
			ft_isdigit.o \
			ft_itobase.o \
			ft_pow.o \
			ft_strchr.o \
			ft_strcpy.o \
			ft_strdup.o \
			ft_strlen.o \
			ft_strmake.o \
			ft_strnew.o \
			ft_strncpy.o \
			ft_strndup.o \
			ft_strnset.o \
			ft_printf.o \
			parsing.o \
			convert_cs.o \
			convert_float.o \
			convert_int.o \
			convert_oux.o \
			convert_p.o \
			scanning.o

NAME	=	libftprintf.a

FLAG	=	-c -Wall -Werror -Wextra

all :		$(NAME)

$(NAME) :	$(SRC-C)
			gcc $(FLAG) $(SRC-C)
			ar rc $(NAME) $(SRC-O)

clean :
			/bin/rm -Rf $(SRC-O)

fclean :	clean
			/bin/rm -Rf $(NAME)

re :		fclean all
