/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 10:48:00 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/03 18:53:00 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct	s_printable
{
	char				*str;
	int					len_str;
	int					len_flag;
	struct s_printable	*next;
}				t_printable;

char			*convert_unsigned(va_list arglist, t_printable *args,
								char *flags, char id);

char			*convert_char(va_list arglist, t_printable *args, char *flag,
								int p);

char			*convert_str(va_list arglist, t_printable *args, char *flag);

char			*convert_ptr(va_list arglist, t_printable *args, char *flag);

t_printable		*parse(const char *restrict format, va_list arglist, int *len);

int				ft_printf(const char *restrict format, ...);

#endif
