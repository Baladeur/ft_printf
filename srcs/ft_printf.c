/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 10:52:20 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/03 18:54:29 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		len_modifier(t_printable *args)
{
	int			mod;
	t_printable	*pos;

	mod = 0;
	pos = args;
	while (pos->next)
	{
		mod += (pos->len_str - pos->len_flag);
		pos = pos->next;
	}
	return (mod);
}

static char		*merge(const char *restrict format, int *len, t_printable *args)
{
	t_printable	*pos;
	char		*printable;
	int			c1;
	int			c2;

	*len += len_modifier(args);
	pos = args;
	c1 = 0;
	c2 = 0;
	if (!(printable = ft_strnew(*len + 1)))
		return (NULL);
	while (format[c1])
	{
		if (format[c1] == '%' && (c1 += pos->len_flag - 1) >= 0)
		{
			ft_strcpy(printable + c2, pos->str);
			c2 += pos->len_str - 1;
			pos = pos->next;
		}
		else
			printable[c2] = format[c1];
		c2++;
		c1++;
	}
	return (printable);
}

int				ft_printf(const char *restrict format, ...)
{
	t_printable	*args;
	va_list		arglist;
	char		*res;
	int			len;

	len = 0;
	va_start(arglist, format);
	if (!(args = parse(format, arglist, &len)))
	{
		write(2, "Parsing error\n", 14);
		return (-1);
	}
	else
	{
		va_end(arglist);
		if (!(res = merge(format, &len, args)))
		{
			write(2, "Malloc error\n", 13);
			return (-1);
		}
		else
			return(write(1, res, len));
	}
}
