/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 10:52:20 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/10 19:56:11 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		len_modifier(t_printable *args)
{
	int			mod;
	t_printable	*pos;

	mod = 0;
	pos = args;
	while (pos)
	{
		mod += (pos->len_str - pos->len_flag);
		pos = pos->next;
	}
	return (mod);
}

static void		destroy_printable(t_printable **args)
{
	t_printable	*tmp;

	tmp = (*args)->next;
	if (*args)
	{
		if ((*args)->str)
			free((*args)->str);
		(*args)->str = NULL;
		free(*args);
		*args = NULL;
	}
	*args = tmp;
}

static char		*merge(const char *restrict format, int *len, t_printable *args)
{
	char		*printable;
	int			c1;
	int			c2;

	*len += len_modifier(args);
	c1 = 0;
	c2 = 0;
	if (!(printable = ft_strnew(*len + 1)))
		return (NULL);
	while (format[c1])
	{
		if (format[c1] == '%' && (c1 += args->len_flag - 1) >= 0)
		{
			ft_strcpy(printable + c2, args->str);
			c2 += args->len_str - 1;
			destroy_printable(&args);
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
	args = NULL;
	va_start(arglist, format);
	if (!(parse(format, arglist, &len, &args)))
	{
		write(1, "Parsing error\n", 14);
		return (-1);
	}
	va_end(arglist);
	if (!(res = merge(format, &len, args)))
	{
		write(1, "Merging error\n", 14);
		return (-1);
	}
	else
	{
		write(1, res, len);
		free(res);
		return (len);
	}
}
