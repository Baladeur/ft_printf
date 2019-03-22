/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 10:52:20 by tferrieu          #+#    #+#             */
/*   Updated: 2019/03/22 19:07:27 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		len_printable(const char *restrict format, t_printable *args)
{
	int			len;
	t_printable	*pos;

	len = ft_strlen(format);
	pos = args;
	while (pos)
	{
		len += (pos->len_str - pos->len_flag);
		pos = pos->next;
	}
	return (len);
}

static char*	merge(const char *restrict format, int *len, t_printable *args)
{
	t_printable	*pos;
	char		*printable;
	int			c1;
	int			c2;

	*len = len_printable(format, args);
	pos = args;
	c1 = 0;
	c2 = 0;
	if (!(printable = ft_strnew(*len + 1)))
		return (NULL);
	while (format[c1])
	{
		if (format[c1] == '%')
		{
			ft_strcpy(printable + c2, pos->str);
			c2 += pos->len_str;
			c1 += pos->len_flag;
			pos = pos->next;
		}
		printable[c2] = format[c1];
		c2++;
		c1++;
	}
	return (printable);
}

void			ft_printf(const char *restrict format, ...)
{
	t_printable	*args;
	int			len;
	//PARSING + error checker
	write(1, merge(format, &len, args), len);
}
