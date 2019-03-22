/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 10:48:00 by tferrieu          #+#    #+#             */
/*   Updated: 2019/03/22 19:10:21 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_printable
{
	char				*str;
	int					len_str;
	int					len_flag;
	struct s_printable	*next;
}				t_printable;

void			ft_printf(const char *restrict format, ...);

#endif
